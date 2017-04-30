#include <stdio.h>
#include <binarytree.h>
#include <search.h>
#include <graph.h>

int main(void)
{
#if 1
    struct adjacencyGraph graph;

    initAdjacencyGraph(&graph, 7, DIGRAPH);
    // 插入图的顶点
    addVertex(&graph, 0, 1);
    addVertex(&graph, 1, 2);
    addVertex(&graph, 2, 3);
    addVertex(&graph, 3, 4);
    addVertex(&graph, 4, 5);
    addVertex(&graph, 5, 6);
    addVertex(&graph, 6, 7);

    // 插入图中的边
    addEdge(&graph, 0, 2, 0);
    addEdge(&graph, 0, 3, 0);
    addEdge(&graph, 0, 1, 0);

    addEdge(&graph, 1, 3, 0);
    addEdge(&graph, 1, 4, 0);

    addEdge(&graph, 4, 3, 0);
    addEdge(&graph, 4, 6, 0);

    addEdge(&graph, 6, 5, 0);

    addEdge(&graph, 3, 2, 0);
    addEdge(&graph, 3, 5, 0);
    addEdge(&graph, 3, 6, 0);

    addEdge(&graph, 2, 5, 0);

    // 对图进行深度遍历
    depth(&graph);

    // 对图进行广度遍历
    breadth(&graph);

    // 拓扑排序
    topSort(&graph);

#endif
}

void depthBreadthTopSort() {
#if 1
    struct adjacencyGraph graph;

    initAdjacencyGraph(&graph, 9, DIGRAPH);
    // 插入图的顶点
    addVertex(&graph, 0, 1);
    addVertex(&graph, 1, 2);
    addVertex(&graph, 2, 3);
    addVertex(&graph, 3, 4);
    addVertex(&graph, 4, 5);
    addVertex(&graph, 5, 6);
    addVertex(&graph, 6, 7);

    //　测试图是由多个子图构成时，算法的正确性
    addVertex(&graph, 7, 8);
    addVertex(&graph, 8, 9);

    // 插入图中的边
    addEdge(&graph, 0, 2, 0);
    addEdge(&graph, 0, 3, 0);
    addEdge(&graph, 0, 1, 0);

    addEdge(&graph, 1, 3, 0);
    addEdge(&graph, 1, 4, 0);

    addEdge(&graph, 4, 3, 0);
    addEdge(&graph, 4, 6, 0);

    addEdge(&graph, 6, 5, 0);

    addEdge(&graph, 3, 2, 0);
    addEdge(&graph, 3, 5, 0);
    addEdge(&graph, 3, 6, 0);

    addEdge(&graph, 2, 5, 0);

    // 对图进行深度遍历
    depth(&graph);

    // 对图进行广度遍历
    breadth(&graph);

    // 拓扑排序
    topSort(&graph);

#endif
}

