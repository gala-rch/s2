#include <iostream>
#include <string>
#include <algorithm>

bool est_palindrome(std::string const& str) {
    return std::equal(str.begin(), str.end(), str.rbegin());
}

int main() {
    std::string texte;
    std::cout << "Entrez un texte pour verifier s'il s'agit d'un palindrome: ";
    std::getline(std::cin, texte);
    
    if (est_palindrome(texte)) {
        std::cout << "'" << texte << "' est un palindrome." << std::endl;
    } else {
        std::cout << "'" << texte << "' n'est pas un palindrome." << std::endl;
    }
    
    return 0;
}