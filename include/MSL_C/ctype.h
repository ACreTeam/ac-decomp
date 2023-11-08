#ifndef _CTYPE_H
#define _CTYPE_H

#include "types.h"
#include "MSL_C/locale.h"
#include "MSL_C/ctype_api.h"

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(weak) int isalpha(int __c);
    __declspec(weak) int isdigit(int __c);
    __declspec(weak) int isspace(int __c);
    __declspec(weak) int isupper(int __c);
    __declspec(weak) int isxdigit(int __c);

    __declspec(weak) int tolower(int __c);
    __declspec(weak) int toupper(int __c);

    // added underscore to avoid naming conflicts
    inline int _isalpha(int c) { return (int)(__ctype_map[(u8)c] & __letter); }
    inline int _isdigit(int c) { return (int)(__ctype_map[(u8)c] & __digit); }
    inline int _isspace(int c) { return (int)(__ctype_map[(u8)c] & __whitespace); }
    inline int _isupper(int c) { return (int)(__ctype_map[(u8)c] & __upper_case); }
    inline int _isxdigit(int c) { return (int)(__ctype_map[(u8)c] & __hex_digit); }
    inline int _tolower(int c) { return (c == -1 ? -1 : (int)__lower_map[(u8)c]); }
    inline int _toupper(int c) { return (c == -1 ? -1 : (int)__upper_map[(u8)c]); }

#ifdef __cplusplus
}
#endif
#endif
