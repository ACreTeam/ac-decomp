#ifndef _JSYSTEM_JUT_JUTDBPRINT_H
#define _JSYSTEM_JUT_JUTDBPRINT_H

void* JC_JUTDbPrint_getManager(void);    
void JC_JUTDbPrint_setVisible(void*, int);  // I know these are C++ but these were used to match a c function so I'll fix these when I need them or fix zurumode update.

void JUTReport(int x, int y, int show_count, const char* fmt, ...);

#endif