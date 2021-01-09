#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cache.h"
#include "cachelab.h"
#include "utilies.h"

#define lineLength 100 /* 按行读取文件时，每行的字符缓存长度 */

void printUsage();

int main(int argc, char *argv[]) {
    // 1 、解析参数,分配内存模拟缓存
    int opt = 0;
    int s = 0, E = 0, b = 0;
    char path[lineLength];

    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                printUsage();
                return 0;
            case 'v':
                /* 暂时不做处理 */
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(path, optarg);
                break;
            default:
                printf("argc parse err");
                return 0;
        }
    }

    initCache(s, E, b);

    // 2、读文件，模拟缓存读写
    BehavrInfo behavrInfo;
    char handle;
    unsigned long addr;
    int width;

    FILE *fp = fopen(path, "r");

    while (fscanf(fp, "%c %lx,%d", &handle, &addr, &width) != EOF) {
        // printf("handle is %c,addr is %lx\n", handle, addr);
        switch (handle) {
            case 'L':
            case 'S':
                visit(addr, &behavrInfo);
                break;
            case 'M':
                visit(addr, &behavrInfo);
                visit(addr, &behavrInfo);
                break;
            case 'I':
                /* I指令不做处理 */
                break;
            default:
                break;
        }
    }

    fclose(fp);
    freeCacke();

    printSummary(behavrInfo.hits, behavrInfo.misses, behavrInfo.evictions);
    return 0;
}

void printUsage() { /* 打印帮助信息 */
    FILE *fp = NULL;
    char buff[lineLength];

    fp = fopen("UsageTxt", "r");

    if (fp == NULL) {
        printf("file does not exit!\n");
        fclose(fp);
        return;
    }

    while (fgets(buff, lineLength, fp) != NULL) {
        puts(buff);
    }

    fclose(fp);
}
