#include <stdio.h>
#include <stdlib.h>
/*
 * 
 */
typedef struct TstNode {
    struct TstNode *lef;
    struct TstNode *rig;
    struct TstNode *mid;
    char isWord;
    char now;
};
/**
 *
 */
typedef struct Tst {
	struct TstNode root;
};
int main(int argc, char **args)
{
    printf("Input strings:\n");
    char *str = malloc(sizeof(char) * 20);
    while (scanf("%s", str) != EOF) {
		printf("Output %s\n",str);
    }
	free(str);
}
