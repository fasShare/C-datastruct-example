#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <climits>

int initAdjacencyGraph(struct adjacencyGraph* graph, int vexNum, enum GRAPHTYPE type) {

    graph->nodeNum = vexNum;
    graph->type = type;
    graph->nodes = (struct adjacencyListNode *)malloc(sizeof(struct adjacencyListNode) * vexNum);

    if (graph->nodes == NULL) {
        return -1;
    }

    int  i = 0;
    for (i = 0; i < graph->nodeNum; i++) {
        graph->nodes[i].state = INVALID;
        graph->nodes[i].firstEdge = NULL;
    }

    return 0;
}

int addVertex(struct adjacencyGraph* graph, int verIndex, VertexType data) {

    if (graph->nodeNum <= verIndex) {
        return -1;
    }

    graph->nodes[verIndex].data = data;
    graph->nodes[verIndex].state = VALID;

    return 0;
}

int addEdge(struct adjacencyGraph* graph, int firstVer, int secondVer, int weight) {

    if ((firstVer >= graph->nodeNum) || (secondVer >= graph->nodeNum)) {
        return -1;
    }

    struct edge *newEdge = (struct edge *)malloc(sizeof(struct edge));
    if (newEdge == NULL) {
        return -1;
    }

    newEdge->next = NULL;
    newEdge->verIndex = secondVer;
    newEdge->weight = weight;

    newEdge->next = graph->nodes[firstVer].firstEdge;
    graph->nodes[firstVer].firstEdge = newEdge;

    return 0;
}

int getFirstNoErgodicVertex(struct adjacencyGraph* graph, char *ergodic) {
    int i = 0;

    for (i = 0; i < graph->nodeNum; i++) {
        if ((graph->nodes[i].state == VALID) && (ergodic[i] == 0)) {
            return i;
        }

    }

    return -1;
}


// 返回本次遍历成功的节点数
int depth__(struct adjacencyGraph* graph, int index, char *flag) {
    int count = 0;
    flag[index] = 1;

    struct edge *cur = graph->nodes[index].firstEdge;
    printf("%d\t", graph->nodes[index].data);

    ++count;

    while(cur != NULL) {
        if (flag[cur->verIndex] == 0) {
            count += depth__(graph, cur->verIndex, flag);
        }
        cur = cur->next;
    }

    return count;
}

void depth(struct adjacencyGraph* graph) {

    // 记录遍历的总的节点数，当这个图由很多小的独立的图组成时有用。
    int count = 0;

    char *ergodic = (char *)malloc(sizeof(char) * graph->nodeNum);
    if (ergodic == NULL) {
        return;
    }

    int i = 0;
    for (i = 0; i < graph->nodeNum; i++) {
        ergodic[i] = 0;
    }

NoErgodicComplete:

    int index = getFirstNoErgodicVertex(graph, ergodic);
    if (index == -1) {
        return;
    }
    count += depth__(graph, index, ergodic);

    if (count < graph->nodeNum) {
        goto NoErgodicComplete;
    }

    printf("\n");

    printf("count = %d\n", count);

    free(ergodic);
    ergodic = NULL;
}

void breadth(struct adjacencyGraph* graph) {

    // 记录遍历的总的节点数，当这个图由很多小的独立的图组成时有用。
    int count = 0;

    char *ergodic = (char *)malloc(sizeof(char) * graph->nodeNum);
    if (ergodic == NULL) {
        return;
    }

    int i = 0;
    for (i = 0; i < graph->nodeNum; i++) {
        ergodic[i] = 0;
    }

NoErgodicComplete:
    int index = getFirstNoErgodicVertex(graph, ergodic);
    if (index == -1) {
        return;
    }

    // 先不实现
    std::queue<int> verIndexQueue;
    verIndexQueue.push(index);
    ergodic[index] = 1;

    while (!verIndexQueue.empty()) {
        index = verIndexQueue.front(); verIndexQueue.pop();
        printf("%d\t", graph->nodes[index].data);
        count++;
        edge *cur = graph->nodes[index].firstEdge;

        while (cur != NULL) {
            if (ergodic[cur->verIndex] == 0) {
                verIndexQueue.push(cur->verIndex);
                ergodic[cur->verIndex] = 1;
            }
            cur = cur->next;
        }
    }

    if (count < graph->nodeNum) {
        goto NoErgodicComplete;
    }

    printf("\n");

    printf("count = %d\n", count);

    free(ergodic);
    ergodic = NULL;
}

int findFirstIndegreeZero(struct adjacencyGraph* graph, int* degree) {
    for (int i = 0; i < graph->nodeNum; i++) {
        if ((graph->nodes[i].state == VALID) && (degree[i] == 0)) {
            return i;
        }
    }
    return -1;
}

int topSort(struct adjacencyGraph* graph) {
    int count = 0; // 统计排序过的顶点数目

    int *degree = (int *)malloc(sizeof(int) * graph->nodeNum);
    if (degree == NULL) {
        return -1;
    }
    for (int i = 0; i < graph->nodeNum; i++) {
        degree[i] = 0;
    }

    // 统计各个顶点的入度

    for (int i = 0; i < graph->nodeNum; i++) {
        if (graph->nodes[i].state == VALID) {
            edge *cur = graph->nodes[i].firstEdge;
            while (cur != NULL) {
                degree[cur->verIndex] += 1;
                cur = cur->next;
            }
        }
    }



    char *ergodic = (char *)malloc(sizeof(char) * graph->nodeNum);
    if (ergodic == NULL) {
        return -1;
    }

    for (int i = 0; i < graph->nodeNum; i++) {
        ergodic[i] = 0;
    }

    // 声明一个保存入度为0的顶点的队列
    std::queue<int> ZeroDegreeQueue;

    // 找到所有入度为0的顶点
    for (int i = 0; i < graph->nodeNum; i++) {
        if ((graph->nodes[i].state == VALID) && (degree[i] == 0)) {
            ZeroDegreeQueue.push(i);
            ergodic[i] = 1; // 防止该顶点被多次放入队列
        }
    }

    while (!ZeroDegreeQueue.empty()) {
        int index = ZeroDegreeQueue.front();
        ZeroDegreeQueue.pop();
        printf("%d\t", graph->nodes[index].data);
        ++count;

        edge *cur = graph->nodes[index].firstEdge;
        // 从入度为０的队列中取出一个节点，更新其所有的后继节点的入度，然后把入度为０的后继节点，继续放入队列
        while (cur != NULL) {
            if (ergodic[cur->verIndex] == 0) {
                if (--degree[cur->verIndex] == 0) {
                    ZeroDegreeQueue.push(cur->verIndex);
                }
            }
            cur = cur->next;
        }
    }

    if (count < graph->nodeNum) {
        return -1;
    }

    printf("\n");

    free(degree);
    degree = NULL;
    free(ergodic);
    ergodic = NULL;
    return 0;
}

int SingleShortestWeightPath(struct adjacencyGraph* graph, int vertex) {
    // 参数合法性检查
    if (vertex >= graph->nodeNum) {
        return -1;
    }

    // 声明一个存储该点到其他所有点最短路径的数组
    int *shortestPath = (int *)malloc(sizeof(int) * graph->nodeNum);
    if (shortestPath == NULL) {
        return -1;
    }

    for (int i = 0; i < graph->nodeNum; i++) {
        shortestPath[i] = INT_MAX;
    }

    // 声明一个标识顶点是否遍历过的标志数组
    char *ergodic = (char *)malloc(sizeof(char) * graph->nodeNum);
    if (ergodic == NULL) {
        return -1;
    }

    for (int i = 0; i < graph->nodeNum; i++) {
        ergodic[i] = 0;
    }

    //　采用广度遍历或者深度遍历，这里采用广度遍历
    // 借助队列
    std::queue<int> ergodicVertex;
    ergodicVertex.push(vertex);

    while (!ergodicVertex.empty()) {

    }

    free(ergodic);
    ergodic = NULL;
    free(shortestPath);
    shortestPath = NULL;

    return 0;
}

