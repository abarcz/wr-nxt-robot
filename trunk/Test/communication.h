#include "debug.h"

/* prints "s: v" in the line y, where s is a string and v - a number */
#define print_val(y,s,v) TextOut(0,y,StrCat(s,": ",NumToStr(v)))

#define print_num(y,v) NumOut(0,y,v)

#define print_text(y,s) TextOut(0,y,s)
