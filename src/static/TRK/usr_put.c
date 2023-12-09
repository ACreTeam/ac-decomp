#include "TRK/usr_put.h"
#include "TRK/msghndlr.h"

extern void OSReport(const char*);

TRKResult usr_puts_serial(const char* putString){
    TRKResult res = 0;
    char tstring;
    char buff[2];
    int con;
    while ((res == 0) && (tstring = *putString++) != 0){
       con = GetTRKConnected();
       buff[0] = tstring;
       buff[1] = '\0';
       SetTRKConnected(0);
       OSReport(buff);
       SetTRKConnected(con);
       res = 0;
    }
    return res;
}

TRKResult usr_put_initialize(){

}