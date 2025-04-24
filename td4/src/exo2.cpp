#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 1. 
int longueur_premier_mot(std::string const& str) {
    auto const is_space = [](char letter){ return letter == ' '; };
    auto debut = std::find_if_not(str.begin(), str.end(), is_space); 
    auto fin = std::find_if(debut, str.end(), is_space); 
    return std::distance(debut, fin); 
}

// 2. 
std::vector<std::string> split_string(std::string const& str) {
    std::vector<std::string> mots;
    auto const is_space = [](char letter){ return letter == ' '; };
    
    auto debut = str.begin();
    auto fin = str.begin();
    
    while (debut != str.end()) {
        debut = std::find_if_not(fin, str.end(), is_space);
        if (debut == str.end()) break; 
        
        fin = std::find_if(debut, str.end(), is_space);
        
        mots.push_back(std::string(debut, fin));
    }
    
    return mots;
}

int main() {
    std::string phrase;
    std::cout << "Entrez une phrase: ";
    std::getline(std::cin, phrase);
    
    std::cout << "Le premier mot contient " << longueur_premier_mot(phrase) << " caracteres." << std::endl;
    
    std::vector<std::string> mots = split_string(phrase);
    
    std::cout << "La phrase contient " << mots.size() << " mot(s):" << std::endl;
    for (std::string const& mot : mots) {
        std::cout << "'" << mot << "'" << std::endl;
    }
    
    return 0;
}