#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

enum class Operator { ADD, SUB, MUL, DIV };
enum class TokenType { OPERATOR, OPERAND };

struct Token {
    TokenType type;
    float value;
    Operator op;
};

std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

Token make_token(float value) {
    return Token{TokenType::OPERAND, value, Operator::ADD}; 
}

Token make_token(Operator op) {
    return Token{TokenType::OPERATOR, 0.0f, op}; 
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

std::vector<Token> tokenize(std::vector<std::string> const& words)
{
    std::vector<Token> tokens;
    
    for (const auto& word : words) {
        if (is_floating(word)) {
            tokens.push_back(make_token(std::stof(word)));
        } else {
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

float npi_evaluate(std::vector<Token> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            stack.push(token.value);
        } else {
            
            if (stack.size() < 2) {
                std::cerr << "Expression NPI invalide: pas assez d'opérandes" << std::endl;
                return 0.0f;
            }
            
            float rightOperand { stack.top() };
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();
            
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
    
    std::vector<std::string> words = split_string(expression);
    
    std::vector<Token> tokens = tokenize(words);
    
    float result = npi_evaluate(tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}