// dijkstras.cpp
#include "dijkstras.h"

/*
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

struct Edge {
    int src=0;
    int dst=0;
    int weight=0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend istream& operator>>(istream& in, Edge& e)
    {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend ostream& operator<<(ostream& out, const Edge& e)
    {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public vector<vector<Edge>> {
    int numVertices=0;
};

inline istream& operator>>(istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

inline void file_to_graph(const string& filename, Graph& G) {
    ifstream in(filename);
    if (!in) {
        throw runtime_error("Can't open input file");
    }
    in >> G;
    in.close();
}
*/
struct Node {
    int vertex;
    int distance;
    
    Node(int v, int d) : vertex(v), distance(d) {}
    
    // Custom comparator for priority queue (min heap)
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);

    // Initialize priority queue (min heap)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distances[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u])
            continue;

        visited[u] = true;
        
        // Process neighbors
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }
    return distances;
}
/*
    while !pq.empty():
        current = pq.pop_top()
        u = current.vertex
        if graph.visited[u]:
            continue
        graph.visited[u] = true
        for each neighbor in graph.adjacencyList[u]:
            v = neighbor.vertex
            weight = neighbor.weight
            if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
                graph.distance[v] = graph.distance[u] + weight
                graph.previous[v] = u
                pq.push(Node(v, graph.distance[v]))*/

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;

    // If destination is the source, just return the source
    if (destination == 0) { // NEW
        path.push_back(0);
        return path;
    }

    // if destination isn't reachable
    if (previous[destination] == -1 && destination != 0)
        return path;

    // Reconstruct path
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);

        if (at == 0) break; // NEW
    }

    reverse(path.begin(), path.end());

    return path;
}
void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    
    // Print path without "Path:" prefix and with spaces instead of arrows
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << " ";
        }
    }
    
    // Print total cost on a new line
    cout << " \nTotal cost is " << total << endl;
}
/*
Here is pseudocode for Disjkstra’s algorithm:
struct Node:
    int vertex
    int weight

struct Graph:
    list adjacencyList
    list distance
    list previous
    list visited

function dijkstra(source, graph):
    n = graph.adjacencyList.size()

    graph.distance.resize(n, INT_MAX)
    graph.previous.resize(n, -1)
    graph.visited.resize(n, false)

    priorityQueue pq
    pq.push(Node(source, 0))
    graph.distance[source] = 0

    while !pq.empty():
        current = pq.pop_top()
        u = current.vertex
        if graph.visited[u]:
            continue
        graph.visited[u] = true
        for each neighbor in graph.adjacencyList[u]:
            v = neighbor.vertex
            weight = neighbor.weight
            if !graph.visited[v] and graph.distance[u] + weight < graph.distance[v]:
                graph.distance[v] = graph.distance[u] + weight
                graph.previous[v] = u
                pq.push(Node(v, graph.distance[v]))
end function*/