/* avg_tab - a FIFO queue for storing AVG_NUM uint values and getting 
 * their averaged value
 */

#include "debug.h"

#define AVG_NUM 	3				// size of avg_tab
#define AVG_INVAL 	999				// invalid value of avg_tab element

#ifndef NXC_COMPILE					// for GCC
	#include <stdio.h>
	#define AVG_TAB_REF avg_tab[]
	#define M_START int
	#define M_END return 0
#endif

#ifdef NXC_COMPILE					// for NXC
	#define AVG_TAB_REF &avg_tab[]	
	#define M_START task
	#define M_END ;
#endif

typedef unsigned int AVG_EL;		// type of data used in avg_tab

/* add 'new' as a new value to the FIFO AVG_TAB_REF, drop oldest val */
void avg_append(AVG_EL AVG_TAB_REF, AVG_EL new)
{
	int i;
	for (i=1;i<AVG_NUM;i++)
	{
		avg_tab[i-1] = avg_tab[i];
	}
	avg_tab[AVG_NUM-1] = new;
}

/* initializes AVG_TAB_REF with AVG_INVAL values */
void avg_init(AVG_EL AVG_TAB_REF)
{
	int i;
	for(i=0;i<AVG_NUM;i++)
		avg_tab[i] = AVG_INVAL;
}

/* gets the averaged value from AVG_TAB_REF		*/
AVG_EL avg_getval(AVG_EL AVG_TAB_REF)
{
	unsigned long sum = 0;
	int val_num = 0;
	int i;
	for(i=0;i<AVG_NUM;i++)
		if(avg_tab[i] != AVG_INVAL)
		{
			sum += avg_tab[i];
			val_num++;
		}
	if(val_num != 0)
		return sum / val_num;
	else
		return AVG_INVAL;
}
/*
M_START main ()
{
	AVG_EL a[AVG_NUM];
	AVG_EL e;
	avg_init(a);
	avg_append(a,120);
	avg_append(a,110);
	avg_append(a,100);
	avg_append(a,110);
	e = avg_getval(a);
	
	printf("%i\n", e);

	M_END;
}*/

