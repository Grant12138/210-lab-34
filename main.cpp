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
            cout << "Graph's adjacency list:\n";

            for (int i = 0; i < adjList.size(); i++) {
                for (Pair v: adjList[i])
                    cout << i << " --> (" << v.first << ", " << v.second << ") ";
                cout << endl;
            }
        }

        void BFS(int start)
        {
            cout << "BFS starting from vertex " << start << "\n";
            vector<bool> visited(adjList.size(), false);
            queue<int> q {};

            visited[start] = true;
            q.push(start);

            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                cout << v << " ";

                for (Pair &neighbor : adjList[v])
                {
                    int u = neighbor.first;
                    if (!visited[u])
                    {
                        visited[u] = true;
                        q.push(u);
                    }
                }
            }
            cout << '\n';
        }

        void DFS(int start)
        {
            cout << "DFS starting from vertex " << start << "\n";

            vector<bool> visited(adjList.size(), false);
            DFSUtil(start, visited);
            cout << '\n';
        }

    private:
        void DFSUtil(int v, vector<bool> &visited)
        {
            visited[v] = true;
            cout << v << " ";

            for (Pair &neighbor : adjList[v])
            {
                int u = neighbor.first;
                if (!visited[u])
                    DFSUtil(u, visited);
            }
        }
};


int main()
{
    vector<Edge> edges = {
        // Original edges with updated weights
        {0, 2, 9},
        {0, 3, 22},
        {2, 3, 7},
        {2, 4, 5},
        {2, 5, 6},
        {4, 5, 10},

        // New edges involving new nodes
        {0, 7, 15},
        {3, 8, 10},
        {7, 8, 7},
        {5, 9, 12},
        {4, 10, 9},
        {2, 11, 3},
        {8, 9, 4},
        {9, 12, 6},
        {11, 12, 5},
        {10, 11, 2},
        {3, 12, 8}
    };
    // Creates graph
    Graph graph(edges);
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}

