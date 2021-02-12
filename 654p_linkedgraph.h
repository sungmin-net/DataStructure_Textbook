#ifndef _GRAPH_ADJLIST_
#define _GRAPH_ADJLIST_

typedef struct LinkedGraphType {
    int maxVertexCount;     // 최대 노드 개수
    int currentVertexCount; // 현재 사용되는 노드의 개수
    int currentEdgeCount;   // 현재 간선의 개수
    int graphType;          // 그래프 종류: 1-Undirected, 2-Directed
    LinkedList** ppAdjEdge; // 간선 저장을 위한 연결 리스트(포인터)들의 배열
    int* pVertex;           // 노드 저장을 위한 1차원 배열
} LinkedGraph;

LinkedGraph* createLinkedGraph(int maxVertexCount);
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount);
void deleteLinkedGraph(LinkedGraph* pGraph);
int isEmptyLinkedGraph(LinkedGraph* pGraph);
int addVertexLinkedGraph(LinkedGraph* pGraph, int vertexId);
int addEdgeLinkedGraph(LinkedGraph* pGraph, int fromVertexId, int toVertexId);
int addEdgeWithWeightLinkedGraph(LinkedGraph* pGraph, int fromVertexId,
        int toVertexId, int weight);
int checkVertexValid(LinkedGraph* pGraph, int vertexId);
int removeVertexLinkedGraph(LinkedGraph* pGraph, int vertexId);
int removeEdgeLinkedGraph(LinkedGraph* pGraph, int fromVertexId,
        int toVertexId);
void deleteGraphNode(LinkedList* pList, int delVertexId);
int findGraphNodePosition(LinkedList* pList, int vertexId);
void displayLinkedGraph(LinkedGraph* pGraph);
#endif

#ifndef _COMMON_GRAPH_DEF_
#define _COMMON_GRAPH_DEF_

#define TRUE                1
#define FALSE               0

#define USED                1
#define NOT_USED            0

#define SUCCESS             1
#define FAIL                0

#define GRAPH_UNDIRECTED    1
#define GRAPH_DIRECTED      2
#endif
