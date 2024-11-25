/***************************************************************************
* COMSC-210 | Lab 34 | Grant Luo
* Editor: CLion
* Compiler: Apple clang version 16.0.0
*/
#include <iostream>
#include <vector>
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

    return 0;
}

