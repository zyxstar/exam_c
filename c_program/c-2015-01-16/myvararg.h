#ifndef HS_MYVARARG_H
#define HS_MYVARARG_H

#define myva_start(p, last) (p = (char *)(&last + 1))

#define myva_arg(p, type) (p += sizeof(type), *(type *)(p - sizeof(type)))

#endif	/* HS_MYVARARG_H */
