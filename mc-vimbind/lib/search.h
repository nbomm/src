#ifndef MC__SEARCH_H
#define MC__SEARCH_H

#include <config.h>

#include "lib/global.h"         /* <glib.h> */

#include <sys/types.h>

#ifdef SEARCH_TYPE_PCRE
#include <pcre.h>
#endif

/*** typedefs(not structures) and defined constants **********************************************/

typedef int (*mc_search_fn) (const void *user_data, gsize char_offset);

#define MC_SEARCH__NUM_REPLACE_ARGS 64

#ifdef SEARCH_TYPE_GLIB
#define mc_search_matchinfo_t GMatchInfo
#else
#define mc_search_matchinfo_t pcre_extra
#endif

/*** enums ***************************************************************************************/

typedef enum
{
    MC_SEARCH_E_OK,
    MC_SEARCH_E_INPUT,
    MC_SEARCH_E_REGEX_COMPILE,
    MC_SEARCH_E_REGEX,
    MC_SEARCH_E_REGEX_REPLACE,
    MC_SEARCH_E_NOTFOUND
} mc_search_error_t;

typedef enum
{
    MC_SEARCH_T_NORMAL,
    MC_SEARCH_T_REGEX,
    MC_SEARCH_T_HEX,
    MC_SEARCH_T_GLOB
} mc_search_type_t;

typedef enum
{
    MC_SEARCH_CB_OK = 0,
    MC_SEARCH_CB_INVALID = -1,
    MC_SEARCH_CB_ABORT = -2,
    MC_SEARCH_CB_SKIP = -3
} mc_search_cbret_t;


/*** structures declarations (and typedefs of structures)*****************************************/

typedef struct mc_search_struct
{
    /* public input data */

    /* search in all charsets */
    gboolean is_all_charsets;

    /* case sensitive search */
    gboolean is_case_sensitive;

    /* search only once.  Is this for replace? */
    gboolean is_once_only;

    /* search only whole words (from begin to end). Used only with NORMAL search type */
    gboolean whole_words;

    /* search entire string (from begin to end). Used only with GLOB search type */
    gboolean is_entire_line;

    /* function, used for getting data. NULL if not used */
    mc_search_fn search_fn;

    /* function, used for updatin current search status. NULL if not used */
    mc_search_fn update_fn;

    /* type of search */
    mc_search_type_t search_type;


    /* public output data */

    /* some data for normal */
    off_t normal_offset;

    off_t start_buffer;
    /* some data for regexp */
    int num_results;
    gboolean is_utf8;
    mc_search_matchinfo_t *regex_match_info;
    GString *regex_buffer;
#ifdef SEARCH_TYPE_PCRE
    int iovector[MC_SEARCH__NUM_REPLACE_ARGS * 2];
#endif                          /* SEARCH_TYPE_PCRE */

    /* private data */

    /* prepared conditions */
    GPtrArray *conditions;

    /* original search string */
    gchar *original;
    gsize original_len;

    /* error code after search */
    mc_search_error_t error;
    gchar *error_str;
} mc_search_t;

typedef struct mc_search_type_str_struct
{
    const char *str;
    mc_search_type_t type;
} mc_search_type_str_t;

/*** global variables defined in .c file *********************************************************/

/*** declarations of public functions ************************************************************/

mc_search_t *mc_search_new (const gchar * original, gsize original_len);

void mc_search_free (mc_search_t * lc_mc_search);

gboolean mc_search_prepare (mc_search_t * mc_search);

gboolean mc_search_run (mc_search_t * mc_search, const void *user_data, gsize start_search,
                        gsize end_search, gsize * found_len);

gboolean mc_search_is_type_avail (mc_search_type_t);

const mc_search_type_str_t *mc_search_types_list_get (size_t * num);

GString *mc_search_prepare_replace_str (mc_search_t * mc_search, GString * replace_str);
char *mc_search_prepare_replace_str2 (mc_search_t *, char *);

gboolean mc_search_is_fixed_search_str (mc_search_t *);

gchar **mc_search_get_types_strings_array (size_t * num);

gboolean mc_search (const gchar *, const gchar *, mc_search_type_t);

int mc_search_getstart_result_by_num (mc_search_t *, int);
int mc_search_getend_result_by_num (mc_search_t *, int);

#endif