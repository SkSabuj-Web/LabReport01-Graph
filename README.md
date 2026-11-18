# LabReport01-Graph

## About the Project

This project is developed using the C programming language. It analyzes a connected, undirected, weighted graph to find the shortest path and Minimum Spanning Tree (MST).

The program uses Dijkstra's, Kruskal's, and Prim's algorithms to find paths between a source and a destination. It also removes a selected edge and checks how the graph is affected.

If removing an edge disconnects the graph, the program displays "Not Possible".

## Algorithms Used

1. **Dijkstra's Algorithm**
   - Finds the shortest path between the source and destination vertices.

2. **Kruskal's Algorithm**
   - Builds a Minimum Spanning Tree (MST).
   - Finds the path between the source and destination inside the MST.

3. **Prim's Algorithm**
   - Builds a Minimum Spanning Tree (MST).
   - Finds the path between the source and destination inside the MST.

4. **Breadth-First Search (BFS)**
   - Finds a path between two vertices inside the MST.

## Features

- Reads graph data from an input file.
- Finds the shortest path using Dijkstra's algorithm.
- Builds an MST using Kruskal's algorithm.
- Builds an MST using Prim's algorithm.
- Finds paths inside both MSTs using BFS.
- Displays paths and their total costs.
- Removes a selected edge from the graph.
- Creates an updated graph after edge removal.
- Calculates updated paths and costs.
- Displays "Not Possible" if a path cannot be found.

## Technologies Used

- C Programming Language
- Graph
- Dijkstra's Algorithm
- Kruskal's Algorithm
- Prim's Algorithm
- Breadth-First Search (BFS)

## Input Format

The program reads input from `input.txt`.

The input format is:

```text
N M
u v w
u v w
...
source destination
removeU removeV
```

Where:

- `N` = Number of vertices.
- `M` = Number of edges.
- `u` and `v` = Connected vertices.
- `w` = Weight of the edge.
- `source` = Starting vertex.
- `destination` = Target vertex.
- `removeU` and `removeV` = Edge to be removed.

### Example Input

```text
6 8
0 2 2
2 3 2
0 1 2
1 3 2
3 5 2
4 5 4
0 4 5
0 5 5
0 5
3 5
```

## How to Run

### 1. Compile the Program

```bash
gcc -std=c99 main.c -o main
```

### 2. Run the Program

**Windows:**

```bash
.\main.exe
```

**Linux / macOS:**

```bash
./main
```

Make sure `input.txt` is in the same folder as `main.c`.

## Expected Output

The program displays:

- Original shortest path using Dijkstra's algorithm.
- Kruskal MST path and cost.
- Prim MST path and cost.
- The selected edge being removed.
- Updated shortest path after edge removal.
- Updated Kruskal MST path and cost.
- Updated Prim MST path and cost.

If removing the selected edge disconnects the graph, the program displays:

```text
Not Possible
```

## Author

**Sajib Khan Sabuj**

GitHub: [SkSabuj-Web](https://github.com/SkSabuj-Web)
