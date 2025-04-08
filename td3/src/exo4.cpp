#include <iostream>
#include <vector>


int search(std::vector<int> vec, int const value){
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (vec[middle] == value) {
            return middle; 
        } else if (vec[middle] < value) {
            left = middle + 1; 
        } else {
            right = middle - 1; 
        }
    }
    return -1; 


}

int main(){
    std::vector<int> array1{1, 2, 2, 3, 4, 8, 12};
    std::vector<int> array2{1, 2, 3, 3, 6, 14, 12, 15};
    std::vector<int> array3{2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::vector<int> array4{5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<int> array5{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> value{8,15,16,6,10};
    std::vector<std::vector<int>> arrays = {array1, array2, array3, array4, array5};   
    for(int i = 0; i < 5; i++){
        int index = search(arrays[i],value[i]);
        if (index != -1) {
            std::cout << "L'element " << value[i] << " est trouve a l'indice " << index << std::endl;
        } else {
            std::cout << "L'element " << value[i] << " n'est pas trouve" << std::endl;
        }
    }
}