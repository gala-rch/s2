#include <iostream>
#include <string>

//1
size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    for (char c : s) {
        hash += static_cast<size_t>(c);
    }
    return hash % max;
}

//2
size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        hash += static_cast<size_t>(s[i]) * (i + 1); 
    }
    return hash % max;
}

//3
size_t polynomial_rolling_hash(std::string const& s, size_t p, size_t m) {
    size_t hash = 0;
    size_t power = 1; 
    
    for (char c : s) {
        hash = (hash + static_cast<size_t>(c) * power) % m;
        power = (power * p) % m; 
    }
    
    return hash;
}

// Fonction pour tester nos fonctions de hachage
void test_hash_functions() {
    std::string test1 = "abc";
    std::string test2 = "cba";
    std::string test3 = "abcdefg";
    
    size_t max = 1000; 
    size_t p = 31;    
    size_t m = 1000000009;
    std::cout << "Test folding_string_hash:" << std::endl;
    std::cout << "Hash de \"" << test1 << "\": " << folding_string_hash(test1, max) << std::endl;
    std::cout << "Hash de \"" << test2 << "\": " << folding_string_hash(test2, max) << std::endl;
    std::cout << "(Devrait être identique car même caractères)" << std::endl;
    
    std::cout << "\nTest folding_string_ordered_hash:" << std::endl;
    std::cout << "Hash de \"" << test1 << "\": " << folding_string_ordered_hash(test1, max) << std::endl;
    std::cout << "Hash de \"" << test2 << "\": " << folding_string_ordered_hash(test2, max) << std::endl;
    std::cout << "(Devrait être différent car ordre différent)" << std::endl;
    
    std::cout << "\nTest polynomial_rolling_hash:" << std::endl;
    std::cout << "Hash de \"" << test1 << "\": " << polynomial_rolling_hash(test1, p, m) << std::endl;
    std::cout << "Hash de \"" << test2 << "\": " << polynomial_rolling_hash(test2, p, m) << std::endl;
    std::cout << "Hash de \"" << test3 << "\": " << polynomial_rolling_hash(test3, p, m) << std::endl;
}

int main() {
    test_hash_functions();
    return 0;
}