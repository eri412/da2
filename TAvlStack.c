#include <stdlib.h>
#include <stdio.h>

#include "TAvlStack.h"

TAvlStack *StackCreate() {
    TAvlStack *temp = malloc(sizeof(TAvlStack));
    if (temp == NULL) {
        perror("ERROR");
        return NULL;
    }
    temp->size = 0;
    temp->capacity = DEFAULT_CAPACITY;
    temp->buff = malloc(DEFAULT_CAPACITY * sizeof(TAvl *));
    if (temp->buff == NULL) {
        free(temp);
        perror("ERROR");
        return NULL;
    }
    return temp;
}

void StackDelete(TAvlStack *stack) {
    free(stack->buff);
    free(stack);
}

void StackGrow(TAvlStack *stack) {
    TAvl **temp = realloc(stack->buff, stack->capacity * sizeof(TAvl *) * CAPACITY_MULTIPLIER);
    if (temp == NULL) {
        perror("ERROR");
        return;
    }
    stack->buff = temp;
    stack->capacity *= CAPACITY_MULTIPLIER;
}

void StackPush(TAvlStack *stack, TAvl *tree) {
    if (tree == NULL) {
        return;
    }
    if (stack->size == stack->capacity) {
        StackGrow(stack);
    }
    stack->buff[stack->size] = tree;
    stack->size++;
}

TAvl *StackPop(TAvlStack *stack) {
    if (stack->size == 0) {
        return NULL;
    }
    stack->size--;
    return stack->buff[stack->size];
}