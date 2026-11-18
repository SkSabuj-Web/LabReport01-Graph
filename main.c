
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int u, v, w;
}Edge;

int FindMinCost(int vertices, int minCost[vertices], bool included[vertices]) {
    int min= INT_MAX;
    int vertex =-1;

    for(int i = 0; i < vertices; i++) {
        if(!included[i] && minCost[i] < min) {
            min = minCost[i];
            vertex =i;
        }
    }

    return vertex;
}

int FindParent(int parent[], int vertex) {
    if(parent[vertex] ==vertex) {
        return vertex;
    }

    return FindParent(parent,parent[vertex]);
}

bool FindTreePath(int vertices,int tree[vertices][vertices],
                  int source, int destination, int path[], int *cost) {

    int queue[vertices], parent[vertices];
    bool visited[vertices];

    for(int i = 0; i < vertices; i++) {
        parent[i] =-1;
        visited[i] = false;
    }

    int front = 0, rear = 0;
    queue[rear++] =source;
    visited[source] = true;

    while(front < rear) {
        int current = queue[front++];

        if(current == destination) break;

        for(int j =0; j < vertices; j++) {
            if(tree[current][j] != 0 && !visited[j]) {
                visited[j] = true;
                parent[j] =current;
                queue[rear++] = j;
            }
        }
    }

    if(!visited[destination]) return false;

    int temp[vertices],count = 0;
    int current = destination;

    while(current != -1) {
        temp[count++]= current;
        current = parent[current];
    }

    for(int i = 0; i < count; i++) {
        path[i] = temp[count - 1 - i];
    }

    *cost = 0;

    for(int i = 0; i< count - 1; i++) {
        *cost += tree[path[i]][path[i + 1]];
    }

    return true;
}

void PrintPath(int vertices,int path[], int destination, int cost) {
    int count = 0;

    while(count < vertices && path[count]!= destination) {
        count++;
    }

    count++;

    for(int i = 0; i < count; i++) {
        printf("%d", path[i]);

        if(i < count- 1) printf(" -> ");
    }

    printf(" (Cost: %d)\n",cost);
}