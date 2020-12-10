#ifndef _TAVL_QUEUE_H_
#define _TAVL_QUEUE_H_

#include "TAvl.h"

typedef struct TAvlQueue {
    TAvl *tree;
    struct TAvlQueue *next;
} TAvlQueue;

void QueuePush(TAvlQueue **queue, TAvl *tree);
TAvl *QueuePop(TAvlQueue **queue);

#endif
