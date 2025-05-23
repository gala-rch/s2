#include "node.hpp"

Node* create_node(int value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}

bool Node::is_leaf() const {
    return (left == nullptr && right == nullptr);
}

void Node::insert(int value) {
    if (value < this->value) {
        if (left == nullptr) {
            left = create_node(value);
        } else {
            left->insert(value);
        }
    } else {
        if (right == nullptr) {
            right = create_node(value);
        } else {
            right->insert(value);
        }
    }
}

int Node::height() const {
    if (this->is_leaf()) {
        return 1;
    }
    
    int left_height = 0;
    int right_height = 0;
    
    if (left != nullptr) {
        left_height = left->height();
    }
    
    if (right != nullptr) {
        right_height = right->height();
    }
    
    return 1 + std::max(left_height, right_height);
}

void Node::delete_children() {
    if (left != nullptr) {
        left->delete_children();
        delete left;
        left = nullptr;
    }
    
    if (right != nullptr) {
        right->delete_children();
        delete right;
        right = nullptr;
    }
}

void Node::display_infix() const {
    if (left != nullptr) {
        left->display_infix();
    }
    
    std::cout << value << " ";
    
    if (right != nullptr) {
        right->display_infix();
    }
}

std::vector<Node const*> Node::prefix() const {
    std::vector<Node const*> nodes;
    
    nodes.push_back(this);
    
    if (left != nullptr) {
        auto left_nodes = left->prefix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    
    if (right != nullptr) {
        auto right_nodes = right->prefix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    
    return nodes;
}

std::vector<Node const*> Node::postfix() const {
    std::vector<Node const*> nodes;
    
    if (left != nullptr) {
        auto left_nodes = left->postfix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    
    if (right != nullptr) {
        auto right_nodes = right->postfix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    
    nodes.push_back(this);
    
    return nodes;
}

Node*& most_left(Node*& node) {
    if (node->left == nullptr) {
        return node;
    } else {
        return most_left(node->left);
    }
}

bool remove(Node*& node, int value) {
    if (node == nullptr) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    }
    
    if (value > node->value) {
        return remove(node->right, value);
    }
    
    
    if (node->is_leaf()) {
        delete node;
        node = nullptr;
        return true;
    }
    
    if (node->left == nullptr) {
        Node* temp = node;
        node = node->right;
        delete temp;
        return true;
    }
    
    if (node->right == nullptr) {
        Node* temp = node;
        node = node->left;
        delete temp;
        return true;
    }
    

    Node*& successor = most_left(node->right);
    node->value = successor->value;
    return remove(successor, successor->value);
}

void delete_tree(Node* node) {
    if (node != nullptr) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

int Node::min() const {
    if (left == nullptr) {
        return value;
    } else {
        return left->min();
    }
}

int Node::max() const {
    if (right == nullptr) {
        return value;
    } else {
        return right->max();
    }
}