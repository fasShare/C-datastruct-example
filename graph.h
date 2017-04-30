#ifndef GRAPH_H
#define GRAPH_H

typedef int VertexType;
typedef int WeightType;

enum GRAPHTYPE {
    DIGRAPH,
    UNDIGRAPH,
};

enum VERTEXSTATE {
    VALID,
    INVALID,
};

struct edge {
    int verIndex;
    WeightType weight;
    struct edge *next;
};


struct adjacencyListNode {
    char state;
    VertexType data;
    struct edge *firstEdge;
};

struct adjacencyGraph {
    enum GRAPHTYPE type;
    int nodeNum;
    struct adjacencyListNode *nodes;
};

int initAdjacencyGraph(struct adjacencyGraph* graph, int vexNum, enum GRAPHTYPE type);
int addVertex(struct adjacencyGraph* graph, int verIndex, VertexType data);
int addEdge(struct adjacencyGraph* graph, int firstVer, int secondVer, int weight);

int getFirstNoErgodicVertex(struct adjacencyGraph* graph);

// 深度遍历， 广度遍历
void depth(struct adjacencyGraph* graph);
void breadth(struct adjacencyGraph* graph);

// 拓扑排序
int topSort(struct adjacencyGraph* graph);

// 单源有权最短路径
int SingleShortestWeightPath(struct adjacencyGraph* graph, int vertex);

#endif // GRAPH_H
