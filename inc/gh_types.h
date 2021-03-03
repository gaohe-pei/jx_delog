#ifndef _GH_TYPES_H
#define _GH_TYPES_H

typedef signed char schar_t;
typedef unsigned char uchar_t;
typedef char *pchar_t;

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

#define _getva_T_(P, params, _T_)     \
    do                                \
    {                                 \
        P = (_T_)va_arg(params, _T_); \
    } while (0)
#define _getva_S(s, params) _getva_T_(s, params, pchar_t)
#define _getva_I(i, params) _getva_T_(i, params, uint32_t)

#endif /* _GH_TYPES_H */