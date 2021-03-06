#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "jx_delog.h"

#define _chkPOSINFO(type) ((type)&_POS_INFOBITS)

static uint32_t inited = 0;
#define MSG_SIZE 4096

static uint32_t msgsize = MSG_SIZE;
static schar_t ms_buf[MSG_SIZE];
static pchar_t ms_msg = ms_buf;

#define _initMSG()          \
    do                      \
    {                       \
        ms_msg = ms_buf;    \
        ms_buf[0] = 0;      \
        msgsize = MSG_SIZE; \
    } while (0)

#define va_copy_statement(params, op, ...) \
    do                                     \
    {                                      \
        va_list _backup;                   \
        va_copy(_backup, params);          \
        va_end(params);                    \
        op(__VA_ARGS__);                   \
        va_copy(params, _backup);          \
        va_end(_backup);                   \
    } while (0)

#define _init_delog(params)                            \
    do                                                 \
    {                                                  \
        if (inited == 0)                               \
        {                                              \
            va_copy_statement(params, s_init_delog, ); \
        }                                              \
        _initMSG();                                    \
    } while (0)

static void s_init_delog(void)
{
    inited = 1;
    _pos_delog(_MAX_INFO_DELOG, "reg");
    return;
}

#define fmt_str(s, n, ...)                            \
    do                                                \
    {                                                 \
        int32_t __tlen = snprintf(s, n, __VA_ARGS__); \
        if (__tlen >= 0)                              \
        {                                             \
            s += __tlen;                              \
            n -= __tlen;                              \
        }                                             \
    } while (0)

#define getPosInfo(params)                                          \
    do                                                              \
    {                                                               \
        pchar_t __file, __func;                                     \
        uint32_t __line;                                            \
        _getva_S(__file, params);                                   \
        _getva_I(__line, params);                                   \
        _getva_S(__func, params);                                   \
        va_copy_statement(params,                                   \
                          fmt_str, ms_msg, msgsize, "[%s]<%s>(%d)", \
                          __file, __func, __line);                  \
    } while (0)

void _jx_delog(uint32_t type,...)
{
    va_list params;
    va_start(params, type);
    _init_delog(params);
    if (_chkPOSINFO(type))
    {
        getPosInfo(params);
    }

_jx_delog_END:
    va_end(params);
    printf("test only:%s\n", ms_msg);
    return;
}