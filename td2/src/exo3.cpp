#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <iterator>
#include <cctype>

enum class Operator { ADD, SUB, MUL, DIV, OPEN_PAREN, CLOSE_PAREN };
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
            return 0; 
        default:
            return 0;
    }
}

std::vector<Token> infix_to_npi_tokens(std::string const& expression)
{
    std::vector<std::string> words = split_string(expression);
    
    std::vector<Token> infix_tokens = tokenize(words);
    
    std::vector<Token> output; 
    std::stack<Token> op_stack; 
    
    for (const auto& token : infix_tokens) {
        if (token.type == TokenType::OPERAND) {
            output.push_back(token);
        } else {
            if (token.op == Operator::OPEN_PAREN) {
                op_stack.push(token);
            } else if (token.op == Operator::CLOSE_PAREN) {
                while (!op_stack.empty() && op_stack.top().op != Operator::OPEN_PAREN) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                
                if (!op_stack.empty()) {
                    op_stack.pop();
                } else {
                    std::cerr << "Erreur: parenthèses non équilibrées." << std::endl;
                }
            } else {
                while (!op_stack.empty() && 
                       op_stack.top().op != Operator::OPEN_PAREN &&
                       operator_precedence(op_stack.top().op) >= operator_precedence(token.op)) {
                    output.push_back(op_stack.top());
                    op_stack.pop();
                }
                
                op_stack.push(token);
            }
        }
    }
    
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
                default:
                    std::cerr << "Opérateur non reconnu!" << std::endl;
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
    
    std::vector<Token> npi_tokens = infix_to_npi_tokens(expression);
    
    std::cout << "Expression en NPI: ";
    for (const auto& token : npi_tokens) {
        print_token(token);
    }
    std::cout << std::endl;
    
    float result = npi_evaluate(npi_tokens);
    
    std::cout << "Résultat: " << result << std::endl;
    
    return 0;
}