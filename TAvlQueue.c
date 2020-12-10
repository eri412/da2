#include <stdlib.h>

#include "TAvlQueue.h"

void QueuePush(TAvlQueue **queue, TAvl *tree) {
    if (tree == NULL) {
        return;
    }
    TAvlQueue *temp = malloc(sizeof(TAvlQueue));
    temp->tree = tree;
    temp->next = *queue;
    *queue = temp;
}

TAvl *QueuePop(TAvlQueue **queue) {
    if (*queue == NULL) {
        return NULL;
    }
    TAvlQueue *iter = *queue;
    TAvlQueue *prev = iter;
    while (iter->next != NULL) {
        prev = iter;
        iter = iter->next;
    }
    TAvl *res = iter->tree;
    if (iter == prev) {
        *queue = NULL;
    }
    else {
        prev->next = NULL;
    }
    free(iter);
    return res;
}