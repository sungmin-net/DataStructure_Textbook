#ifndef _GRAPH_MST_
#define _GRAPH_MST_

typedef struct GraphEdgeType {
    int vertexIdFrom;       // tail 노드 ID
    int vertexIdTo;         // Head 노드 ID
    int weight;             // 가중치
} GraphEdge;

// 순환검사
int checkCycle(LinkedGraph* pGraph, int fromVertexId, int toVertexId);

// Prim 알고리즘
LinkedGraph* mstPrim(LinkedGraph* pGraph, int vertex);

// 정점(mstVertexId)과 부속된 모든 간선 중
// 가중치가 가장 작으면서 순환을 발생시키지 않는 간선을 선택
void getMinWeightEdge(LinkedGraph* pGraph, LinkedGraph* pMST, int mstVertexId,
        GraphEdge* pMinWeightEdge);
int checkEdege(LinkedGraph* pGraph, int fromVertexId, int toVertexId);
#define MAX_INT         99999
#endif
