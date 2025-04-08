#include <vector>
#include <algorithm>
#include <iostream> 

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }


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

int main(){
    std::vector<int> array{2,6,3,7,4,1};
    //bubble_sort(array);
    if (is_sorted(array)) {
        std::cout << "Le tableau est trie" << std::endl;
    } 
    else {
        std::cout << "Le tableau n'est pas trie" << std::endl;
    }
}