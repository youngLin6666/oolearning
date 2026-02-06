/* common.h */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FALSE = 0, TRUE = 1 } Boolean;

// 简单的错误处理宏
#define NEW(type) (type*)malloc(sizeof(type))

// 安全释放宏，防止悬垂指针
#define SAFE_FREE(ptr) do { if(ptr) { free(ptr); ptr = NULL; } } while(0)

#endif

