#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

enum class CardKind {
    Heart,
    Diamond,
    Club,
    Spade,
};

enum class CardValue {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

struct Card {
    CardKind kind;
    CardValue value;
    
    //1
    bool operator==(const Card& other) const {
        return kind == other.kind && value == other.value;
    }
    
    //2,3
    // Il y a 13 valeurs possibles (de 2 à As) et 4 couleurs
    // On peut créer un hash unique avec: kind * 13 + value
    size_t hash() const {
        size_t kind_value = static_cast<size_t>(kind);
        size_t card_value = static_cast<size_t>(value);
        
        return kind_value * 13 + card_value;
    }
};

namespace std {
    template<>
    struct hash<Card> {
        size_t operator()(Card const& card) const {
            return card.hash();
        }
    };
}

// Fonction pour obtenir le nom d'une carte
std::string card_name(Card const& card) {
    std::string name {};

    unsigned int card_value {(static_cast<unsigned int>(card.value)+2) % 14};

    if (card_value < 10) {
        name += '0' + std::to_string(card_value);
    }else if (card_value == 10) {
        name += "10";
    }else if (card_value == 11) {
        name += 'J';
    }else if (card_value == 12) {
        name += 'Q';
    }else if (card_value == 13) {
        name += 'K';
    }

    name += " of ";

    if (card.kind == CardKind::Heart) {
        name += "Heart";
    }else if (card.kind == CardKind::Diamond) {
        name += "Diamond";
    }else if (card.kind == CardKind::Club) {
        name += "Club";
    }else if (card.kind == CardKind::Spade) {
        name += "Spade";
    }
    return name;
}

// Fonction pour générer des cartes aléatoires
std::vector<Card> get_cards(size_t const size) {
    std::vector<Card> cards {};
    cards.reserve(size);
    for (size_t i {0}; i < size; ++i) {
        cards.push_back({static_cast<CardKind>(rand() % 4), static_cast<CardValue>(rand() % 13)});
    }
    return cards;
}

int main() {
    srand(time(nullptr));
    
    std::vector<Card> cards = get_cards(100);
    
    std::unordered_map<Card, int> card_counts;
    
    for (const Card& card : cards) {
        card_counts[card]++;
    }
    
    std::cout << "Comptage des cartes (100 cartes aléatoires):" << std::endl;
    for (const auto& [card, count] : card_counts) {
        std::cout << card_name(card) << ": " << count << std::endl;
    }
    
    std::cout << "\nNombre de cartes distinctes: " << card_counts.size() << std::endl;
    
    std::cout << "\nTest de la fonction de hachage:" << std::endl;
    
    Card card1 = {CardKind::Heart, CardValue::Ace};
    Card card2 = {CardKind::Heart, CardValue::King};
    Card card3 = {CardKind::Spade, CardValue::Ace};
    
    std::cout << "Hash de " << card_name(card1) << ": " << card1.hash() << std::endl;
    std::cout << "Hash de " << card_name(card2) << ": " << card2.hash() << std::endl;
    std::cout << "Hash de " << card_name(card3) << ": " << card3.hash() << std::endl;
    
    return 0;
}