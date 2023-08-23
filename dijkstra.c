#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100
#define INF 9999

struct Graph {
    int nodes;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
};

int minDistance(int distances[], bool shortestPathSet[], int nodes) {
    int min = INF, minIndex;
	int i;
    for (i = 0; i < nodes; i++) {
        if (!shortestPathSet[i] && distances[i] <= min) {
            min = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(struct Graph *graph, int startNode) {
    int distances[MAX_NODES];
    bool shortestPathSet[MAX_NODES];
	int i;
    for (i = 0; i < graph->nodes; i++) {
        distances[i] = INF;
        shortestPathSet[i] = false;
    }

    distances[startNode] = 0;
	int count;
    for (count = 0; count < graph->nodes - 1; count++) {
        int u = minDistance(distances, shortestPathSet, graph->nodes);
        shortestPathSet[u] = true;
		int v;
        for (v = 0; v < graph->nodes; v++) {
            if (!shortestPathSet[v] && graph->adjacencyMatrix[u][v] && distances[u] != INF &&
                distances[u] + graph->adjacencyMatrix[u][v] < distances[v]) {
                distances[v] = distances[u] + graph->adjacencyMatrix[u][v];
            }
        }
    }

    printf("Vertex   Distance from Source\n");
    for (i = 0; i < graph->nodes; i++) {
        printf("%d \t\t %d\n", i, distances[i]);
    }
}

int main() {
    struct Graph graph = {
        .nodes = 5,
        .adjacencyMatrix = {
            {0, 10, 20, 0, 0},
            {10, 0, 0, 50, 10},
            {20, 0, 0, 20, 33},
            {0, 50, 20, 0, 2},
            {0, 10, 33, 2, 0}
        }
    };

    int startNode = 0;
    dijkstra(&graph, startNode);

    return 0;
}
