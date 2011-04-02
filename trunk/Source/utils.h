/* 
 * Useful functions 
 */

#ifndef NXC_MYUTILS
#define NXC_MYUTILS

int min_i (int a, int b)
{
	if (a<b)
		return a;
	else 
		return b;
}

int max_i (int a, int b)
{
	if (a>b)
		return a;
	else 
		return b;
}

int abs_i (int a)
{
	if (a < 0)
		return -a;
	else 
		return a;
}

#endif
