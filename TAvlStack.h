#ifndef _TAVL_STACK_H_
#define _TAVL_STACK_H_

#include "TAvl.h"

enum {DEFAULT_CAPACITY = 1024, CAPACITY_MULTIPLIER = 2};

typedef struct {
    size_t size;
    size_t capacity;
    TAvl **buff;
} TAvlStack;

TAvlStack *StackCreate();
void StackDelete(TAvlStack *stack);
void StackPush(TAvlStack *stack, TAvl *tree);
TAvl *StackPop(TAvlStack *stack);

#endif
