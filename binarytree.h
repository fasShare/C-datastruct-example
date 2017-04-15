#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef int elementType;
typedef struct TreeNode *treeNodePtr;
typedef treeNodePtr Tree;

struct TreeNode {
    elementType data;
    Tree left;
    Tree right;
    int leftlevel;
    int rightlevel;
};

void initTreeNode(Tree tree, elementType e);
int insertToTree(Tree *tree, elementType e);
void preSearchTree(Tree tree);
void postSearchTree(Tree tree);
void middleSearchTree(Tree tree);
void showTree(Tree tree, int steps);
void printData(elementType e);

int getTreeHeight(Tree tree);

int getBalanceFactor(Tree tree);

int getMax(int a, int b);

int balanceInsertToTree(Tree *tree, elementType e);
int balanceDeleteFromTree(Tree *tree, elementType e);

void turnRight(Tree *tree);
void turnLeft(Tree *tree);
#endif // BINARYTREE_H

