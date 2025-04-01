#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

// Définition des énumérations et de la structure Token
enum class Operator { ADD, SUB, MUL, DIV, OPEN_PAREN, CLOSE_PAREN };
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

// Fonction pour convertir une chaîne en token (infixe)
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
            } else if (word == "(") {
                tokens.push_back(make_token(Operator::OPEN_PAREN));
            } else if (word == ")") {
                tokens.push_back(make_token(Operator::CLOSE_PAREN));
            } else {
                std::cerr << "Opérateur non reconnu: " << word << std::endl;
            }
        }
    }
    
    return tokens;
}

// Fonction pour définir la priorité des opérateurs
size_t operator_precedence(Operator const op)
{
    switch (op) {
        case Operator::ADD:
        case Operator::SUB:
            return 1;
        case Operator::MUL:
        case Operator::DIV:
            return 2;
        case Operator::OPEN_PAREN:
        case Operator::CLOSE_PAREN:
            return 0; // Priorité la plus basse pour les parenthèses
        default:
            return 0;
    }
}

// Fonction pour convertir une expression en notation infixe en NPI
std::vector<Token> infix_to_npi_tokens(std::string const& expression)
{
    // Séparation des tokens de l'expression infixe
    std::vector<std::string> words = split_string(expression);
    
    // Conversion en tokens
    std::vector<Token> infix_tokens = tokenize(words);
    
    std::vector<Token> output; // Résultat en NPI
    std::stack<Token> op_stack; // Pile des opérateurs
    
    for (const auto& token : infix_tokens) {
        if (token.type == TokenType::OPERAND) {
            // Si c'est un nombre, on l'ajoute à la sortie
            output.push_back(token);
        } else {
            // Si c'est un opérateur
            if (token.op == Operator::OPEN_PAREN) {
                // Si c'est une parenthèse ouvrante, on la met sur la pile
                op_stack.push(token);
            } else if (token.op == Operator::CLOSE_PAREN) {
                // Si c'est une parenthèse fermante, on dépile les opérateurs
                // jusqu'à trouver une parenthèse ouvrante
                while (!op_stack.empty() && op_stack.top().op != Operator::OPEN_PAREN) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                
                // On enlève la parenthèse ouvrante de la pile (sans l'ajouter à la sortie)
                if (!op_stack.empty()) {
                    op_stack.pop();
                } else {
                    std::cerr << "Erreur: parenthèses non équilibrées." << std::endl;
                }
            } else {
                // Si c'est un autre opérateur
                // On dépile les opérateurs de priorité supérieure ou égale
                while (!op_stack.empty() && 
                       op_stack.top().op != Operator::OPEN_PAREN &&
                       operator_precedence(op_stack.top().op) >= operator_precedence(token.op)) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                
                // On empile l'opérateur courant
                op_stack.push(token);
            }
        }
    }
    
    // On dépile les opérateurs restants et on les ajoute à la sortie
    while (!op_stack.empty()) {
        if (op_stack.top().op == Operator::OPEN_PAREN) {
            std::cerr << "Erreur: parenthèses non équilibrées." << std::endl;
            op_stack.pop();
        } else {
            output.push_back(op_stack.top());
            op_stack.pop();
        }
    }
    
    return output;
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
                default:
                    std::cerr << "Opérateur non reconnu!" << std::endl;
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

// Fonction d'aide pour afficher un token
void print_token(const Token& token) {
    if (token.type == TokenType::OPERAND) {
        std::cout << token.value << " ";
    } else {
        switch (token.op) {
            case Operator::ADD: std::cout << "+ "; break;
            case Operator::SUB: std::cout << "- "; break;
            case Operator::MUL: std::cout << "* "; break;
            case Operator::DIV: std::cout << "/ "; break;
            case Operator::OPEN_PAREN: std::cout << "( "; break;
            case Operator::CLOSE_PAREN: std::cout << ") "; break;
        }
    }
}

int main()
{
    std::string expression;
    std::cout << "Entrez une expression en notation infixe (avec des espaces entre chaque élément): ";
    std::getline(std::cin, expression);
    
    // Conversion en NPI
    std::vector<Token> npi_tokens = infix_to_npi_tokens(expression);
    
    // Affichage de l'expression en NPI
    std::cout << "Expression en NPI: ";
    for (const auto& token : npi_tokens) {
        print_token(token);
    }
    std::cout << std::endl;
    
    // Évaluation de l'expression
    float result = npi_evaluate(npi_tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}