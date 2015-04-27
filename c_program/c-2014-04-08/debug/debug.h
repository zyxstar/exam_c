#ifndef HS_DEBUG_H
#define HS_DEBUG_H

#ifdef  DEBUG3
#ifndef DEBUG2
#define DEBUG2
#endif
#endif

#ifdef  DEBUG2
#ifndef DEBUG1
#define DEBUG1
#endif
#endif

#ifdef  DEBUG1
#ifndef DEBUG
#define DEBUG
#endif
#endif

#ifdef  DEBUG
#ifndef DEBUG1
#define DEBUG1
#endif
#endif

#ifdef DEBUG1
#define debug1(...) printf(__VA_ARGS__)
#else
#define debug1(...)
#endif

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

#ifdef DEBUG2
#define debug2(...) printf(__VA_ARGS__)
#else
#define debug2(...)
#endif

#ifdef DEBUG3
#define debug3(...) printf(__VA_ARGS__)
#else
#define debug3(...)
#endif

#endif	/* HS_DEBUG_H */
