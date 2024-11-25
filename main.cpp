/***************************************************************************
* COMSC-210 | Lab 34 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*
* This program simulates the city network within a county
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

        unordered_map<int, string> cityNames {};

        vector<Edge> edges {};

        // constructor
        Graph(vector<Edge> const &edges, unordered_map<int, string> cityNames) {
            // Find the maximum numbered vertex
            int N = 0;
            for (auto &edge : edges)
                N = max(N, max(edge.src, edge.dest));
            N += 1;

            // Resize the vector to hold SIZE elements of type vector<Edge>
            adjList.resize(N);
            this->cityNames = cityNames;
            this->edges = edges;

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
            cout << "\tThe City Network\n";
            cout << "================================\n";

            for (int i = 0; i < adjList.size(); i++) {
                if (adjList[i].empty()) continue;
                cout << cityNames[i] << ": ";
                for (Pair v : adjList[i])
                    cout << "(" << cityNames[v.first] << ", " << v.second << " km) ";
                cout << "\n";
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

        void findShortestPath(int src, int dest)
        {
            // Number of vertices in the graph
            int N = adjList.size();

            // A mini-heap priority queue
            priority_queue<Pair, vector<Pair>, greater<Pair>> minHeap {};

            // Distance vector to store the shortest distance from src to i
            vector<int> dist(N, INT_MAX);

            // Parent vector to store the path
            vector<int> parent(N, -1);

            // Insert source vertex into the priority queue and initialize its distance to 0
            minHeap.push(make_pair(0, src));
            dist[src] = 0;

            while (!minHeap.empty()) {
                int u = minHeap.top().second;
                minHeap.pop();

                // Visit all adjacent vertices of u
                for (auto &neighbor : adjList[u]) {
                    int v = neighbor.first;
                    int weight = neighbor.second;

                    // Relaxation step
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        minHeap.push(make_pair(dist[v], v));
                    }
                }
            }

            // Output the shortest distance
            if (dist[dest] == INT_MAX) {
                cout << "There is no path between " << cityNames[src] << " and " << cityNames[dest] << "." << endl;
                return;
            }

            cout << "\nThe shortest distance from " << cityNames[src] << " to " << cityNames[dest] << " is " << dist[dest] << " km." << endl;

            // Reconstruct the shortest path
            vector<int> path;
            for (int v = dest; v != -1; v = parent[v])
                path.push_back(v);

            reverse(path.begin(), path.end());

            // Output the path
            cout << "Path: ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << cityNames[path[i]];
                if (i != path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
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

    unordered_map<int, string> cityNames = {
            {0, "City A"},
            {2, "City B"},
            {3, "City C"},
            {4, "City D"},
            {5, "City E"},
            {7, "City F"},
            {8, "City G"},
            {9, "City H"},
            {10, "City I"},
            {11, "City J"},
            {12, "City K"}
    };

    // Creates graph
    Graph graph(edges, cityNames);
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    // Ask user for source and destination cities
    string srcCity, destCity;
    cout << "\nEnter source city: ";
    getline(cin, srcCity);
    cout << "Enter destination city: ";
    getline(cin, destCity);

    // Find the node indices for the given city names
    int src = -1, dest = -1;
    for (auto &pair : cityNames) {
        if (pair.second == srcCity)
            src = pair.first;
        if (pair.second == destCity)
            dest = pair.first;
    }

    if (src == -1 || dest == -1) {
        cout << "Invalid city name(s) entered." << endl;
        return 1;
    }

    // Find the shortest path
    graph.findShortestPath(src, dest);

    return 0;
}

