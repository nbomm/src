/** \file  execute.h
 *  \brief Header: execution routines
 */

#ifndef MC__EXECUTE_H
#define MC__EXECUTE_H

#include "lib/utilunix.h"

/*** typedefs(not structures) and defined constants **********************************************/

/*** enums ***************************************************************************************/

/* If true, after executing a command, wait for a keystroke */
enum
{
    pause_never,
    pause_on_dumb_terminals,
    pause_always
};

/*** structures declarations (and typedefs of structures)*****************************************/

/*** global variables defined in .c file *********************************************************/

extern int pause_after_run;

/*** declarations of public functions ************************************************************/

/* Execute functions that use the shell to execute */
void shell_execute (const char *command, int flags);

/* This one executes a shell */
void exec_shell (void);

/* Handle toggling panels by Ctrl-O */
void toggle_panels (void);

/* Handle toggling panels by Ctrl-Z */
gboolean execute_suspend (const gchar * event_group_name, const gchar * event_name,
                          gpointer init_data, gpointer data);

/* Execute command on a filename that can be on VFS */
void execute_with_vfs_arg (const char *command, const char *filename);

void post_exec (void);
void pre_exec (void);

/*** inline functions ****************************************************************************/

#endif /* MC__EXECUTE_H */