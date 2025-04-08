#include <vector>
#include <algorithm>
#include <iostream>


bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }


void merge_sort_merge(std::vector<int> & vec, size_t const left, size_t const middle, size_t const right) {
    std::vector<int> left_array(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> right_array(vec.begin() + middle + 1, vec.begin() + right + 1);
    
    size_t left_index = 0;
    size_t right_index = 0;
    size_t merge_index = left;
    
    while (left_index < left_array.size() && right_index < right_array.size()) {
        if (left_array[left_index] <= right_array[right_index]) {
            vec[merge_index] = left_array[left_index];
            left_index++;
        } else {
            vec[merge_index] = right_array[right_index];
            right_index++;
        }
        merge_index++;
    }
    
    while (left_index < left_array.size()) {
        vec[merge_index] = left_array[left_index];
        left_index++;
        merge_index++;
    }
    
    while (right_index < right_array.size()) {
        vec[merge_index] = right_array[right_index];
        right_index++;
        merge_index++;
    }
}

void merge_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    if (left >= right) {
        return;
    }
    
    size_t middle = left + (right - left) / 2;
    
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<int> & vec) {
    merge_sort(vec, 0, vec.size() - 1);
}

int main(){
    std::vector<int> array{2,6,3,7,4,1};
    merge_sort(array);
    if (is_sorted(array)) {
        std::cout << "Le tableau est trie" << std::endl;
    } 
    else {
        std::cout << "Le tableau n'est pas trie" << std::endl;
    }
}