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

        void BFS(const string& startCity) {
            auto it = cityIndices.find(startCity);
            if (it == cityIndices.end()) {
                cout << "City " << startCity << " does not exist in the graph." << endl;
                return;
            }

            int start = it->second;
            vector<bool> visited(adjList.size(), false);
            queue<int> q;

            visited[start] = true;
            q.push(start);

            cout << "\nBFS traversal starting from " << startCity << ":\n";

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << cityNames[v] << " ";

                for (Pair &neighbor : adjList[v]) {
                    int u = neighbor.first;
                    if (!visited[u]) {
                        visited[u] = true;
                        q.push(u);
                    }
                }
            }
            cout << endl;
        }

        void DFS(const string& startCity) {
            auto it = cityIndices.find(startCity);
            if (it == cityIndices.end()) {
                cout << "City " << startCity << " does not exist in the graph." << endl;
                return;
            }

            int start = it->second;
            vector<bool> visited(adjList.size(), false);
            cout << "\nDFS traversal starting from " << startCity << ":\n";
            DFSUtil(start, visited);
            cout << endl;
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

        void findMST() {
            // Number of vertices in the graph
            int N = adjList.size();

            // Sort all edges in increasing order of their weight
            vector<Edge> sortedEdges = edges;
            sort(sortedEdges.begin(), sortedEdges.end(), [](Edge a, Edge b) {
                return a.weight < b.weight;
            });

            // Disjoint Set Union (Union-Find) data structure
            vector<int> parent(N);
            for (int i = 0; i < N; i++)
                parent[i] = i;

            function<int(int)> find = [&](int u) {
                if (parent[u] != u)
                    parent[u] = find(parent[u]);
                return parent[u];
            };

            auto unionSets = [&](int u, int v) {
                parent[find(u)] = find(v);
            };

            vector<Edge> mstEdges;
            int totalWeight = 0;

            for (auto &edge : sortedEdges) {
                int u = edge.src;
                int v = edge.dest;

                // Skip nodes not in cityNames (deleted nodes)
                if (cityNames.find(u) == cityNames.end() || cityNames.find(v) == cityNames.end())
                    continue;

                if (find(u) != find(v)) {
                    mstEdges.push_back(edge);
                    totalWeight += edge.weight;
                    unionSets(u, v);
                }
            }

            // Output the MST edges and total weight
            cout << "\nMinimum Spanning Tree (MST) edges:\n";
            for (auto &edge : mstEdges) {
                cout << cityNames[edge.src] << " - " << cityNames[edge.dest] << " : " << edge.weight << " km" << endl;
            }
            cout << "Total weight of MST: " << totalWeight << " km\n";
        }

    private:
        void DFSUtil(int v, vector<bool> &visited) {
            visited[v] = true;
            cout << cityNames[v] << " ";

            for (Pair &neighbor : adjList[v]) {
                int u = neighbor.first;
                if (!visited[u]) {
                    DFSUtil(u, visited);
                }
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

    int choice;
    do
    {
        cout << "The City Network Visualization System Menu:\n";
        cout << "[1] Display the city network\n";
        cout << "[2] Find the shortest path between two cities\n"
        cout << "[3] Display the MST\n";
        cout << "[4] Route Exploration (DFS)\n";
        cout << "[5] Network Expansion Exploration (BFS)\n";
        cout << "[6] Exit\n";
        cout << "Enter your choice (1 - 6): ";

        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1:
                graph.printGraph();
                break;
            case 2:
            {
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

                graph.findShortestPath(src, dest);
                break;
            }
            case 3:
                graph.findMST();
                break;
            case 4:
            {
                string startCity;
                cout << "Enter starting city for DFS: ";
                getline(cin, startCity);
                graph.DFS(startCity);
                break;
            }
            case 5:
            {
                string startCity;
                cout << "Enter starting city for BFS: ";
                getline(cin, startCity);
                graph.DFS(startCity);
                break;
            }
            case 6:
                cout << "Exiting the system.\n";
                break;
        }
    }
    while (choice != 6);

    return 0;
}

