#include "dijkstra.h"

int main()
{
    int graph[N][N] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0}};

    int startNode = 0;
    int endNode = 4;

    dijkstra(graph, startNode, endNode);

    return 0;
}