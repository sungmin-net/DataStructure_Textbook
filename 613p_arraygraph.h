#ifndef _GRAPH_ADJMATRIX_
#define _GRAPH_ADJMATRIX_

typedef struct ArrayGraphType {
    int maxVertexCount;
    int currentVertexCount;
    int graphType;
    int** ppAdjEdge;
    int* pVertex;
} ArrayGraph;

ArrayGraph* createArrayGraph(int maxVertexCount);
ArrayGraph* createArrayDirectedGraph(int maxVertexCount);
void deleteArrayGraph(ArrayGraph* pGraph);
int isEmptyArrayGraph(ArrayGraph* pGraph);
int addVertexArrayGraph(ArrayGraph* pGraph, int vertexId);
int addEdgeArrayGraph(ArrayGraph* pGraph, int fromVertexId, int toVertexId);
int addEdgeWithWeightArrayGraph(ArrayGraph* pGraph, int fromVertexId,
        int toVertexId, int weight);
int removeVertexArrayGraph(ArrayGraph* pGraph, int vertexId);
int removeEdgeArrayGraph(ArrayGraph* pGraph, int fromVertexId, int toVertexId);
int checkVertexValid(ArrayGraph* pGraph, int vertexId);
void displayArrayGraph(ArrayGraph* pGraph);
#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define USED        1
#define NOT_USED    0

#define SUCCESS     1
#define FAIL        0

#define TRUE        1
#define FALSE       0

#define GRAPH_UNDIRECTED    1
#define GRAPH_DIRECTED      0
#endif
