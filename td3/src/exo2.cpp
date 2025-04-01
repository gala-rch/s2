#include <vector>
#include <algorithm>
bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

void merge_sort_merge(std::vector<float> & vec, size_t const left, size_t const middle, size_t const right) {
    // Créer des copies temporaires des sous-tableaux
    std::vector<float> left_array(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<float> right_array(vec.begin() + middle + 1, vec.begin() + right + 1);
    
    // Indices pour parcourir les sous-tableaux temporaires
    size_t left_index = 0;
    size_t right_index = 0;
    size_t merge_index = left;
    
    // Fusionner les deux sous-tableaux triés
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
    
    // Copier les éléments restants du sous-tableau gauche
    while (left_index < left_array.size()) {
        vec[merge_index] = left_array[left_index];
        left_index++;
        merge_index++;
    }
    
    // Copier les éléments restants du sous-tableau droit
    while (right_index < right_array.size()) {
        vec[merge_index] = right_array[right_index];
        right_index++;
        merge_index++;
    }
}

void merge_sort(std::vector<float> & vec, size_t const left, size_t const right) {
    // Condition d'arrêt: tableau de taille 1 ou vide
    if (left >= right) {
        return;
    }
    
    // Trouver le milieu du tableau
    size_t middle = left + (right - left) / 2;
    
    // Trier récursivement les deux moitiés
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    
    // Fusionner les deux moitiés triées
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<float> & vec) {
    merge_sort(vec, 0, vec.size() - 1);
}