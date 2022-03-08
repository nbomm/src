/*
   lib/vfs - vfs_path_t serialize/deserialize functions

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

#include "lib/global.c"

#ifndef HAVE_CHARSET
#define HAVE_CHARSET 1
#endif

#include "lib/charsets.h"

#include "lib/strutil.h"
#include "lib/vfs/xdirentry.h"
#include "lib/vfs/path.h"

#include "src/vfs/local/local.c"


struct vfs_s_subclass test_subclass1, test_subclass2, test_subclass3;
struct vfs_class vfs_test_ops1, vfs_test_ops2, vfs_test_ops3;

static void
setup (void)
{

    str_init_strings (NULL);

    vfs_init ();
    init_localfs ();
    vfs_setup_work_dir ();


    test_subclass1.flags = VFS_S_REMOTE;
    vfs_s_init_class (&vfs_test_ops1, &test_subclass1);

    vfs_test_ops1.name = "testfs1";
    vfs_test_ops1.flags = VFSF_NOLINKS;
    vfs_test_ops1.prefix = "test1";
    vfs_register_class (&vfs_test_ops1);

    vfs_s_init_class (&vfs_test_ops2, &test_subclass2);
    vfs_test_ops2.name = "testfs2";
    vfs_test_ops2.prefix = "test2";
    vfs_register_class (&vfs_test_ops2);

    vfs_s_init_class (&vfs_test_ops3, &test_subclass3);
    vfs_test_ops3.name = "testfs3";
    vfs_test_ops3.prefix = "test3";
    vfs_register_class (&vfs_test_ops3);

    mc_global.sysconfig_dir = (char *) TEST_SHARE_DIR;
    load_codepages_list ();
}

static void
teardown (void)
{
    free_codepages_list ();

    vfs_shut ();
    str_uninit_strings ();
}

/* --------------------------------------------------------------------------------------------- */
#define ETALON_PATH_STR "/local/path/#test1:user:pass@some.host:12345/bla-bla/some/path/#test2/#enc:KOI8-R/bla-bla/some/path#test3/111/22/33"
#define ETALON_PATH_URL_STR "/local/path/test1://user:pass@some.host:12345/bla-bla/some/path/test2://#enc:KOI8-R/bla-bla/some/path/test3://111/22/33"
#define ETALON_SERIALIZED_PATH \
    "g14:path-element-0" \
        "p4:pathv12:/local/path/" \
        "p10:class-namev7:localfs" \
    "g14:path-element-1" \
        "p4:pathv18:bla-bla/some/path/" \
        "p10:class-namev7:testfs1" \
        "p10:vfs_prefixv5:test1" \
        "p4:userv4:user" \
        "p8:passwordv4:pass" \
        "p4:hostv9:some.host" \
        "p4:portv5:12345" \
    "g14:path-element-2" \
        "p4:pathv17:bla-bla/some/path" \
        "p10:class-namev7:testfs2" \
        "p8:encodingv6:KOI8-R" \
        "p10:vfs_prefixv5:test2" \
    "g14:path-element-3" \
        "p4:pathv9:111/22/33" \
        "p10:class-namev7:testfs3" \
        "p10:vfs_prefixv5:test3"

START_TEST (test_path_serialize_deserialize)
{
    vfs_path_t *vpath;
    char *serialized_vpath;
    GError *error = NULL;

    vpath = vfs_path_from_str_flags (ETALON_PATH_STR, VPF_USE_DEPRECATED_PARSER);
    serialized_vpath = vfs_path_serialize (vpath, &error);
    vfs_path_free (vpath);

    if (serialized_vpath == NULL)
    {
        fail ("serialized_vpath is NULL!\nError code is '%d'; error message is '%s'", error->code, error->message);
        g_clear_error (&error);
        return;
    }

    fail_unless (
        strcmp (serialized_vpath, ETALON_SERIALIZED_PATH ) == 0,
        "\nserialized_vpath    (%s)\nnot equal to etalon (%s)", serialized_vpath, ETALON_SERIALIZED_PATH
    );

    vpath = vfs_path_deserialize (serialized_vpath, &error);
    g_free (serialized_vpath);

    if (vpath == NULL)
    {
        fail ("vpath is NULL!\nError code is '%d'; error message is '%s'", error->code, error->message);
        g_clear_error (&error);
        return;
    }

    serialized_vpath = vfs_path_to_str (vpath);
    fail_unless (
        strcmp (serialized_vpath, ETALON_PATH_URL_STR) == 0,
        "\ndeserialized path   (%s)\nnot equal to etalon (%s)", serialized_vpath, ETALON_PATH_URL_STR
    );
    vfs_path_free(vpath);
    g_free(serialized_vpath);

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
    tcase_add_test (tc_core, test_path_serialize_deserialize);
    /* *********************************** */

    suite_add_tcase (s, tc_core);
    sr = srunner_create (s);
    srunner_set_log (sr, "path_serialize.log");
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? 0 : 1;
}

/* --------------------------------------------------------------------------------------------- */
