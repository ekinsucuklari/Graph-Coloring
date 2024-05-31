#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <string>
#include <iomanip>
using namespace std;

class Graph {
private:
    int V;
    vector<unordered_set<int>> graph;

public:
    Graph(int vertices) : V(vertices), graph(vertices) {}

    void add_edge(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int dsatur_coloring() {
        vector<int> degree(V, 0);
        vector<int> color(V, -1);
        int max_degree = 0;
        int max_degree_vertex = -1;

        for (int v = 0; v < V; ++v) {
            degree[v] = graph[v].size();
            if (degree[v] > max_degree) {
                max_degree = degree[v];
                max_degree_vertex = v;
            }
        }

        color[max_degree_vertex] = 0;

        for (int i = 1; i < V; ++i) {
            int selected_vertex = -1;
            int max_dsatur = -1;

            for (int v = 0; v < V; ++v) {
                if (color[v] == -1) {
                    unordered_set<int> colored_neighbors;
                    for (int u : graph[v]) {
                        if (color[u] != -1)
                            colored_neighbors.insert(color[u]);
                    }
                    int dsatur = colored_neighbors.size();
                    if (dsatur > max_dsatur) {
                        max_dsatur = dsatur;
                        selected_vertex = v;
                    }
                    else if (dsatur == max_dsatur && degree[v] > degree[selected_vertex]) {
                        selected_vertex = v;
                    }
                }
            }

            unordered_set<int> used_colors;
            for (int u : graph[selected_vertex]) {
                if (color[u] != -1)
                    used_colors.insert(color[u]);
            }

            int chosen_color = 0;
            while (used_colors.find(chosen_color) != used_colors.end())
                chosen_color++;

            color[selected_vertex] = chosen_color;
        }

        int num_colors = *max_element(color.begin(), color.end()) + 1;

        cout << "Kullanilan Renk Sayisi: " << num_colors << endl;
        for (int v = 0; v < V; ++v)
            cout << "Kose " << v << " --> Renk " << color[v] << endl;

        return num_colors;
    }
};

Graph create_graph_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        exit(1);
    }

    int V, E;
    file >> V >> E;
    Graph g(V);
    int u, v;
    for (int i = 0; i < E; ++i) {
        file >> u >> v;
        g.add_edge(u, v);
    }
    return g;
}

int main() {

    string graph_file = "C:/Users/LENOVO/Desktop/graph coloring/graph coloring/data/gc_20_1"; // Dosya adını değiştirin
    
    auto start_time = chrono::high_resolution_clock::now(); // Başlangıç zamanı

    Graph g = create_graph_from_file(graph_file);
    g.dsatur_coloring();

    auto end_time = chrono::steady_clock::now(); // Bitiş zamanı

    // Geçen süreyi hesapla ve ekrana yazdır
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_seconds = std::chrono::duration<double>(end_time - start_time).count();
    std::cout << "Programin calisma suresi: " << std::fixed << std::setprecision(2) << duration_seconds << " saniye" << std::endl;

    return 0;
}


