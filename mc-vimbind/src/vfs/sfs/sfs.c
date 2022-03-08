/*
   Single File fileSystem

   Copyright 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,
   2011
   The Free Software Foundation, Inc.

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

/**
 * \file
 * \brief Source: Single File fileSystem
 *
 * This defines whole class of filesystems which contain single file
 * inside. It is somehow similar to extfs, except that extfs makes
 * whole virtual trees and we do only single virtual files.
 *
 * If you want to gunzip something, you should open it with \verbatim #ugz \endverbatim
 * suffix, DON'T try to gunzip it yourself.
 *
 * Namespace: exports vfs_sfs_ops
 */

#include <config.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "lib/global.h"
#include "lib/util.h"
#include "lib/widget.h"         /* D_ERROR, D_NORMAL */

#include "src/execute.h"        /* EXECUTE_AS_SHELL */

#include "lib/vfs/vfs.h"
#include "lib/vfs/utilvfs.h"
#include "src/vfs/local/local.h"
#include "lib/vfs/gc.h"         /* vfs_stamp_create */

#include "sfs.h"

/*** global variables ****************************************************************************/

/*** file scope macro definitions ****************************************************************/

#define MAXFS 32

#define F_1 1
#define F_2 2
#define F_NOLOCALCOPY 4
#define F_FULLMATCH 8

#define COPY_CHAR \
    if ((size_t) (t - pad) > sizeof(pad)) \
    { \
        g_free (pqname); \
        return -1; \
    } \
    else \
        *t++ = *s;

#define COPY_STRING(a) \
    if ((t - pad) + strlen(a) > sizeof(pad)) \
    { \
        g_free (pqname); \
        return -1; \
    } \
    else \
    { \
        strcpy (t, a); \
        t += strlen (a); \
    }

/*** file scope type declarations ****************************************************************/

typedef struct cachedfile
{
    char *name;
    char *cache;
} cachedfile;

/*** file scope variables ************************************************************************/

static GSList *head;
static struct vfs_class vfs_sfs_ops;

static int sfs_no = 0;
static char *sfs_prefix[MAXFS];
static char *sfs_command[MAXFS];
static int sfs_flags[MAXFS];

/*** file scope functions ************************************************************************/

static int
cachedfile_compare (const void *a, const void *b)
{
    const cachedfile *cf = (const cachedfile *) a;
    const char *name = (const char *) b;

    return strcmp (name, cf->name);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_vfmake (const vfs_path_t * vpath, char *cache)
{
    int w;
    char pad[10240];
    char *s, *t = pad;
    int was_percent = 0;
    char *pname;                /* name of parent archive */
    char *pqname;               /* name of parent archive, quoted */
    vfs_path_element_t *path_element;

    path_element = vfs_path_get_by_index (vpath, -1);
    pname = vfs_path_to_str_elements_count (vpath, -1);
    w = (*path_element->class->which) (path_element->class, path_element->vfs_prefix);
    if (w == -1)
        vfs_die ("This cannot happen... Hopefully.\n");

    if (!(sfs_flags[w] & F_1) && strcmp (pname, "/"))
    {
        g_free (pname);
        return -1;
    }

    /*    if ((sfs_flags[w] & F_2) || (!inpath) || (!*inpath)); else return -1; */
    if (!(sfs_flags[w] & F_NOLOCALCOPY))
    {
        s = mc_getlocalcopy (pname);
        if (!s)
        {
            g_free (pname);
            return -1;
        }
        pqname = name_quote (s, 0);
        g_free (s);
    }
    else
    {
        pqname = name_quote (pname, 0);
    }
    g_free (pname);


    for (s = sfs_command[w]; *s; s++)
    {
        if (was_percent)
        {

            const char *ptr = NULL;
            was_percent = 0;

            switch (*s)
            {
            case '1':
                ptr = pqname;
                break;
            case '2':
                ptr = path_element->path;
                break;
            case '3':
                ptr = cache;
                break;
            case '%':
                COPY_CHAR;
                continue;
            }
            COPY_STRING (ptr);
        }
        else
        {
            if (*s == '%')
                was_percent = 1;
            else
                COPY_CHAR;
        }
    }

    g_free (pqname);
    open_error_pipe ();
    if (my_system (EXECUTE_AS_SHELL, "/bin/sh", pad))
    {
        close_error_pipe (D_ERROR, NULL);
        return -1;
    }

    close_error_pipe (D_NORMAL, NULL);
    return 0;                   /* OK */
}

/* --------------------------------------------------------------------------------------------- */

static const char *
sfs_redirect (const vfs_path_t * vpath)
{
    GSList *cur;
    cachedfile *cf;
    char *cache;
    int handle;
    vfs_path_element_t *path_element;
    char *path = vfs_path_to_str (vpath);

    path_element = vfs_path_get_by_index (vpath, -1);
    cur = g_slist_find_custom (head, path, cachedfile_compare);
    g_free (path);

    if (cur != NULL)
    {
        cf = (cachedfile *) cur->data;
        vfs_stamp (&vfs_sfs_ops, cf);
        return cf->cache;
    }

    handle = vfs_mkstemps (&cache, "sfs", path_element->path);

    if (handle == -1)
        return "/SOMEONE_PLAYING_DIRTY_TMP_TRICKS_ON_US";

    close (handle);

    if (sfs_vfmake (vpath, cache) == 0)
    {
        cf = g_new (cachedfile, 1);
        cf->name = vfs_path_to_str (vpath);
        cf->cache = cache;
        head = g_slist_prepend (head, cf);

        vfs_stamp_create (&vfs_sfs_ops, (cachedfile *) head->data);
        return cache;
    }

    unlink (cache);
    g_free (cache);
    return "/I_MUST_NOT_EXIST";
}

/* --------------------------------------------------------------------------------------------- */

static void *
sfs_open (const vfs_path_t * vpath /*struct vfs_class *me, const char *path */ , int flags,
          mode_t mode)
{
    int *sfs_info;
    int fd;

    fd = open (sfs_redirect (vpath), NO_LINEAR (flags), mode);
    if (fd == -1)
        return 0;

    sfs_info = g_new (int, 1);
    *sfs_info = fd;

    return sfs_info;
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_stat (const vfs_path_t * vpath, struct stat *buf)
{
    return stat (sfs_redirect (vpath), buf);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_lstat (const vfs_path_t * vpath, struct stat *buf)
{
#ifndef HAVE_STATLSTAT
    return lstat (sfs_redirect (vpath), buf);
#else
    return statlstat (sfs_redirect (vpath), buf);
#endif
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_chmod (const vfs_path_t * vpath, mode_t mode)
{
    return chmod (sfs_redirect (vpath), mode);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_chown (const vfs_path_t * vpath, uid_t owner, gid_t group)
{
    return chown (sfs_redirect (vpath), owner, group);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_utime (const vfs_path_t * vpath, struct utimbuf *times)
{
    return utime (sfs_redirect (vpath), times);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_readlink (const vfs_path_t * vpath, char *buf, size_t size)
{
    return readlink (sfs_redirect (vpath), buf, size);
}

/* --------------------------------------------------------------------------------------------- */

static vfsid
sfs_getid (const vfs_path_t * vpath)
{
    GSList *cur;
    char *path = vfs_path_to_str (vpath);

    cur = g_slist_find_custom (head, path, cachedfile_compare);
    g_free (path);

    return (vfsid) (cur != NULL ? cur->data : NULL);
}

/* --------------------------------------------------------------------------------------------- */

static void
sfs_free (vfsid id)
{
    struct cachedfile *which;
    GSList *cur;

    which = (struct cachedfile *) id;
    cur = g_slist_find (head, which);
    if (cur == NULL)
        vfs_die ("Free of thing which is unknown to me\n");

    which = (struct cachedfile *) cur->data;
    unlink (which->cache);
    g_free (which->cache);
    g_free (which->name);
    g_free (which);

    head = g_slist_delete_link (head, cur);
}

/* --------------------------------------------------------------------------------------------- */

static void
sfs_fill_names (struct vfs_class *me, fill_names_f func)
{
    GSList *cur;

    (void) me;

    for (cur = head; cur != NULL; cur = g_slist_next (cur))
        func (((cachedfile *) cur->data)->name);
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_nothingisopen (vfsid id)
{
    /* FIXME: Investigate whether have to guard this like in
       the other VFSs (see fd_usage in extfs) -- Norbert */
    (void) id;
    return 1;
}

/* --------------------------------------------------------------------------------------------- */

static char *
sfs_getlocalcopy (const vfs_path_t * vpath)
{
    return g_strdup (sfs_redirect (vpath));
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_ungetlocalcopy (const vfs_path_t * vpath, const char *local, int has_changed)
{
    (void) vpath;
    (void) local;
    (void) has_changed;
    return 0;
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_init (struct vfs_class *me)
{
    char *mc_sfsini;
    FILE *cfg;
    char key[256];

    (void) me;

    mc_sfsini = g_build_filename (mc_global.sysconfig_dir, "sfs.ini", (char *) NULL);
    cfg = fopen (mc_sfsini, "r");

    if (cfg == NULL)
    {
        fprintf (stderr, _("%s: Warning: file %s not found\n"), "sfs_init()", mc_sfsini);
        g_free (mc_sfsini);
        return 0;
    }
    g_free (mc_sfsini);

    sfs_no = 0;
    while (sfs_no < MAXFS && fgets (key, sizeof (key), cfg))
    {
        char *c, *semi = NULL, flags = 0;

        if (*key == '#' || *key == '\n')
            continue;

        for (c = key; *c; c++)
            if ((*c == ':') || (*c == '/'))
            {
                semi = c;
                if (*c == '/')
                {
                    *c = 0;
                    flags |= F_FULLMATCH;
                }
                break;
            }

        if (!semi)
        {
          invalid_line:
            fprintf (stderr, _("Warning: Invalid line in %s:\n%s\n"), "sfs.ini", key);
            continue;
        }

        c = semi + 1;
        while (*c && (*c != ' ') && (*c != '\t'))
        {
            switch (*c)
            {
            case '1':
                flags |= F_1;
                break;
            case '2':
                flags |= F_2;
                break;
            case 'R':
                flags |= F_NOLOCALCOPY;
                break;
            default:
                fprintf (stderr, _("Warning: Invalid flag %c in %s:\n%s\n"), *c, "sfs.ini", key);
            }
            c++;
        }
        if (!*c)
            goto invalid_line;

        c++;
        *(semi + 1) = 0;
        semi = strchr (c, '\n');
        if (semi != NULL)
            *semi = 0;

        sfs_prefix[sfs_no] = g_strdup (key);
        sfs_command[sfs_no] = g_strdup (c);
        sfs_flags[sfs_no] = flags;
        sfs_no++;
    }
    fclose (cfg);
    return 1;
}

/* --------------------------------------------------------------------------------------------- */

static void
sfs_done (struct vfs_class *me)
{
    int i;

    (void) me;

    for (i = 0; i < sfs_no; i++)
    {
        g_free (sfs_prefix[i]);
        g_free (sfs_command[i]);
        sfs_prefix[i] = sfs_command[i] = NULL;
    }
    sfs_no = 0;
}

/* --------------------------------------------------------------------------------------------- */

static int
sfs_which (struct vfs_class *me, const char *path)
{
    int i;

    (void) me;

    for (i = 0; i < sfs_no; i++)
        if (sfs_flags[i] & F_FULLMATCH)
        {
            if (!strcmp (path, sfs_prefix[i]))
                return i;
        }
        else if (!strncmp (path, sfs_prefix[i], strlen (sfs_prefix[i])))
            return i;

    return -1;
}

/* --------------------------------------------------------------------------------------------- */
/*** public functions ****************************************************************************/
/* --------------------------------------------------------------------------------------------- */

void
init_sfs (void)
{
    vfs_sfs_ops.name = "sfs";
    vfs_sfs_ops.init = sfs_init;
    vfs_sfs_ops.done = sfs_done;
    vfs_sfs_ops.fill_names = sfs_fill_names;
    vfs_sfs_ops.which = sfs_which;
    vfs_sfs_ops.open = sfs_open;
    vfs_sfs_ops.close = local_close;
    vfs_sfs_ops.read = local_read;
    vfs_sfs_ops.stat = sfs_stat;
    vfs_sfs_ops.lstat = sfs_lstat;
    vfs_sfs_ops.fstat = local_fstat;
    vfs_sfs_ops.chmod = sfs_chmod;
    vfs_sfs_ops.chown = sfs_chown;
    vfs_sfs_ops.utime = sfs_utime;
    vfs_sfs_ops.readlink = sfs_readlink;
    vfs_sfs_ops.ferrno = local_errno;
    vfs_sfs_ops.lseek = local_lseek;
    vfs_sfs_ops.getid = sfs_getid;
    vfs_sfs_ops.nothingisopen = sfs_nothingisopen;
    vfs_sfs_ops.free = sfs_free;
    vfs_sfs_ops.getlocalcopy = sfs_getlocalcopy;
    vfs_sfs_ops.ungetlocalcopy = sfs_ungetlocalcopy;
    vfs_register_class (&vfs_sfs_ops);
}

/* --------------------------------------------------------------------------------------------- */
