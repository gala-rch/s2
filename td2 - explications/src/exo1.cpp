#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

// Fonction pour séparer les éléments d'une chaîne par des espaces
std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

// Fonction pour vérifier si un token est un nombre flottant
bool is_floating(std::string const& s)
{
    bool has_dot = false;
    for (char c : s) {
        if (c == '.') {
            // On ne permet qu'un seul point décimal
            if (has_dot) return false;
            has_dot = true;
        } else if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Fonction pour évaluer une expression en NPI
float npi_evaluate(std::vector<std::string> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        if (is_floating(token)) {
            // Si c'est un nombre, on le convertit en float et on l'empile
            stack.push(std::stof(token));
        } else {
            // Si c'est un opérateur, on dépile les deux derniers nombres
            // et on effectue l'opération
            
            // Vérification qu'il y a au moins deux opérandes dans la pile
            if (stack.size() < 2) {
                std::cerr << "Expression NPI invalide: pas assez d'opérandes pour l'opérateur " << token << std::endl;
                return 0.0f;
            }
            
            // Je récupère l'élément en haut de la pile (opérande droite)
            float rightOperand { stack.top() };
            // Je l'enlève de la stack
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();
            
            // En fonction de l'opérateur, je calcule le résultat
            float result;
            if (token == "+") {
                result = leftOperand + rightOperand;
            } else if (token == "-") {
                result = leftOperand - rightOperand;
            } else if (token == "*") {
                result = leftOperand * rightOperand;
            } else if (token == "/") {
                if (rightOperand == 0) {
                    std::cerr << "Division par zéro!" << std::endl;
                    return 0.0f;
                }
                result = leftOperand / rightOperand;
            } else {
                std::cerr << "Opérateur non reconnu: " << token << std::endl;
                return 0.0f;
            }
            
            // Je pousse le résultat sur la pile
            stack.push(result);
        }
    }
    
    // Vérification qu'il reste exactement un élément dans la pile
    if (stack.size() != 1) {
        std::cerr << "Expression NPI invalide: trop d'opérandes" << std::endl;
        return 0.0f;
    }
    
    // Le résultat final est le seul élément restant dans la pile
    return stack.top();
}

int main()
{
    std::string expression;
    std::cout << "Entrez une expression en NPI (les éléments séparés par des espaces): ";
    std::getline(std::cin, expression);
    
    // Séparation des tokens
    std::vector<std::string> tokens = split_string(expression);
    
    // Évaluation de l'expression
    float result = npi_evaluate(tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}