/* median_tab - a structure for keeping sensor data and getting 
 * a median from them
 */
 
#include "debug.h"

#define MEDIAN_NUM 3		// size of median_tab
#define MEDIAN_INVAL 999	// invalid value for median_tab element MUST BE BIG!
#define MEDIAN_EL unsigned int		// type of data used in median_tab

#ifndef NXC_COMPILE					// for GCC
	#include <stdio.h>
	#define MEDIAN_TAB_REF median_tab[]
	#define M_START int
	#define M_END return 0
#endif

#ifdef NXC_COMPILE					// for NXC
	#define MEDIAN_TAB_REF &median_tab[]	
	#define M_START task
	#define M_END ;
#endif



MEDIAN_EL ui_min(MEDIAN_EL a, MEDIAN_EL b)
{
	if (a > b)
		return b;
	else
		return a;
}

/* add 'new' as a new value to the FIFO MEDIAN_TAB_REF, drop oldest val */
void median_append(MEDIAN_EL MEDIAN_TAB_REF, MEDIAN_EL new)
{
	int i;
	for (i=1;i<MEDIAN_NUM;i++)
	{
		median_tab[i-1] = median_tab[i];
	}
	median_tab[MEDIAN_NUM-1] = new;
}

/* initializes MEDIAN_TAB_REF with MEDIAN_INVAL values */
void median_init(MEDIAN_EL MEDIAN_TAB_REF)
{
	int i;
	for(i=0;i<MEDIAN_NUM;i++)
		median_tab[i] = MEDIAN_INVAL;
}

/* gets the median value from MEDIAN_TAB_REF		*/
MEDIAN_EL median_getval(MEDIAN_EL MEDIAN_TAB_REF)
{
	int round = 0;	// counts the sort rounds
	unsigned int max_rounds;	// how many sort rounds should we do
	int med_1;
	int med_2;		// two median elements in case MEDIAN_NUM is even
	int smallest_found;	// smallest element found in current round
	int smallest_index;
	// flags, showing if element i has already been considered in the sort alg.
	char used[MEDIAN_NUM];	
	int i;
	int valid = 0;
	
	// count valid elements
	for (i=0;i<MEDIAN_NUM;i++)
		if (median_tab[i] != MEDIAN_INVAL)
			valid++;
	
	if (valid == 0)
		return MEDIAN_INVAL;
		
	if (valid == 1)
		for (i=0;i<MEDIAN_NUM;i++)
			if (median_tab[i] != MEDIAN_INVAL)
				return median_tab[i];
	
	
	// mark all elements unused
	for (i=0;i<MEDIAN_NUM;i++)
		used[i] = 0;
		
	max_rounds = ui_min(valid, MEDIAN_NUM / 2 + 1); // works for odd and even as well
	
	for (round=0; round<max_rounds; round++)
	{
		smallest_found = MEDIAN_INVAL;
		smallest_index = MEDIAN_INVAL;
		for (i=0;i<MEDIAN_NUM;i++)
		{
			if (used[i] == 0)
			{
				if (median_tab[i] == MEDIAN_INVAL)
					used[i] = 1;
				else if (median_tab[i] < smallest_found)
				{
					smallest_found = median_tab[i];
					smallest_index = i;
				}
			}
		}
		used[smallest_index] = 1;
		med_1 = med_2;
		med_2 = smallest_found;
	}
	if (MEDIAN_NUM % 2 == 0) //even => average
		return (med_1 + med_2) / 2;
	else 
		return med_2;
}
