#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include <functional>
#include <limits>

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        // Exercice 1.1 - Ajouter un sommet
        void add_vertex(int const id) {
            if (adjacency_list.find(id) == adjacency_list.end()) {
                adjacency_list[id] = std::vector<WeightedGraphEdge>{};
            }
        }

        // Exercice 1.2 - Ajouter une arête orientée
        void add_directed_edge(int const from, int const to, float const weight = 1.0f) {
            add_vertex(from);
            add_vertex(to);
            
            adjacency_list[from].push_back({to, weight});
        }

        // Exercice 1.3 - Ajouter une arête non orientée
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f) {
            add_directed_edge(from, to, weight);
            add_directed_edge(to, from, weight);
        }
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        // Exercice 2.1 - Parcours en profondeur (DFS)
        void print_DFS(int const start) const {
            std::cout << "DFS from node " << start << ":" << std::endl << "Visited nodes: ";
            
            std::stack<int> stack;
            std::unordered_map<int, bool> visited;
            
            stack.push(start);
            
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();
                
                if (visited.find(current) == visited.end()) {
                    visited[current] = true;
                    std::cout << current << " ";
                    
                    if (adjacency_list.find(current) != adjacency_list.end()) {
                        for (auto it = adjacency_list.at(current).rbegin(); 
                             it != adjacency_list.at(current).rend(); ++it) {
                            if (visited.find(it->to) == visited.end()) {
                                stack.push(it->to);
                            }
                        }
                    }
                }
            }
            std::cout << std::endl;
        }

        // Exercice 2.2 - Parcours en largeur (BFS)
        void print_BFS(int const start) const {
            std::cout << "BFS from node " << start << ":" << std::endl << "Visited nodes: ";
            
            std::queue<int> queue;
            std::unordered_map<int, bool> visited;
            
            queue.push(start);
            visited[start] = true;
            
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                
                std::cout << current << " ";
                
                if (adjacency_list.find(current) != adjacency_list.end()) {
                    for (const auto& edge : adjacency_list.at(current)) {
                        if (visited.find(edge.to) == visited.end()) {
                            visited[edge.to] = true;
                            queue.push(edge.to);
                        }
                    }
                }
            }
            std::cout << std::endl;
        }

        // Exercice 2.3 (Bonus) - DFS avec callback
        void DFS(int const start, std::function<void(int const)> const& callback) const {
            std::stack<int> stack;
            std::unordered_map<int, bool> visited;
            
            stack.push(start);
            
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();
                
                if (visited.find(current) == visited.end()) {
                    visited[current] = true;
                    callback(current);  
                    
                    if (adjacency_list.find(current) != adjacency_list.end()) {
                        for (auto it = adjacency_list.at(current).rbegin(); 
                             it != adjacency_list.at(current).rend(); ++it) {
                            if (visited.find(it->to) == visited.end()) {
                                stack.push(it->to);
                            }
                        }
                    }
                }
            }
        }
    };

    // Exercice 1.4 - Construire un graphe à partir d'une matrice d'adjacence
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
        WeightedGraph graph;
        int n = adjacency_matrix.size();
        
        for (int i = 0; i < n; ++i) {
            graph.add_vertex(i);
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < adjacency_matrix[i].size(); ++j) {
                if (adjacency_matrix[i][j] != 0) {
                    graph.add_directed_edge(i, j, adjacency_matrix[i][j]);
                }
            }
        }
        
        return graph;
    }

}

//Exercice Dijkstra

// Étape 1
// Distances :
//     A (0)
// À visiter :
//     A (0)

// Étape 2
// Distances :
//     A (0), B (1, A), D (2, A)
// À visiter :
//     B (1), D (2)


// Étape 3
// Distances :
//     A (0), B (1, A), D (2, A), C (5, B)
// À visiter :
//     D (2), C (5)


// Étape 4
// Distances :
//     A (0), B (1, A), D (2, A), C (4, D), E (7, D)
// À visiter :
//     C (5), C (4), E (7)

// Étape 5
// Distances :
//     A (0), B (1, A), D (2, A), C (4, D), E (7, D), F (8, C)
// À visiter :
//     C (5), E (7), F (8)

// Chemin final
// Pour retrouver le chemin :
// E ← D ← A ← donc A → D → E
// Résultat final
//     Chemin : A → D → E
//     Coût total : 7

int main() {
    // Exercice 1.5 - Exemple d'utilisation
    std::cout << "=== Exercice 1: Construction de graphes ===" << std::endl;
    
    // Matrice d'adjacence de l'exemple du TD
    std::vector<std::vector<float>> matrix = {
        {0, 1, 0, 0, 2},
        {0, 0, 2, 4, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 6},
        {0, 0, 0, 0, 0}
    };
    
    // Créer le graphe à partir de la matrice
    Graph::WeightedGraph graph1 = Graph::build_from_adjacency_matrix(matrix);
    
    // Créer le même graphe manuellement
    Graph::WeightedGraph graph2;
    graph2.add_vertex(0);
    graph2.add_vertex(1);
    graph2.add_vertex(2);
    graph2.add_vertex(3);
    graph2.add_vertex(4);
    
    graph2.add_directed_edge(0, 1, 1.0f);
    graph2.add_directed_edge(0, 4, 2.0f);
    graph2.add_directed_edge(1, 2, 2.0f);
    graph2.add_directed_edge(1, 3, 4.0f);
    graph2.add_directed_edge(2, 3, 1.0f);
    graph2.add_directed_edge(3, 4, 6.0f);
    
    // Comparer les deux graphes
    if (graph1 == graph2) {
        std::cout << "Les deux graphes sont identiques !" << std::endl;
    } else {
        std::cout << "Les graphes sont différents." << std::endl;
    }
    
    std::cout << "\n=== Exercice 2: Parcours de graphes ===" << std::endl;
    
    // Test des parcours
    graph1.print_DFS(0);
    graph1.print_BFS(0);
    
    // Test du DFS avec callback
    std::cout << "DFS avec callback from node 0:" << std::endl << "Visited nodes: ";
    graph1.DFS(0, [](int const node_id) { std::cout << node_id << " "; });
    std::cout << std::endl;
    
    
    return 0;
}