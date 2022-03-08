/*
   lib/vfs - test vfs_parse_ls_lga() functionality

   Copyright (C) 2011
   The Free Software Foundation, Inc.

   Written by:
   Slava Zanko <slavazanko@gmail.com>, 2011

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

#define TEST_SUITE_NAME "/lib/vfs"

#include <config.h>

#include <check.h>
#include <stdio.h>

#include "lib/global.h"
#include "lib/vfs/utilvfs.h"
#include "lib/vfs/xdirentry.h"
#include "lib/strutil.h"

#include "src/vfs/local/local.c"


struct vfs_s_subclass test_subclass1;
struct vfs_class vfs_test_ops1;

struct vfs_s_entry *vfs_root_entry;
static struct vfs_s_inode *vfs_root_inode;
static struct vfs_s_super *vfs_test_super;

void message (int flags, const char *title, const char *text, ...);


static void
setup (void)
{
    static struct stat initstat;

    str_init_strings (NULL);

    vfs_init ();
    init_localfs ();
    vfs_setup_work_dir ();

    test_subclass1.flags = VFS_S_REMOTE;
    vfs_s_init_class (&vfs_test_ops1, &test_subclass1);
    vfs_test_ops1.name = "testfs1";
    vfs_test_ops1.flags = VFSF_NOLINKS;
    vfs_test_ops1.prefix = "test1:";
    vfs_register_class (&vfs_test_ops1);

    vfs_test_super = g_new0 (struct vfs_s_super, 1);
    vfs_test_super->me = &vfs_test_ops1;

    vfs_root_inode = vfs_s_new_inode (&vfs_test_ops1, vfs_test_super, &initstat);
    vfs_root_entry = vfs_s_new_entry (&vfs_test_ops1, "/", vfs_root_inode);
}

static void
teardown (void)
{
    vfs_s_free_entry (&vfs_test_ops1, vfs_root_entry);
    vfs_shut ();
    str_uninit_strings ();
}


void
message (int flags, const char *title, const char *text, ...)
{
    char *p;
    va_list ap;

    (void) flags;
    (void) title;

    va_start (ap, text);
    p = g_strdup_vprintf (text, ap);
    va_end (ap);
    printf("message(): %s\n", p);
    g_free(p);
}

/* --------------------------------------------------------------------------------------------- */

#define check_one_stat_field(etalon_stat, test_stat, field, format, input_str)\
{\
    fail_unless(etalon_stat.field == test_stat.field,\
    "\ninput string: %s\netalon."#field" = " format "\nactual."#field" = " format "\n",\
    input_str, etalon_stat.field, test_stat.field);\
}

#define check_stat_struct(etalon_stat, test_stat, input_str)\
{\
    check_one_stat_field(etalon_stat, test_stat, st_dev, "%zu", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_ino, "%zu", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_ino, "%zu", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_mode, "%04x", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_uid, "%u", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_gid, "%u", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_rdev, "%zu", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_size, "%zd", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_blksize, "%zu", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_blocks, "%zd", input_str);\
\
/* FIXME: these commented checks are related to time zone! \
    check_one_stat_field(etalon_stat, test_stat, st_atime, "%zd", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_mtime, "%zd", input_str);\
    check_one_stat_field(etalon_stat, test_stat, st_ctime, "%zd", input_str);\
*/\
}

static void check_vfs_parse_ls_lga_call(const char *input_data, int etalon_result,
const char *etalon_filename, const char *etalon_linkname, struct stat etalon_stat, size_t *filepos)
{
    static struct stat test_stat;
    char *filename = NULL;
    char *linkname = NULL;
    gboolean result;

    result = vfs_parse_ls_lga (input_data, &test_stat, &filename, &linkname, filepos);

    fail_if (result != etalon_result,
        "\nactual result: %d\netalon result: %d\n", result, etalon_result);

    fail_unless((filename != NULL && etalon_filename != NULL && strcmp(filename, etalon_filename) == 0)
        || (filename == NULL && etalon_filename == filename),
        "\nactual filename '%s'\netalon filename '%s'", filename, etalon_filename);

    fail_unless((linkname != NULL && etalon_linkname != NULL && strcmp(linkname, etalon_linkname) == 0)
        || (linkname == NULL && etalon_linkname == linkname),
        "\nactual linkname '%s'\netalon linkname '%s'", linkname, etalon_linkname);

    check_stat_struct(etalon_stat, test_stat, input_data);
}

START_TEST (test_vfs_parse_ls_lga)
{
    size_t filepos = 0;

    vfs_parse_ls_lga_init();

    check_vfs_parse_ls_lga_call(
        "drwxrwxr-x   10 500      500          4096 Jun 23 17:09 build_root",
        1, "build_root", NULL, (struct stat)
        {
        .st_dev = 0,
        .st_ino = 0,
        .st_mode = 0x41fd,
        .st_nlink = 10,
        .st_uid = 500,
        .st_gid = 500,
        .st_rdev = 0,
        .st_size = 4096,
        .st_blksize = 512,
        .st_blocks = 8,
        .st_atime = 1308838140,
        .st_mtime = 1308838140,
        .st_ctime = 1308838140
        },
        NULL
    );

    check_vfs_parse_ls_lga_call(
        "lrwxrwxrwx    1 500      500            11 Mar 13  2010 COPYING -> doc/COPYING",
        1, "COPYING", "doc/COPYING",
        (struct stat)
        {
        .st_dev = 0,
        .st_ino = 0,
        .st_mode = 0xa1ff,
        .st_nlink = 10,
        .st_uid = 500,
        .st_gid = 500,
        .st_rdev = 0,
        .st_size = 11,
        .st_blksize = 512,
        .st_blocks = 1,
        .st_atime = 1268431200,
        .st_mtime = 1268431200,
        .st_ctime = 1268431200
        },
        NULL
    );

    check_vfs_parse_ls_lga_call(
        "drwxrwxr-x   10 500      500          4096 Jun 23 17:09 ..",
        1, "..", NULL, (struct stat)
        {
        .st_dev = 0,
        .st_ino = 0,
        .st_mode = 0x41fd,
        .st_nlink = 10,
        .st_uid = 500,
        .st_gid = 500,
        .st_rdev = 0,
        .st_size = 4096,
        .st_blksize = 512,
        .st_blocks = 8,
        .st_atime = 1308838140,
        .st_mtime = 1308838140,
        .st_ctime = 1308838140
        },
        &filepos
    );

    check_vfs_parse_ls_lga_call(
        "drwxrwxr-x   10 500      500          4096 Jun 23 17:09   build_root",
        1, "build_root", NULL, (struct stat)
        {
        .st_dev = 0,
        .st_ino = 0,
        .st_mode = 0x41fd,
        .st_nlink = 10,
        .st_uid = 500,
        .st_gid = 500,
        .st_rdev = 0,
        .st_size = 4096,
        .st_blksize = 512,
        .st_blocks = 8,
        .st_atime = 1308838140,
        .st_mtime = 1308838140,
        .st_ctime = 1308838140
        },
        &filepos
    );

}
END_TEST

/* --------------------------------------------------------------------------------------------- */

START_TEST (test_vfs_parse_ls_lga_reorder)
{
    size_t filepos = 0;
    struct vfs_s_entry *ent1, *ent2, *ent3;
    int i;

    vfs_parse_ls_lga_init();

    ent1 = vfs_s_generate_entry (&vfs_test_ops1, NULL, vfs_root_inode, 0);
    i = ent1->ino->st.st_nlink;
    if (! vfs_parse_ls_lga ("drwxrwxr-x   10 500      500          4096 Jun 23 17:09      build_root1",
    &ent1->ino->st, &ent1->name, &ent1->ino->linkname, &filepos))
    {
        fail ("An error occured while parse ls output");
        return;
    }
    vfs_s_store_filename_leading_spaces (ent1, filepos);
    vfs_s_insert_entry (&vfs_test_ops1, vfs_root_inode, ent1);


    ent2 = vfs_s_generate_entry (&vfs_test_ops1, NULL, vfs_root_inode, 0);
    i = ent2->ino->st.st_nlink;
    if (! vfs_parse_ls_lga ("drwxrwxr-x   10 500      500          4096 Jun 23 17:09    build_root2",
    &ent2->ino->st, &ent2->name, &ent2->ino->linkname, &filepos))
    {
        fail ("An error occured while parse ls output");
        return;
    }
    vfs_s_store_filename_leading_spaces (ent2, filepos);
    vfs_s_insert_entry (&vfs_test_ops1, vfs_root_inode, ent2);

    ent3 = vfs_s_generate_entry (&vfs_test_ops1, NULL, vfs_root_inode, 0);
    i = ent3->ino->st.st_nlink;
    if (! vfs_parse_ls_lga ("drwxrwxr-x   10 500      500          4096 Jun 23 17:09 ..",
    &ent3->ino->st, &ent3->name, &ent3->ino->linkname, &filepos))
    {
        fail ("An error occured while parse ls output");
        return;
    }
    vfs_s_store_filename_leading_spaces (ent3, filepos);
    vfs_s_insert_entry (&vfs_test_ops1, vfs_root_inode, ent3);

    vfs_s_normalize_filename_leading_spaces (vfs_root_inode, vfs_parse_ls_lga_get_final_spaces ());

    fail_unless(strcmp(ent1->name, "     build_root1") == 0, "\nactual '%s'\nnot equal to '%s'\n", ent1->name, "     build_root1");
    fail_unless(strcmp(ent2->name, "   build_root2") == 0, "\nactual '%s'\nnot equal to '%s'\n", ent2->name, "   build_root2");
}
END_TEST

/* --------------------------------------------------------------------------------------------- */
#define parce_one_line(ent_index, ls_output) {\
    ent[ent_index] = vfs_s_generate_entry (&vfs_test_ops1, NULL, vfs_root_inode, 0);\
    if (! vfs_parse_ls_lga (ls_output,\
    &ent[ent_index]->ino->st, &ent[ent_index]->name, &ent[ent_index]->ino->linkname, &filepos))\
    {\
        fail ("An error occured while parse ls output");\
        return;\
    }\
    vfs_s_store_filename_leading_spaces (ent[ent_index], filepos);\
    vfs_s_insert_entry (&vfs_test_ops1, vfs_root_inode, ent[ent_index]);\
    \
}
#define fail_unless_ent(ent_index, etalon_str){\
    fail_unless(\
        strcmp(ent[ent_index]->name, etalon_str) == 0,\
        "\nactual '%s'\nnot equal to '%s'\n", ent[ent_index]->name, etalon_str\
    );\
}

START_TEST (test_vfs_parse_ls_lga_unaligned)
{
    size_t filepos = 0;
    struct vfs_s_entry *ent[4];

    vfs_parse_ls_lga_init();

    parce_one_line(0, "drwxrwxr-x   10 500      500          4096 Jun 23 17:09  build_root1");
    parce_one_line(1, "drwxrwxr-x   10 500     500         4096 Jun 23 17:09     build_root2");
    parce_one_line(2, "drwxrwxr-x 10 500 500 4096 Jun 23 17:09  ..");
    parce_one_line(3, "drwxrwxr-x      10   500        500             4096   Jun   23   17:09   build_root 0");

    vfs_s_normalize_filename_leading_spaces (vfs_root_inode, vfs_parse_ls_lga_get_final_spaces ());

    fail_unless_ent(0, "build_root1");
    fail_unless_ent(1, "   build_root2");
    fail_unless_ent(3, " build_root 0");

}
END_TEST

/* --------------------------------------------------------------------------------------------- */

int
main (void)
{
    int number_failed;

    Suite *s = suite_create (TEST_SUITE_NAME);
    TCase *tc_core = tcase_create ("Core");
    SRunner *sr;

    tcase_add_checked_fixture (tc_core, setup, teardown);

    /* Add new tests here: *************** */
    tcase_add_test (tc_core, test_vfs_parse_ls_lga);
    tcase_add_test (tc_core, test_vfs_parse_ls_lga_reorder);
    tcase_add_test (tc_core, test_vfs_parse_ls_lga_unaligned);
    /* *********************************** */

    suite_add_tcase (s, tc_core);
    sr = srunner_create (s);
    srunner_set_log (sr, "vfs_parse_ls_lga.log");
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? 0 : 1;
}

/* --------------------------------------------------------------------------------------------- */
