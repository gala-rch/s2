#include "ScopedTimer.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

{
    ScopedTimer timer("nom du chronomètre");
    void bubble_sort(std::vector<int> & vec) {
        size_t n = vec.size();
        
        // Pour chaque itération, le plus grand élément "remonte" à la fin du tableau
        for (size_t i = 0; i < n - 1; i++) {
            // Derniers i éléments sont déjà triés, donc on parcourt jusqu'à n-i-1
            for (size_t j = 0; j < n - i - 1; j++) {
                // Si l'élément courant est plus grand que le suivant, on les échange
                if (vec[j] > vec[j + 1]) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
}