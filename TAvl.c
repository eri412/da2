#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "TAvl.h"
#include "TAvlQueue.h"

TAvl *NewNode(TAvl *parent, char *key, unsigned long long value) {
    TAvl *temp;
    if ((temp = malloc(sizeof(TAvl))) == NULL) {
        return NULL;
    }
    memset(temp->key, 0, MAX_KEY_LEN + 1);
    strcpy(temp->key, key);
    temp->value = value;
    temp->height = 1;
    temp->parent = parent;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

TAvl *DeleteNode(TAvl *iter, TAvl **root) {
    TAvl *res;
    if (iter->left == NULL || iter->right == NULL) {
        TAvl *father = iter->parent;
        TAvl *next;
        if (iter->left == NULL) {
            next = iter->right;
        }
        else {
            next = iter->left;
        }

        if (father == NULL) {
            *root = next;
        }
        else {
            if (father->left == iter) {
                father->left = next;
            }
            else {
                father->right = next;
            }
        }

        if (next != NULL) {
            next->parent = father;
        }
        res = iter->parent;
        free(iter);
        FixHeight(father);
    }
    else {
        TAvl *minKeyNode = iter->right;
        while (minKeyNode->left != NULL) {
            minKeyNode = minKeyNode->left;
        }
        strcpy(iter->key, minKeyNode->key);
        iter->value = minKeyNode->value;
        TAvl *minKeyNodeParent = minKeyNode->parent;
        if (minKeyNodeParent == iter) {
            iter->right = minKeyNode->right;
            if (minKeyNode->right != NULL) {
                minKeyNode->right->parent = iter;
            }
        }
        else {
            minKeyNodeParent->left = minKeyNode->right;
            if (minKeyNode->right != NULL) {
                minKeyNode->right->parent = minKeyNodeParent;
            }
        }
        res = minKeyNode->parent;
        free(minKeyNode);
        FixHeight(minKeyNodeParent);
    }
    return res;
}

int Height(TAvl *tree) {
    if (tree == NULL) {
        return 0;
    }
    return tree->height;
}

void FixHeight(TAvl *iter) {
    while (iter != NULL) {
        iter->height = MAX(Height(iter->left), Height(iter->right)) + 1;
        iter = iter->parent;
    }
}

int BalanceFactor(TAvl *tree) {
    if (tree == NULL) {
        return 0;
    }
    return Height(tree->right) - Height(tree->left);
}

void RightRotate(TAvl *z, TAvl **root) {
    TAvl *father = z->parent;
    TAvl *y = z->left;
    TAvl *t3 = y->right;
    if (father == NULL) {
        *root = y;
    }
    else if (father->left == z) {
        father->left = y;
    }
    else if (father->right == z) {
        father->right = y;
    }
    y->parent = father;
    y->right = z;
    z->parent = y;
    z->left = t3;
    if (t3 != NULL) {
        t3->parent = z;
    }
    FixHeight(z);
}

void LeftRotate(TAvl *z, TAvl **root) {
    TAvl *father = z->parent;
    TAvl *y = z->right;
    TAvl *t2 = y->left;
    if (father == NULL) {
        *root = y;
    }
    else if (father->left == z) {
        father->left = y;
    }
    else if (father->right == z) {
        father->right = y;
    }
    y->parent = father;
    y->left = z;
    z->parent = y;
    z->right = t2;
    if (t2 != NULL) {
        t2->parent = z;
    }
    FixHeight(z);
}

void BalanceInsertion(TAvl *iter, TAvl **root) {
    if (Height(*root) <= 2) {
        return;
    }
    TAvl *x = iter;
    TAvl *y = iter->parent;
    TAvl *z = y->parent;
    while (z != NULL) {
        if (BalanceFactor(z) == -2) {
            if (x == y->left) {
                RightRotate(z, root);
            }
            else {
                LeftRotate(y, root);
                RightRotate(z, root);
            }
            return;
        }
        else if (BalanceFactor(z) == 2) {
            if (x == y->right) {
                LeftRotate(z, root);
            }
            else {
                RightRotate(y, root);
                LeftRotate(z, root);
            }
            return;
        }
        x = y;
        y = z;
        z = z->parent;
    }
}

int Insert(TAvl **root, char *key, unsigned long long value) {
    for (size_t i = 0; i < strlen(key); ++i) {
        key[i] = tolower(key[i]);
    }
    if (*root == NULL) {
        *root = NewNode(NULL, key, value);
        if (*root == NULL) {
            return -1;
        }
        return 0;
    }
    TAvl *iter = *root;
    while (1) {
        if (strcmp(key, iter->key) < 0) {
            if (iter->left == NULL) {
                iter->left = NewNode(iter, key, value);
                if (iter->left == NULL) {
                    return -1;
                }
                FixHeight(iter);
                BalanceInsertion(iter->left, root);
                return 0;
            }
            else {
                iter = iter->left;
            }
        }
        else if (strcmp(key, iter->key) > 0) {
            if (iter->right == NULL) {
                iter->right = NewNode(iter, key, value);
                if (iter->right == NULL) {
                    return -1;
                }
                FixHeight(iter);
                BalanceInsertion(iter->right, root);
                return 0;
            }
            else {
                iter = iter->right;
            }
        }
        else {
            return 1;
        }
    }
}

void Print(TAvl *tree, int level) { 
    if (tree == NULL) {
        printf("\n");
        return;
    }  
    Print(tree->right, level + 1);
    for (int i = 0; i < level; ++i) {
        printf("\t");
    }
    printf("%s;%llu;\n", tree->key, tree->value);
    Print(tree->left, level + 1);
}

void InOrder(TAvl *tree) {
    if (tree == NULL) {
        return;
    }
    InOrder(tree->left);
    printf("%s ", tree->key);
    InOrder(tree->right);
}

void CheckIntegrity(TAvl *tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->parent != NULL) {
        if (tree->parent->left != tree && tree->parent->right != tree) {
            printf("Integrity broken\n");
        }
    }
    if (tree->left != NULL) {
        if (tree->left->parent != tree) {
            printf("Integrity broken\n");
        }
        CheckIntegrity(tree->left);
    }
    if (tree->right != NULL) {
        if (tree->right->parent != tree) {
            printf("Integrity broken\n");
        }
        CheckIntegrity(tree->right);
    }
}

unsigned long long *Find(TAvl *root, char *key) {
    for (size_t i = 0; i < strlen(key); ++i) {
        key[i] = tolower(key[i]);
    }
    if (root == NULL) {
        return NULL;
    }
    while (1) {
        if (strcmp(key, root->key) < 0) {
            if (root->left == NULL) {
                return NULL;
            }
            root = root->left;
        }
        else if (strcmp(key, root->key) > 0) {
            if (root->right == NULL) {
                return NULL;
            }
            root = root->right;
        }
        else {
            return &root->value;
        }
    }
}

void BalanceDeletion(TAvl *iter, TAvl **root) {
    if (Height(*root) <= 2) {
        return;
    }
    TAvl *z = iter;
    
    while (z != NULL) {
        if (BalanceFactor(z) == 2 || BalanceFactor(z) == -2) {
            TAvl *y;
            if (Height(z->left) >= Height(z->right)) {
                y = z->left;
            }
            else {
                y = z->right;
            }
            TAvl *x;
            if (Height(y->left) >= Height(y->right)) {
                x = y->left;
            }
            else {
                x = y->right;
            }
            if (BalanceFactor(z) == -2) {
                if (x == y->left) {
                    RightRotate(z, root);
                }
                else {
                    LeftRotate(y, root);
                    RightRotate(z, root);
                }
                return;
            }
            else if (BalanceFactor(z) == 2) {
                if (x == y->right) {
                    LeftRotate(z, root);
                }
                else {
                    RightRotate(y, root);
                    LeftRotate(z, root);
                }
                return;
            }
        }
        z = z->parent;
    }
}

int Delete(TAvl **root, char *key) {
    for (size_t i = 0; i < strlen(key); ++i) {
        key[i] = tolower(key[i]);
    }
    if (*root == NULL) {
        return 1;
    }
    TAvl *iter = *root;
    while (1) {
        if (strcmp(key, iter->key) < 0) {
            if (iter->left == NULL) {
                return 1;
            }
            iter = iter->left;
        }
        else if (strcmp(key, iter->key) > 0) {
            if (iter->right == NULL) {
                return 1;
            }
            iter = iter->right;
        }
        else {
            TAvl *res = DeleteNode(iter, root);
            BalanceDeletion(res, root);
            return 0;
        }
    }
}

void DeleteTree(TAvl *tree) {
    if (tree == NULL) {
        return;
    }
    DeleteTree(tree->left);
    DeleteTree(tree->right);
    free(tree);
}

void SaveWrite(TAvl *tree, FILE *fp) {
    fwrite(&tree->value, sizeof(tree->value), 1, fp);
    fwrite(tree->key, sizeof(char), MAX_KEY_LEN, fp);
}

int Save(TAvl *tree, char *fileName) {  
    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == NULL) {
        return -1;
    }
    TAvlQueue *queue = NULL;
    QueuePush(&queue, tree);
    TAvl *curr;
    while ((curr = QueuePop(&queue)) != NULL) {
        SaveWrite(curr, fp);
        QueuePush(&queue, curr->left);
        QueuePush(&queue, curr->right);
    }
    fclose(fp);

    return 0;
}

int Load(TAvl **tree, char *fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "rb")) == NULL) {
        return -1;
    }
    unsigned long long tempValue;
    char tempKey[MAX_KEY_LEN + 1];
    tempKey[MAX_KEY_LEN] = '\0';
    while (1) {
        tempValue = 0;
        memset(tempKey, 0, MAX_KEY_LEN * sizeof(char));
        int ch = fgetc(fp);
        if (ch == EOF) {
            fclose(fp);
            return 0;
        }
        else {
            ungetc(ch, fp);
        }
        size_t readed = fread(&tempValue, sizeof(tempValue), 1, fp);
        if (readed == 0) {
            fclose(fp);
            return 1;
        }
        readed = fread(tempKey, sizeof(char), MAX_KEY_LEN, fp);
        if (readed != MAX_KEY_LEN) {
            fclose(fp);
            return 1;
        }
        Insert(tree, tempKey, tempValue);
    }
}
