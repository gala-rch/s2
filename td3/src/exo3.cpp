#include "ScopedTimer.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <ctime>

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void bubble_sort(std::vector<int> & vec) {
    size_t n = vec.size();
    
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main() {
    std::srand(std::time(nullptr));
    
    std::vector<size_t> sizes = {100, 1000, 10000, 50000};
    
    for (size_t size : sizes) {
        std::cout << "=== Test avec " << size << " elements ===" << std::endl;
        
        //création de deux vecteurs iddentiques pour une comparaison égale
        std::vector<int> vec1 = generate_random_vector(size);
        std::vector<int> vec2 = vec1; 
        
        {
            ScopedTimer timer("Bubble Sort");
            bubble_sort(vec1);
        }
        
        {
            ScopedTimer timer("std::sort");
            std::sort(vec2.begin(), vec2.end());
        }
        

        std::cout << std::endl;
    }
    
    return 0;
}
//L'algorithme std::sort est plus rapide que l'algorithme de tri à bulle, en particulier pour les grands tableaux.