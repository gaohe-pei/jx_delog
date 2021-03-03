#include <stdio.h>
#include <string.h>
#include "gh_types.h"
#include "jx_delog.h"

#define _OPENFILE(f, name, mode, _label_END) \
    do                                       \
    {                                        \
        if ((f = fopen(name, mode)) == 0)    \
        {                                    \
            goto _label_END;                 \
        }                                    \
    } while (0)

#define _CLOSEFILE(f)  \
    do                 \
    {                  \
        if (f)         \
        {              \
            fclose(f); \
            f = 0;     \
        }              \
    } while (0)

int32_t main(int32_t argc, pchar_t argv[])
{
    //init_delog();
    FILE *f = 0;
    _OPENFILE(f, "test", "wb", _main_END);
    fwrite("test info\n", 1, strlen("test info\n"), f);
_main_END:
    _CLOSEFILE(f);
    return 0;
}