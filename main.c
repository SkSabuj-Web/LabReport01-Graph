
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

void Dijkstra(int vertices, int graph[vertices][vertices],
              int source,int destination) {

    int distance[vertices],parent[vertices];
    bool included[vertices];

    for(int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        included[i] =false;
    }

    distance[source] = 0;

    for(int i = 0; i < vertices; i++) {
        int min = INT_MAX;
        int current = -1;

        for(int j = 0; j < vertices; j++) {
            if(!included[j] && distance[j]< min) {
                min = distance[j];
                current = j;
            }
        }

        if(current == -1) break;

        included[current] =true;

        for(int j = 0; j < vertices; j++) {
            if(graph[current][j] != 0 && !included[j] &&
               distance[current] !=INT_MAX &&
               distance[current] + graph[current][j]<distance[j]) {

                distance[j] = distance[current]+graph[current][j];
                parent[j] = current;
            }
        }
    }

    if(distance[destination] == INT_MAX) {
        printf("Not Possible\n");
        return;
    }

    int temp[vertices], path[vertices];
    int count = 0, current=destination;

    while(current !=-1) {
        temp[count++]=current;
        current=parent[current];
    }

    for(int i =0; i < count; i++) {
        path[i] =temp[count - 1 - i];
    }

    PrintPath(vertices,path,destination,distance[destination]);
}

bool KruskalMST(int vertices,Edge edges[],int edgeCount,
                int tree[vertices][vertices]) {

    int parent[vertices];

    for(int i =0; i<vertices; i++) {
        parent[i] = i;
    }

    for(int i =0; i < edgeCount-1;i++) {
        for(int j =0; j < edgeCount - i - 1; j++) {
            if(edges[j].w > edges[j+1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1]=temp;
            }
        }
    }

    int count = 0;

    for(int i=0; i < edgeCount; i++) {
        int u = FindParent(parent,edges[i].u);
        int v = FindParent(parent,edges[i].v);

        if(u != v) {
            tree[edges[i].u][edges[i].v] = edges[i].w;
            tree[edges[i].v][edges[i].u] = edges[i].w;

            parent[u]=v;
            count++;

            if(count == vertices-1) break;
        }
    }

    return count==vertices-1;
}

bool PrimMST(int vertices, int graph[vertices][vertices],
             int tree[vertices][vertices]) {

    int parent[vertices], minCost[vertices];
    bool included[vertices];

    for(int i = 0; i<vertices; i++) {
        parent[i] =-1;
        minCost[i] = INT_MAX;
        included[i] = false;
    }

    minCost[0] = 0;

    for(int i = 0; i<vertices; i++) {
        int current = FindMinCost(vertices, minCost, included);

        if(current ==-1) return false;

        included[current] = true;

        for(int j = 0; j < vertices; j++) {
            if(graph[current][j] != 0 && !included[j] &&
               graph[current][j] < minCost[j]) {

                minCost[j] = graph[current][j];
                parent[j] = current;
            }
        }
    }

    for(int i =1; i<vertices; i++) {
        if(parent[i] == -1) return false;

        tree[parent[i]][i] = graph[parent[i]][i];
        tree[i][parent[i]] = graph[i][parent[i]];
    }

    return true;
}

void ShowKruskal(int vertices,Edge edges[],int edgeCount,
                int source,int destination) {

    int tree[vertices][vertices];

    for(int i =0; i < vertices; i++) {
        for(int j =0; j < vertices; j++) {
            tree[i][j] =0;
         }
    }
    int path[vertices], cost;

    if(KruskalMST(vertices,edges,edgeCount,tree)) {
        if(FindTreePath(vertices,tree,source,destination,path,&cost)) {
            PrintPath(vertices, path, destination, cost);
        }
        else {
            printf("Not Possible\n");
        }
    }
    else {
        printf("Not Possible\n");
    }
}

void ShowPrim(int vertices,int graph[vertices][vertices],
             int source,int destination) {

    int tree[vertices][vertices];

    for(int i =0; i < vertices;i++) {
        for(int j =0; j < vertices;j++) {
            tree[i][j] =0;
            }
    }
    int path[vertices], cost;

    if(PrimMST(vertices,graph,tree)) {
        if(FindTreePath(vertices,tree,source,destination,path,&cost)) {
            PrintPath(vertices, path, destination, cost);
        }
        else {
            printf("Not Possible\n");
        }
    }
    else {
        printf("Not Possible\n");
    }
}

int main() {
    FILE *file=fopen("input.txt", "r");

    if(file == NULL){
        printf("File not found!\n");
        return 1;
    }

    int vertices, edgeCount;
    fscanf(file,"%d %d",&vertices,&edgeCount);

    Edge edges[edgeCount];
    int graph[vertices][vertices];

    for(int i =0; i < vertices; i++) {
        for(int j =0; j < vertices; j++) {
            graph[i][j] =0;
        }
    }

    for(int i = 0; i < edgeCount; i++) {
        fscanf(file, "%d %d %d",
               &edges[i].u, &edges[i].v, &edges[i].w);

        graph[edges[i].u][edges[i].v] = edges[i].w;
        graph[edges[i].v][edges[i].u] = edges[i].w;
    }
