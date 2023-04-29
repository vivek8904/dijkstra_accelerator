#include "dijkstra.h"

void dijkstra(int graph[N][N], int startNode, int endNode)
{
#pragma HLS INTERFACE ap_fifo depth=50 port=graph
#pragma HLS INTERFACE s_axilite port=startNode bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=endNode bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS ARRAY_PARTITION variable=graph dim=2 complete

    int dist[N];
    bool visited[N] = {false};
    int prevNode[N] = {0};
    int path[N];

    // initialize distance array
    for (int i = 0; i < N; ++i)
        dist[i] = INT_MAX;

    dist[startNode] = 0;

    // run Dijkstra's algorithm
#pragma HLS PIPELINE II = 2
    for (int i = 0; i < N - 1; ++i)
    {
        int minDist = INT_MAX;
        int currNode = -1;

        // find the unvisited node with the shortest distance
        for (int j = 0; j < N; ++j)
        {

            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                currNode = j;
            }
        }

        if (currNode == -1)
            break;

        visited[currNode] = true;

        // update the distances of the unvisited neighbors of the current node
        for (int j = 0; j < N; ++j)
        {
            //#pragma disable_loop_pipelining
            if (graph[currNode][j] > 0 && !visited[j] &&
                dist[currNode] != INT_MAX && dist[currNode] + graph[currNode][j] < dist[j])
            {
                dist[j] = dist[currNode] + graph[currNode][j];
                prevNode[j] = currNode;
            }
        }
    }

    // check if there is a path from startNode to endNode
    if (dist[endNode] == INT_MAX)
    {
        std::cout << "No path found from " << startNode << " to " << endNode << std::endl;
        return;
    }

    // reconstruct the shortest path
    int currNode = endNode;
    int i = 0;

    while (currNode != startNode)
    {

        path[i++] = currNode;
        currNode = prevNode[currNode];
    }

    path[i++] = startNode;

    // print the shortest path

}
