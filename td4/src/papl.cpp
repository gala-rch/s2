#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// 1. Fonction qui calcule la somme des carrés des éléments
int somme_carres(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 0, [](int somme, int element) { 
        return somme + element * element; 
     });
}

// 2. Fonction qui calcule le produit des éléments pairs
int produit_pairs(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 1, [](int produit, int element) { 
        return (element % 2 == 0) ? produit * element : produit; 
    });
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    
    std::cout << "Somme des carres: " << somme_carres(v) << std::endl;
    
    std::cout << "Produit des elements pairs: " << produit_pairs(v) << std::endl;
    
    return 0;
}
