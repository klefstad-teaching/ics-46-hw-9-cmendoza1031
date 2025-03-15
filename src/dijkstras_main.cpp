// dijkstras_main.cpp
#include "dijkstras.h"

int main() {
    try {
        Graph G;
        file_to_graph("small.txt", G);
        
        // Source vertex is always 0
        int source = 0;
        vector<int> previous;
        
        // Run Dijkstra's algorithm
        vector<int> distances = dijkstra_shortest_path(G, source, previous);
        
        // Print shortest paths from source to all vertices
        cout << "Shortest paths from vertex " << source << ":" << endl;
        for (int i = 0; i < G.numVertices; ++i) {
            vector<int> path = extract_shortest_path(distances, previous, i);
            if (!path.empty()) {
                print_path(path, distances[i]);
            } else if (i != source) {
                cout << "No path to vertex " << i << endl;
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
