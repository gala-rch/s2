#include <iostream>
#include <vector>
#include "node.hpp"

int main() {
    Node* root = create_node(5);
    
    root->insert(3);
    root->insert(7);
    root->insert(2);
    root->insert(4);
    root->insert(6);
    root->insert(8);
    root->insert(1);
    root->insert(9);
    root->insert(0);
    
    std::cout << "Parcours infixe: ";
    root->display_infix();
    std::cout << std::endl;
    

    
    std::vector<Node const*> nodes = root->prefix();
    int sum = 0;
    for (const auto& node : nodes) {
        sum += node->value;
    }
    std::cout << "Somme des valeurs: " << sum << std::endl;
    
    std::cout << "Hauteur de l'arbre: " << root->height() << std::endl;
    
    delete_tree(root);
    
    return 0;
}