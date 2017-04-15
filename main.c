#include <stdio.h>
#include <binarytree.h>
#include <search.h>

int main(void)
{
    Tree tree = NULL;
    int i = 0;

    for (i = 0; i < 5; i++) {
        balanceInsertToTree(&tree, i);
    }
    for (i = 5; i < 20; i++) {
        balanceInsertToTree(&tree, i);
    }


    balanceDeleteFromTree(&tree, 1);
    balanceDeleteFromTree(&tree, 0);
    balanceDeleteFromTree(&tree, 15);
    balanceDeleteFromTree(&tree, 5);
    balanceDeleteFromTree(&tree, 4);

    showTree(tree, 0);

    printf("----------------------------------------------\n");

    balanceDeleteFromTree(&tree, 3);
    balanceDeleteFromTree(&tree, 2);

    balanceDeleteFromTree(&tree, 13);
    balanceDeleteFromTree(&tree, 5);
    balanceDeleteFromTree(&tree, 4);

    showTree(tree, 0);
}

