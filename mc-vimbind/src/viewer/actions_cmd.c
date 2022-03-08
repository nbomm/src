/*
   Internal file viewer for the Midnight Commander
   Callback function for some actions (hotkeys, menu)

   Copyright (C) 1994, 1995, 1996, 1998, 1999, 2000, 2001, 2002, 2003,
   2004, 2005, 2006, 2007, 2009, 2011
   The Free Software Foundation, Inc.

   Written by:
   Miguel de Icaza, 1994, 1995, 1998
   Janne Kukonlehto, 1994, 1995
   Jakub Jelinek, 1995
   Joseph M. Hinkle, 1996
   Norbert Warmuth, 1997
   Pavel Machek, 1998
   Roland Illig <roland.illig@gmx.de>, 2004, 2005
   Slava Zanko <slavazanko@google.com>, 2009
   Andrew Borodin <aborodin@vmail.ru>, 2009
   Ilia Maslakov <il.smind@gmail.com>, 2009

   This file is part of the Midnight Commander.

   The Midnight Commander is free software: you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   The Midnight Commander is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
   The functions in this section can be bound to hotkeys. They are all
   of the same type (taking a pointer to mcview_t as parameter and
   returning void). TODO: In the not-too-distant future, these commands
   will become fully configurable, like they already are in the
   internal editor. By convention, all the function names end in
   "_cmd".
 */

#include <config.h>

#include <errno.h>
#include <stdlib.h>

#include "lib/global.h"

#include "lib/tty/tty.h"
#include "lib/tty/key.h"        /* is_idle() */
#include "lib/lock.h"           /* lock_file() */
#include "lib/util.h"
#include "lib/widget.h"
#include "lib/charsets.h"
#include "lib/event.h"          /* mc_event_raise() */

#include "src/filemanager/layout.h"
#include "src/filemanager/cmd.h"
#include "src/filemanager/midnight.h"   /* current_panel */

#include "src/history.h"
#include "src/execute.h"
#include "src/keybind-defaults.h"

#include "internal.h"
#include "mcviewer.h"

/*** global variables ****************************************************************************/

/*** file scope macro definitions ****************************************************************/

/*** file scope type declarations ****************************************************************/

/*** file scope variables ************************************************************************/

/*** file scope functions ************************************************************************/
/* --------------------------------------------------------------------------------------------- */

/* Both views */
static void
mcview_search (mcview_t * view)
{
    if (mcview_dialog_search (view))
        mcview_do_search (view);
}

/* --------------------------------------------------------------------------------------------- */

static void
mcview_continue_search_cmd (mcview_t * view)
{
    if (view->last_search_string != NULL)
    {
        mcview_do_search (view);
    }
    else
    {
        /* find last search string in history */
        GList *history;
        history = history_get (MC_HISTORY_SHARED_SEARCH);
        if (history != NULL && history->data != NULL)
        {
            view->last_search_string = (gchar *) g_strdup (history->data);
            history = g_list_first (history);
            g_list_foreach (history, (GFunc) g_free, NULL);
            g_list_free (history);

            view->search = mc_search_new (view->last_search_string, -1);
            view->search_nroff_seq = mcview_nroff_seq_new (view);

            if (!view->search)
            {
                /* if not... then ask for an expression */
                g_free (view->last_search_string);
                view->last_search_string = NULL;
                mcview_search (view);
            }
            else
            {
                view->search->search_type = mcview_search_options.type;
                view->search->is_all_charsets = mcview_search_options.all_codepages;
                view->search->is_case_sensitive = mcview_search_options.case_sens;
                view->search->whole_words = mcview_search_options.whole_words;
                view->search->search_fn = mcview_search_cmd_callback;
                view->search->update_fn = mcview_search_update_cmd_callback;

                mcview_do_search (view);
            }
        }
        else
        {
            /* if not... then ask for an expression */
            g_free (view->last_search_string);
            view->last_search_string = NULL;
            mcview_search (view);
        }
    }
}

/* --------------------------------------------------------------------------------------------- */

static void
mcview_hook (void *v)
{
    mcview_t *view = (mcview_t *) v;
    WPanel *panel;

    /* If the user is busy typing, wait until he finishes to update the
       screen */
    if (!is_idle ())
    {
        if (!hook_present (idle_hook, mcview_hook))
            add_hook (&idle_hook, mcview_hook, v);
        return;
    }

    delete_hook (&idle_hook, mcview_hook);

    if (get_current_type () == view_listing)
        panel = current_panel;
    else if (get_other_type () == view_listing)
        panel = other_panel;
    else
        return;

    mcview_done (view);
    mcview_init (view);
    mcview_load (view, 0, panel->dir.list[panel->selected].fname, 0);
    mcview_display (view);
}

/* --------------------------------------------------------------------------------------------- */

static cb_ret_t
mcview_handle_editkey (mcview_t * view, int key)
{
    struct hexedit_change_node *node;
    int byte_val;

    /* Has there been a change at this position? */
    node = view->change_list;
    while ((node != NULL) && (node->offset != view->hex_cursor))
        node = node->next;

    if (!view->hexview_in_text)
    {
        /* Hex editing */
        unsigned int hexvalue = 0;

        if (key >= '0' && key <= '9')
            hexvalue = 0 + (key - '0');
        else if (key >= 'A' && key <= 'F')
            hexvalue = 10 + (key - 'A');
        else if (key >= 'a' && key <= 'f')
            hexvalue = 10 + (key - 'a');
        else
            return MSG_NOT_HANDLED;

        if (node != NULL)
            byte_val = node->value;
        else
            mcview_get_byte (view, view->hex_cursor, &byte_val);

        if (view->hexedit_lownibble)
            byte_val = (byte_val & 0xf0) | (hexvalue);
        else
            byte_val = (byte_val & 0x0f) | (hexvalue << 4);
    }
    else
    {
        /* Text editing */
        if (key < 256 && ((key == '\n') || is_printable (key)))
            byte_val = key;
        else
            return MSG_NOT_HANDLED;
    }

    if ((view->filename != NULL) && (view->filename[0] != '\0') && (view->change_list == NULL))
        view->locked = mcview_lock_file (view);

    if (node == NULL)
    {
        node = g_new (struct hexedit_change_node, 1);
        node->offset = view->hex_cursor;
        node->value = byte_val;
        mcview_enqueue_change (&view->change_list, node);
    }
    else
        node->value = byte_val;

    view->dirty++;
    mcview_move_right (view, 1);

    return MSG_HANDLED;
}

/* --------------------------------------------------------------------------------------------- */

static cb_ret_t
mcview_execute_cmd (mcview_t * view, unsigned long command)
{
    int res = MSG_HANDLED;

    switch (command)
    {
    case CK_Help:
        {
            ev_help_t event_data = { NULL, "[Internal File Viewer]" };
            mc_event_raise (MCEVENT_GROUP_CORE, "help", &event_data);
        }
        break;
    case CK_WrapMode:
        /* Toggle between wrapped and unwrapped view */
        mcview_toggle_wrap_mode (view);
        break;
    case CK_HexEditMode:
        /* Toggle between hexview and hexedit mode */
        mcview_toggle_hexedit_mode (view);
        break;
    case CK_HexMode:
        /* Toggle between hex view and text view */
        mcview_toggle_hex_mode (view);
        break;
    case CK_Goto:
        {
            off_t addr;

            if (mcview_dialog_goto (view, &addr))
            {
                if (addr >= 0)
                    mcview_moveto_offset (view, addr);
                else
                {
                    message (D_ERROR, _("Warning"), _("Invalid value"));
                    view->dirty++;
                }
            }
            break;
        }
    case CK_Save:
        mcview_hexedit_save_changes (view);
        break;
    case CK_Search:
        mcview_search (view);
        break;
    case CK_MagicMode:
        mcview_toggle_magic_mode (view);
        break;
    case CK_NroffMode:
        mcview_toggle_nroff_mode (view);
        break;
    case CK_ToggleNavigation:
        view->hexview_in_text = !view->hexview_in_text;
        view->dirty++;
        break;
    case CK_Home:
        mcview_moveto_bol (view);
        break;
    case CK_End:
        mcview_moveto_eol (view);
        break;
    case CK_Left:
        mcview_move_left (view, 1);
        break;
    case CK_Right:
        mcview_move_right (view, 1);
        break;
    case CK_LeftQuick:
        if (!view->hex_mode)
            mcview_move_left (view, 10);
        break;
    case CK_RightQuick:
        if (!view->hex_mode)
            mcview_move_right (view, 10);
        break;
    case CK_SearchContinue:
        mcview_continue_search_cmd (view);
        break;
    case CK_Ruler:
        mcview_display_toggle_ruler (view);
        break;
    case CK_Up:
        mcview_move_up (view, 1);
        break;
    case CK_Down:
        mcview_move_down (view, 1);
        break;
    case CK_HalfPageUp:
        mcview_move_up (view, (view->data_area.height + 1) / 2);
        break;
    case CK_HalfPageDown:
        mcview_move_down (view, (view->data_area.height + 1) / 2);
        break;
    case CK_PageUp:
        mcview_move_up (view, view->data_area.height);
        break;
    case CK_PageDown:
        mcview_move_down (view, view->data_area.height);
        break;
    case CK_Top:
        mcview_moveto_top (view);
        break;
    case CK_Bottom:
        mcview_moveto_bottom (view);
        break;
    case CK_Shell:
        view_other_cmd ();
        break;
    case CK_BookmarkGoto:
        view->marks[view->marker] = view->dpy_start;
        break;
    case CK_Bookmark:
        view->dpy_start = view->marks[view->marker];
        view->dirty++;
        break;
#ifdef HAVE_CHARSET
    case CK_SelectCodepage:
        mcview_select_encoding (view);
        view->dirty++;
        break;
#endif
    case CK_FileNext:
    case CK_FilePrev:
        /* Use to indicate parent that we want to see the next/previous file */
        /* Does not work in panel mode */
        if (!mcview_is_in_panel (view))
            view->move_dir = (command == CK_FileNext) ? 1 : -1;
        /* fallthrough */
    case CK_Quit:
        if (!mcview_is_in_panel (view))
            dlg_stop (view->widget.owner);
        break;
    case CK_Cancel:
        /* don't close viewer due to SIGINT */
        break;
    default:
        res = MSG_NOT_HANDLED;
    }
    return res;
}

/* --------------------------------------------------------------------------------------------- */
/** Both views */
static cb_ret_t
mcview_handle_key (mcview_t * view, int key)
{
    unsigned long command;

    key = convert_from_input_c (key);

    if (view->hex_mode)
    {
        if (view->hexedit_mode && (mcview_handle_editkey (view, key) == MSG_HANDLED))
            return MSG_HANDLED;

        command = keybind_lookup_keymap_command (viewer_hex_map, key);
        if ((command != CK_IgnoreKey) && (mcview_execute_cmd (view, command) == MSG_HANDLED))
            return MSG_HANDLED;
    }

    command = keybind_lookup_keymap_command (viewer_map, key);
    if ((command != CK_IgnoreKey) && (mcview_execute_cmd (view, command) == MSG_HANDLED))
        return MSG_HANDLED;

#ifdef MC_ENABLE_DEBUGGING_CODE
    if (c == 't')
    {                           /* mnemonic: "test" */
        mcview_ccache_dump (view);
        return MSG_HANDLED;
    }
#endif
    if (key >= '0' && key <= '9')
        view->marker = key - '0';

    /* Key not used */
    return MSG_NOT_HANDLED;
}


/* --------------------------------------------------------------------------------------------- */

static inline void
mcview_adjust_size (Dlg_head * h)
{
    mcview_t *view;
    WButtonBar *b;

    /* Look up the viewer and the buttonbar, we assume only two widgets here */
    view = (mcview_t *) find_widget_type (h, mcview_callback);
    b = find_buttonbar (h);

    widget_set_size (&view->widget, 0, 0, LINES - 1, COLS);
    widget_set_size (&b->widget, LINES - 1, 0, 1, COLS);

    mcview_compute_areas (view);
    mcview_update_bytes_per_line (view);
}


/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

cb_ret_t
mcview_callback (Widget * w, widget_msg_t msg, int parm)
{
    mcview_t *view = (mcview_t *) w;
    cb_ret_t i;

    mcview_compute_areas (view);
    mcview_update_bytes_per_line (view);

    switch (msg)
    {
    case WIDGET_INIT:
        if (mcview_is_in_panel (view))
            add_hook (&select_file_hook, mcview_hook, view);
        else
            view->dpy_bbar_dirty = TRUE;
        return MSG_HANDLED;

    case WIDGET_DRAW:
        mcview_display (view);
        return MSG_HANDLED;

    case WIDGET_CURSOR:
        if (view->hex_mode)
            mcview_place_cursor (view);
        return MSG_HANDLED;

    case WIDGET_KEY:
        i = mcview_handle_key (view, parm);
        mcview_update (view);
        return i;

    case WIDGET_COMMAND:
        i = mcview_execute_cmd (view, parm);
        mcview_update (view);
        return i;

    case WIDGET_FOCUS:
        view->dpy_bbar_dirty = TRUE;
        mcview_update (view);
        return MSG_HANDLED;

    case WIDGET_DESTROY:
        if (mcview_is_in_panel (view))
        {
            delete_hook (&select_file_hook, mcview_hook);

            if (mc_global.widget.midnight_shutdown)
                mcview_ok_to_quit (view);
        }
        mcview_done (view);
        return MSG_HANDLED;

    default:
        return default_proc (msg, parm);
    }
}

/* --------------------------------------------------------------------------------------------- */

cb_ret_t
mcview_dialog_callback (Dlg_head * h, Widget * sender, dlg_msg_t msg, int parm, void *data)
{
    mcview_t *view;

    switch (msg)
    {
    case DLG_RESIZE:
        mcview_adjust_size (h);
        return MSG_HANDLED;

    case DLG_ACTION:
        /* shortcut */
        if (sender == NULL)
            return mcview_execute_cmd (NULL, parm);
        /* message from buttonbar */
        if (sender == (Widget *) find_buttonbar (h))
        {
            if (data != NULL)
                return send_message ((Widget *) data, WIDGET_COMMAND, parm);

            view = (mcview_t *) find_widget_type (h, mcview_callback);
            return mcview_execute_cmd (view, parm);
        }
        return MSG_NOT_HANDLED;

    case DLG_VALIDATE:
        view = (mcview_t *) find_widget_type (h, mcview_callback);
        h->state = DLG_ACTIVE;  /* don't stop the dialog before final decision */
        if (mcview_ok_to_quit (view))
            h->state = DLG_CLOSED;
        else
            mcview_update (view);
        return MSG_HANDLED;

    default:
        return default_dlg_callback (h, sender, msg, parm, data);
    }
}

/* --------------------------------------------------------------------------------------------- */
