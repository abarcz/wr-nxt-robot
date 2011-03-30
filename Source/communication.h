#include "debug.h"

#define print_num(y,v) NumOut(0,y,v)

#define print_text(y,s) TextOut(0,y,s)

/* prints "s: v" in the line y, where s is a string and v - a number */
void print_val(int y,string s,long v)
{
	string ss=NumToStr(v);
	TextOut(0,y,StrCat(s,": ",ss));
}

