/* global defines useful for debugging in GCC */

#ifndef NXC_DEBUG
#define NXC_DEBUG

#define NXC_COMPILE 0				// comment this when using GCC

#ifndef NXC_COMPILE					// for GCC
	#define M_START int
	#define M_END return 0
#endif

#ifdef NXC_COMPILE					// for NXC
	#define M_START task
	#define M_END ;
#endif


#endif
