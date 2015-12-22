#define MODULE_NAME "reset"
#define CORE_PRIVATE
#include <ap_config.h>
#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_log.h>
#include <zend.h>
#include <zend_qsort.h>
#include <zend_API.h>
#include <zend_ini.h>
#include <zend_alloc.h>
#include <zend_operators.h>

#if AP_SERVER_MINORVERSION_NUMBER == 2
#define APACHE_22
#endif

typedef struct {
        unsigned long enable:1;
        apr_table_t   *php_ini;
        char          *admin;
        char          *docroot;
        int           nheaders;
#ifdef MOD_RUID2
        char          *ruid_uid;
#endif
} reset_config;

#ifdef MOD_RUID2
#define RUID_MAXGROUPS        8
typedef struct
{
        int8_t ruid_mode;
        uid_t ruid_uid;
        gid_t ruid_gid;
        gid_t groups[RUID_MAXGROUPS];
        int groupsnr;
} ruid_dir_config_t;
#endif
