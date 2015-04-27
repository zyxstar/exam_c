#ifndef HS_MYARG_H
#define HS_MYARG_H

typedef char *myva_list;

#if 0
#define argoffetof(TYPE) \
	((sizeof(TYPE) + 4 - 1) / 4 * 4)
#else
#define argoffetof(TYPE) \
	((sizeof(TYPE) + 4 - 1) & ~(4 - 1))
#endif

#define myva_start(AP, LAST) \
	((AP) = (myva_list)&(LAST) + argoffetof(LAST))

#define myva_arg(AP, TYPE) \
	((AP) += argoffetof(TYPE), *(TYPE *)((AP) - argoffetof(TYPE)))

#define myva_end(AP)

#endif	/* HS_MYARG_H */
