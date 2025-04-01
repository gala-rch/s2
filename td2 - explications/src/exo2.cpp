#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

// Définition des énumérations et de la structure Token
enum class Operator { ADD, SUB, MUL, DIV };
enum class TokenType { OPERATOR, OPERAND };

struct Token {
    TokenType type;
    float value;
    Operator op;
};

// Fonction pour séparer les éléments d'une chaîne par des espaces
std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

// Fonction pour créer un token à partir d'un nombre flottant
Token make_token(float value) {
    return Token{TokenType::OPERAND, value, Operator::ADD}; // Opérateur par défaut, ne sera pas utilisé
}

// Fonction pour créer un token à partir d'un opérateur
Token make_token(Operator op) {
    return Token{TokenType::OPERATOR, 0.0f, op}; // Valeur par défaut, ne sera pas utilisée
}

// Fonction pour vérifier si un token est un nombre flottant
bool is_floating(std::string const& s)
{
    bool has_dot = false;
    for (char c : s) {
        if (c == '.') {
            if (has_dot) return false;
            has_dot = true;
        } else if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Fonction pour convertir une chaîne en token
std::vector<Token> tokenize(std::vector<std::string> const& words)
{
    std::vector<Token> tokens;
    
    for (const auto& word : words) {
        if (is_floating(word)) {
            // Si c'est un nombre, on crée un token de type OPERAND
            tokens.push_back(make_token(std::stof(word)));
        } else {
            // Si c'est un opérateur, on crée un token de type OPERATOR
            if (word == "+") {
                tokens.push_back(make_token(Operator::ADD));
            } else if (word == "-") {
                tokens.push_back(make_token(Operator::SUB));
            } else if (word == "*") {
                tokens.push_back(make_token(Operator::MUL));
            } else if (word == "/") {
                tokens.push_back(make_token(Operator::DIV));
            } else {
                std::cerr << "Opérateur non reconnu: " << word << std::endl;
            }
        }
    }
    
    return tokens;
}

// Fonction pour évaluer une expression en NPI à partir d'un vecteur de tokens
float npi_evaluate(std::vector<Token> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            // Si c'est un nombre, on l'empile
            stack.push(token.value);
        } else {
            // Si c'est un opérateur, on dépile les deux derniers nombres
            // et on effectue l'opération
            
            // Vérification qu'il y a au moins deux opérandes dans la pile
            if (stack.size() < 2) {
                std::cerr << "Expression NPI invalide: pas assez d'opérandes" << std::endl;
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
            switch (token.op) {
                case Operator::ADD:
                    result = leftOperand + rightOperand;
                    break;
                case Operator::SUB:
                    result = leftOperand - rightOperand;
                    break;
                case Operator::MUL:
                    result = leftOperand * rightOperand;
                    break;
                case Operator::DIV:
                    if (rightOperand == 0) {
                        std::cerr << "Division par zéro!" << std::endl;
                        return 0.0f;
                    }
                    result = leftOperand / rightOperand;
                    break;
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
    std::vector<std::string> words = split_string(expression);
    
    // Conversion en tokens
    std::vector<Token> tokens = tokenize(words);
    
    // Évaluation de l'expression
    float result = npi_evaluate(tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}