#include "TRK/trk.h"

extern void OSReport(const char*);

BOOL usr_puts_serial(const char* putString) {
    BOOL res = FALSE;
    char tstring;
    char buff[2];
    int con;
    while ((res == FALSE) && (tstring = *putString++) != 0) {
        con = GetTRKConnected();
        buff[0] = tstring;
        buff[1] = '\0';
        SetTRKConnected(0);
        OSReport(buff);
        SetTRKConnected(con);
        res = FALSE;
    }
    return res;
}

void usr_put_initialize() {
}
