#ifndef _MSL_COMMON_ANSI_FP_H
#define _MSL_COMMON_ANSI_FP_H

#define SIGDIGLEN 36

typedef struct decimal {
    char sign;
    char unk1;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[36];
        unsigned char unk41;
    } sig;
} decimal;

typedef struct decform {
    char style;
    char unk1;
    short digits;
} decform;

void __num2dec(const decform*, double, decimal*);
void __num2dec_internal(decimal*, double);
void __two_exp(decimal*, short);
void __str2dec(decimal*, const char*, short);
void __timesdec(decimal*, const decimal*, const decimal*);
void __ull2dec(decimal*, unsigned long long);

#endif
