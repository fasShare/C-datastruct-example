#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void initTreeNode(Tree tree, elementType e) {
    tree->data = e;
    tree->left = NULL;
    tree->right = NULL;
    tree->leftlevel = -1;
    tree->rightlevel = -1;
}

int insertToTree(Tree *tree, elementType e) {
    if (!tree) {
        return -1;
    }
    if (!(*tree)) {
        *tree = (Tree)malloc(sizeof(struct TreeNode));
        initTreeNode(*tree, e);
        return 0;
    }

    if (e < (*tree)->data) {
        return insertToTree(&((*tree)->left), e);
    } else if (e > (*tree)->data) {
        return insertToTree(&((*tree)->right), e);
    } else {
        return -1;
    }

}

void preSearchTree(Tree tree) {
    if (tree == NULL) {
        return;
    }
    printData(tree->data);
    preSearchTree(tree->left);
    preSearchTree(tree->right);
}

void postSearchTree(Tree tree) {
    if (tree == NULL) {
        return;
    }
    preSearchTree(tree->left);
    preSearchTree(tree->right);
    printData(tree->data);
}

void middleSearchTree(Tree tree) {
    if (tree == NULL) {
        return;
    }
    preSearchTree(tree->left);
    printData(tree->data);
    preSearchTree(tree->right);
}

void showTree(Tree tree, int steps) {
    if (tree == NULL) {
        return;
    }
    showTree(tree->right, steps + 1);
    int i = 0;
    for(i = 0; i < steps; i++) {
        printf("-");
    }
    //printf("(%d,%d,%d)\n", tree->data, tree->leftlevel, tree->rightlevel);
    printf("(%d, %d, %d)\n", tree->data, tree->leftlevel, tree->rightlevel);
    showTree(tree->left, steps + 1);
}

void printData(elementType e) {
    printf(" %d ", e);
}

int balanceInsertToTree(Tree *tree, elementType e) {
    if (!tree) {
        return -1;
    }

    int ret = -1;
    //插入成功时，插入到左子树返回1,插入到右子树返回2,新建节点返回3
    if (!(*tree)) {
        *tree = (Tree)malloc(sizeof(struct TreeNode));
        initTreeNode(*tree, e);
        return 3;
    }

    if (e < (*tree)->data) { //left
        //只有在插入成功的情况更新高度
        ret = balanceInsertToTree(&((*tree)->left), e);
        if ((ret == -1) || (ret == 0)){
            return ret;
        }
        (*tree)->leftlevel += 1;

        int sub = (*tree)->leftlevel - (*tree)->rightlevel;
        if (abs(sub) < 2) {
            return 1;
        }
        if (ret == 1) {// left, left
            turnRight(tree);
        } else if (ret == 2) { // left, right
            turnLeft(&((*tree)->left));
            turnRight(tree);
        }

        return 0;
    } else if (e > (*tree)->data) { //right
        ret = balanceInsertToTree(&((*tree)->right), e);
        if ((ret == -1) || (ret == 0)) {
            return ret;
        }
        (*tree)->rightlevel += 1;

        int sub = (*tree)->rightlevel - (*tree)->leftlevel;
        if (abs(sub) < 2) {
            return 2;
        }

        if (ret == 1) { //right, left
            turnRight(&((*tree)->right));
            turnLeft(tree);
        } else if (ret == 2) { //right, right
            turnLeft(tree);
        }

        return 0;
    }

    return ret;

}

Tree findLeftmost(Tree tree) {
    assert(tree != NULL);
    if (tree->left == NULL) {
        return tree;
    }
    return findLeftmost(tree->left);
}

Tree findRightmost(Tree tree) {
    assert(tree != NULL);
    if (tree->right == NULL) {
        return tree;
    }
    return findRightmost(tree->right);
}

void swap(int *data1, int *data2) {
    int temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

int __deleteFromLeft(Tree *tree, elementType e) {
    int ret = balanceDeleteFromTree(&((*tree)->left), e);
    if (ret == -1) {
        return ret;
    }
    (*tree)->leftlevel -= 1;

    if (abs(getBalanceFactor(*tree)) < 2) { //本节点的平衡性没有被影响。
        return -1;
    }

    //在tree的左子树上进行删除时，根据tree的右子树的平衡因子进行判断
    int rightBalanceFactor = getBalanceFactor((*tree)->right);
    if (rightBalanceFactor == 1) { //需要双旋,否则，只需要对A进行左旋
        turnRight(&((*tree)->right));
    }
    turnLeft(tree);

    return -1;
}

int __deleteFromRight(Tree *tree, elementType e) {
    int ret = balanceDeleteFromTree(&((*tree)->right), e);
    if (ret == -1) {
        return ret;
    }
    (*tree)->rightlevel -= 1;

    if (abs(getBalanceFactor(*tree)) < 2) { //本节点的平衡性没有被影响。
        return ret;
    }

    //在tree的右子树上进行删除时，根据tree的左子树的平衡因子进行判断
    int leftBalanceFactor = getBalanceFactor((*tree)->left);
    if (leftBalanceFactor == -1) { //需要双旋,否则，只需要对A进行右旋
        turnLeft(&((*tree)->left));
    }
    turnRight(tree);

    return -1;
}

int balanceDeleteFromTree(Tree *tree, elementType e) {
    if ((tree == NULL) || (*tree == NULL)) {
        return -1;
    }
    //一、先找出要删除的节点
    if (e == (*tree)->data) {
        //分为3种情况
        //1.如果该节点为叶节点，直接删除
        if (((*tree)->left == NULL) && ((*tree)->right == NULL)) {
            free(*tree);
            *tree = NULL;
            return 0;
        }
        //2.如果该节点只有一棵子树
        if (((*tree)->left != NULL) && ((*tree)->right == NULL)) {
            Tree leftChild = (*tree)->left;
            free(*tree);
            *tree = leftChild;
            return 0;
        }

        if (((*tree)->left == NULL) && ((*tree)->right != NULL)) {
            Tree rightChild = (*tree)->right;
            free(*tree);
            *tree = rightChild;
            return 0;
        }
        //3.如果该节点有两棵子树
        if (getBalanceFactor(*tree) == -1) { //在右子树上找替换删除的节点
            Tree right = findLeftmost((*tree)->right);
            swap(&((*tree)->data), &(right->data));
            return __deleteFromRight(tree, e);
        } else if (getBalanceFactor(*tree) == 1) { //否则，在左子树上找替换删除的节点,但是仍要分两种情况
            Tree left = findRightmost((*tree)->left);
            swap(&((*tree)->data), &(left->data));
            return __deleteFromLeft(tree, e);
        } else {
            Tree left = findRightmost((*tree)->left);
            swap(&((*tree)->data), &(left->data));
            __deleteFromLeft(tree, e);
            return 0;
        }
    }

    //二、找到要删除的节点后进行节点的删除
    if (e < (*tree)->data) {
        return __deleteFromLeft(tree, e);
    }

    if (e > (*tree)->data) {
        return __deleteFromRight(tree, e);
    }

    return -1;
}

int getTreeHeight(Tree tree) {
    return getMax(tree->leftlevel, tree->rightlevel) + 1;
}

int getBalanceFactor(Tree tree) {
    return tree->leftlevel - tree->rightlevel;
}

int getMax(int a, int b) {
    return a > b ? a : b;
}

void turnRight(Tree *tree) {
    Tree leftChild = (*tree)->left;
    Tree leftRightchild = leftChild->right;

    (*tree)->leftlevel = leftChild->rightlevel;
    leftChild->rightlevel = getMax((*tree)->leftlevel, (*tree)->rightlevel) + 1;

    leftChild->right = *tree;
    (*tree)->left = leftRightchild;
    (*tree) = leftChild;
}

void turnLeft(Tree *tree) {
    Tree rightChild = (*tree)->right;
    Tree rightLeftChild = rightChild->left;

    (*tree)->rightlevel = rightChild->leftlevel;
    rightChild->leftlevel = getMax((*tree)->rightlevel, (*tree)->leftlevel) + 1;

    rightChild->left = *tree;
    (*tree)->right = rightLeftChild;
    (*tree)= rightChild;
}

