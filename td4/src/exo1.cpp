#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric> 

int main()
{
    //1.
    std::vector<int> vector;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 100);
    
    for (int i = 0; i < 10; ++i) {
        vector.push_back(distrib(gen));
    }
    
    // 2. 
    std::cout << "Contenu du vecteur: " << std::endl;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 3. 
    int nombre;
    std::cout << "Entrez un nombre a rechercher: ";
    std::cin >> nombre;
    
    auto it = std::find(vector.begin(), vector.end(), nombre);
    if (it != vector.end()) {
        std::cout << "Le nombre " << nombre << " est present dans le vecteur." << std::endl;
    } else {
        std::cout << "Le nombre " << nombre << " n'est pas present dans le vecteur." << std::endl;
    }
    
    // 4. 
    int occurrences = std::count(vector.begin(), vector.end(), nombre);
    std::cout << "Le nombre " << nombre << " apparait " << occurrences << " fois dans le vecteur." << std::endl;
    
    // 5. 
    std::sort(vector.begin(), vector.end());
    
    std::cout << "Vecteur trie: " << std::endl;
    for (int element : vector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // 6. 
    int somme = std::accumulate(vector.begin(), vector.end(), 0);
    std::cout << "La somme des elements du vecteur est: " << somme << std::endl;
    
    return 0;
}