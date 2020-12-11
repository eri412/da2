#ifndef _TAVL_H_
#define _TAVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

enum {MAX_KEY_LEN = 256};
enum {BUFSIZ_MULTIPLIER = 2};

typedef struct TAvl {
    unsigned long long value;
    int height;
    char key[MAX_KEY_LEN + 1];
    struct TAvl *parent;
    struct TAvl *left;
    struct TAvl *right;
} TAvl;

TAvl *NewEmptyNode(TAvl *parent);
TAvl *NewNode(TAvl *parent, char *key, unsigned long long value);
TAvl *DeleteNode(TAvl *iter, TAvl **root);
int Height(TAvl *tree);
void FixHeight(TAvl *iter);
int BalanceFactor(TAvl *tree);
void RightRotate(TAvl *z, TAvl **root);
void LeftRotate(TAvl *z, TAvl **root);
void BalanceInsertion(TAvl *iter, TAvl **root);
int Insert(TAvl **root, char *key, unsigned long long value);
void Print(TAvl *tree, int level);
void InOrder(TAvl *tree);
void CheckIntegrity(TAvl *tree);
unsigned long long *Find(TAvl *root, char *key);
void BalanceDeletion(TAvl *iter, TAvl **root);
int Delete(TAvl **root, char *key);
void DeleteTree(TAvl *tree);
void SaveWrite(TAvl *tree, FILE *fp);
int Save(TAvl *tree, char *fileName);
int Load(TAvl **tree, char *fileName);

#endif
