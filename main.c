#include <ctype.h>
#include <string.h>

#include "TAvl.h"

enum {MAX_INPUT_LEN = 512};

int main() {
    char input[MAX_INPUT_LEN + 1];
    TAvl *tree = NULL;
    while (fgets(input, MAX_INPUT_LEN + 1, stdin) != NULL) {
        char dup[MAX_INPUT_LEN + 2];
        strcpy(dup + 1, input);
        dup[0] = '\0';
        size_t len = strlen(input);
        int argc = 0;
        for (size_t i = 1; i < len; ++i) {
            if (!isspace(dup[i]) && isspace(dup[i+1])) {
                ++argc;
            }
        }
        char *argv[argc];
        int cur = 0;
        for (size_t i = 1; i < len + 1; ++i) {
            if (isspace(dup[i])) {
                dup[i] = '\0';
            }
            else if (dup[i-1] == '\0') {
                argv[cur] = &dup[i];
                ++cur;
            }
        }

        if (argc == 0) {
            continue;
        }

        if (strcmp(argv[0], "+") == 0) {
            if (argc != 3) {
                printf("Wrong number of arguments, should be 3\n");
                continue;
            }
            int error = Insert(&tree, argv[1], strtoull(argv[2], NULL, 10));
            if (error == 1) {
                printf("Exist\n");
            }
            else if (error == -1) {
                perror("ERROR");
            }
            else {
                printf("OK\n");
            }
        }
        else if (strcmp(argv[0], "-") == 0) {
            if (argc != 2) {
                printf("Wrong number of arguments, should be 2\n");
                continue;
            }
            int error = Delete(&tree, argv[1]);
            if (error) {
                printf("NoSuchWord\n");
            }
            else {
                printf("OK\n");
            }
        }
        else if (strcmp(argv[0], "!") == 0) {
            if (argc != 3) {
                printf("Wrong number of arguments, should be 3\n");
                continue;
            }
            if (strcmp(argv[1], "Save") == 0) {
                int error = Save(tree, argv[2]);
                if (error) {
                    perror("ERROR");
                }
                else {
                    printf("OK\n");
                }
            }
            else if (strcmp(argv[1], "Load") == 0) {
                TAvl *tempTree = NULL;
                int error = Load(&tempTree, argv[2]);
                if (error == -1) {
                    DeleteTree(tempTree);
                    perror("ERROR");
                }
                else if (error == 1) {
                    DeleteTree(tempTree);
                    printf("Wrong number of bytes in file, abort\n");
                }
                else {
                    DeleteTree(tree);
                    tree = tempTree;
                    printf("OK\n");
                }
            }
            else {
                printf("No such command\n");
                continue;
            }
        }
        else if (strcmp(argv[0], "Print") == 0) {
            Print(tree, 0);
        }
        else {
            if (argc != 1) {
                printf("No such command\n");
                continue;
            }
            unsigned long long *res = Find(tree, argv[0]);
            if (res == NULL) {
                printf("NoSuchWord\n");
            }
            else {
                printf("OK: %llu\n", *res);
            }
        }
    }

    DeleteTree(tree);

    return 0;
}
