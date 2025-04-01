#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

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

float npi_evaluate(std::vector<std::string> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        if (is_floating(token)) {
            stack.push(std::stof(token));
        } else {
            
            if (stack.size() < 2) {
                std::cerr << "Expression NPI invalide: pas assez d'opérandes pour l'opérateur " << token << std::endl;
                return 0.0f;
            }
            
            float rightOperand { stack.top() };
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();
            
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
            
            stack.push(result);
        }
    }
    
    if (stack.size() != 1) {
        std::cerr << "Expression NPI invalide: trop d'opérandes" << std::endl;
        return 0.0f;
    }
    
    return stack.top();
}

int main()
{
    std::string expression;
    std::cout << "Entrez une expression en NPI (les éléments séparés par des espaces): ";
    std::getline(std::cin, expression);
    
    std::vector<std::string> tokens = split_string(expression);
    
    float result = npi_evaluate(tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}