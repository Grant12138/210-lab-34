/***************************************************************************
* COMSC-210 | Lab 34 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates an alias 'Pair' for the pair<int,int> data type

class Graph {
    public:
        // a vector of vectors of Pairs to represent an adjacency list
        vector<vector<Pair>> adjList;
        // constructor
        Graph(vector<Edge> const &edges) {
            // resize the vector to hold SIZE elements of type vector<Edge>
            int SIZE = edges.size();
            adjList.resize(SIZE);
            // add edges to the directed graph
            for (auto &edge: edges) {
                int src = edge.src;
                int dest = edge.dest;
                int weight = edge.weight;
                adjList[src].push_back(make_pair(dest, weight));
                adjList[dest].push_back(make_pair(src, weight));
            }
        }

        void printGraph() {
            for (int i = 0; i < adjList.size(); i++) {
                for (Pair v: adjList[i])
                    cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
                cout << endl;
            }
        }

        // Depth-First Search (DFS) starting from a given vertex
        void DFS(int startVertex) const {
            // Vector to keep track of visited vertices
            vector<bool> visited(adjList.size(), false);
            // Stack for DFS
            stack<int> stackDFS;

            // Push the starting vertex onto the stack
            stackDFS.push(startVertex);

            cout << "DFS Traversal starting from vertex " << startVertex << ": ";

            while (!stackDFS.empty()) {
                // Pop a vertex from the stack
                int current = stackDFS.top();
                stackDFS.pop();

                // If the vertex hasn't been visited, mark it and process it
                if (!visited[current]) {
                    cout << current << " ";
                    visited[current] = true;

                    // Push all adjacent vertices onto the stack
                    // Iterate in reverse to maintain order
                    for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                        int adjVertex = it->first;
                        if (!visited[adjVertex]) {
                            stackDFS.push(adjVertex);
                        }
                    }
                }
            }
            cout << endl;
        }

        // Breadth-First Search (BFS) starting from a given vertex
        void BFS(int startVertex) const {
            // Vector to keep track of visited vertices
            vector<bool> visited(adjList.size(), false);
            // Queue for BFS
            queue<int> queueBFS;

            // Mark the starting vertex as visited and enqueue it
            visited[startVertex] = true;
            queueBFS.push(startVertex);

            cout << "BFS Traversal starting from vertex " << startVertex << ": ";

            while (!queueBFS.empty()) {
                // Dequeue a vertex from the queue
                int current = queueBFS.front();
                queueBFS.pop();

                // Process the current vertex
                cout << current << " ";

                // Enqueue all adjacent vertices that haven't been visited
                for (const Pair &adj : adjList[current]) {
                    int adjVertex = adj.first;
                    if (!visited[adjVertex]) {
                        visited[adjVertex] = true;
                        queueBFS.push(adjVertex);
                    }
                }
            }
            cout << endl;
        }
};

vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},
        {0,2,8},
        {0,3,21},
        {2,3,6},
        {2,6,2},
        {5,6,6},
        {4,5,9},
        {2,4,4},
        {2,5,5}
};

int main()
{
    // Creates graph
    Graph graph(edges);
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}

