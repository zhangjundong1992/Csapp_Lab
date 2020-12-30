#ifndef CACHE_TOOLS
#define CACHE_TOOLS

#include "utilies.h"

#define bitWidth 64

typedef struct AddrInfo
{
    int r, s, b;
} AddrInfo;

typedef struct CacheInfo
{
    int S, E, B;
} CacheInfo;

typedef struct CacheLine
{
    int val;
    int tag;
    int stamp;

} CacheLine, *CachePtr;

void initCache(int s, int E, int b);

void visit(unsigned long address, BehavrInfo *info);

void freeCacke();

#endif