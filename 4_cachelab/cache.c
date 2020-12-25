#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cache.h"

AddrInfo addrInfo;

AddrInfo getAddrInfo()
{
    return addrInfo;
}

void setAddrInfo(int r, int s, int b)
{
    addrInfo.r = r;
    addrInfo.s = s;
    addrInfo.b = b;
}

CacheInfo cacheInfo;

CacheInfo getCacheInfo()
{
    return cacheInfo;
}

void setCacheInfo(int S, int E, int B)
{
    cacheInfo.S = S;
    cacheInfo.E = E;
    cacheInfo.B = B;

    printf("cacheInfo(S,E,B) is (%d,%d,%d)\n", S, E, B);
}

CachePtr cache;

void initCache(int s, int E, int b)
{
    printf("arg(s,E,b) is (%d,%d,%d)\n", s, E, b);
    /* 初始化缓存元组 */
    setAddrInfo(bitWidth - s - b, s, b);
    setCacheInfo((int)pow(2.0, s), E, (int)pow(2.0, b));
    int num = cacheInfo.S * cacheInfo.E;

    /* 分配内存并初始化 */
    cache = (CachePtr)malloc(num * sizeof(CacheLine));

    for (int i = 0; i < num; i++)
    {
        cache[i].val = 0;
        cache[i].stamp = 0;
    }
}

void visit(unsigned long address, BehavrInfo *info)
{

    /* 切分地址的r,s,b位 */
    int r = address >> (addrInfo.s + addrInfo.b);
    int s = address << addrInfo.r >> (addrInfo.r + addrInfo.b);

    // printf("addr is %lx,s is %d,r is %d\n", address, s, r);

    /* 更新时间戳 */
    for (int i = 0; i < cacheInfo.S * cacheInfo.E; i++)
    {
        // printf("cache[%d](val,tag,stamp) is (%d,%d,%d)\n", i, cache[i].val, cache[i].tag, cache[i].stamp);
        cache[i].stamp++;
    }

    /* 访问缓存 */
    /* 命中的情况 */
    int start_index = s * cacheInfo.E;
    int end_index = start_index + cacheInfo.E;

    for (int i = start_index; i < end_index; i++)
    {
        if (cache[i].val == 1 && cache[i].tag == r)
        {
            cache[i].stamp = 0;
            (*info).hits++;
            puts("hit");
            return;
        }
    }

    /* 未命中但是不需要置换的情况 */
    for (int i = start_index; i < end_index; i++)
    {
        if (cache[i].val == 0)
        {
            cache[i].val = 1;
            cache[i].tag = r;
            cache[i].stamp = 0;
            (*info).misses++;
            puts("miss");
            return;
        }
    }

    /* 未命中但是需要置换的情况 */
    int index = start_index, maxStamp = cache[s * cacheInfo.E].stamp;
    for (int i = start_index + 1; i < end_index; i++)
    {
        if (cache[i].stamp > maxStamp)
        {
            index = i;
            maxStamp = cache[i].stamp;
        }
    }

    cache[index].tag = r;
    cache[index].stamp = 0;
    (*info).misses++;
    (*info).evictions++;
    puts("miss and eviction");
}

void freeCacke()
{
    free(cache);
}