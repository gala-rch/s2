#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <random>
#include <iomanip>


enum class Insect {
    ClassicBee,
    Ladybug,
    Butterfly,
    Dragonfly,
    Ant,
    Grasshopper,
    Beetle,
    Wasp,
    Caterpillar,
    Spider,
    GuimielBee
};

std::vector<Insect> const insect_values {
    Insect::ClassicBee,
    Insect::Ladybug,
    Insect::Butterfly,
    Insect::Dragonfly,
    Insect::Ant,
    Insect::Grasshopper,
    Insect::Beetle,
    Insect::Wasp,
    Insect::Caterpillar,
    Insect::Spider,
    Insect::GuimielBee
};

std::unordered_map<Insect, std::string> const insect_to_string = {
    {Insect::ClassicBee, "ClassicBee"},
    {Insect::Ladybug, "Ladybug"},
    {Insect::Butterfly, "Butterfly"},
    {Insect::Dragonfly, "Dragonfly"},
    {Insect::Ant, "Ant"},
    {Insect::Grasshopper, "Grasshopper"},
    {Insect::Beetle, "Beetle"},
    {Insect::Wasp, "Wasp"},
    {Insect::Caterpillar, "Caterpillar"},
    {Insect::Spider, "Spider"},
    {Insect::GuimielBee, "GuimielBee"}
};

std::vector<int> const expected_insect_counts {
    75, // ClassicBee
    50, // Ladybug
    100, // Butterfly
    20, // Dragonfly
    400, // Ant
    150, // Grasshopper
    60, // Beetle
    10, // Wasp
    40, // Caterpillar
    90, // Spider 
    5, // GuimielBee
};

std::vector<std::pair<Insect, int>> get_insect_observations(
    size_t const number_of_observations,
    std::vector<float> const& insect_probabilities,
    unsigned int const seed = std::random_device{}()
) {
    // Create a random engine with a given seed
    std::default_random_engine random_engine{seed};

    auto rand_insect_index { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        size_t const random_insect_index { rand_insect_index() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        // If we have already seen the same insect, increment the count on the last observation
        if(!observations.empty() && observations.back().first == random_insect) {
            observations.back().second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

//1
std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    int total = 0;
    for (int count : counts) {
        total += count;
    }
    
    std::vector<float> probabilities;
    probabilities.reserve(counts.size());
    
    for (int count : counts) {
        probabilities.push_back(static_cast<float>(count) / total);
    }
    
    return probabilities;
}

int main() {
    std::vector<float> expected_probabilities = probabilities_from_count(expected_insect_counts);
    
    std::vector<std::pair<Insect, int>> observations = get_insect_observations(10000, expected_probabilities, 12345);
    
    std::unordered_map<Insect, int> observed_counts;
    
    for (Insect insect : insect_values) {
        observed_counts[insect] = 0;
    }
    
    for (const auto& observation : observations) {
        observed_counts[observation.first] += observation.second;
    }
    
    std::cout << "Nombre d'insectes observés:" << std::endl;
    for (Insect insect : insect_values) {
        std::cout << insect_to_string.at(insect) << ": " << observed_counts[insect] << std::endl;
    }
    
    std::vector<int> observed_counts_vector;
    observed_counts_vector.reserve(insect_values.size());
    
    for (Insect insect : insect_values) {
        observed_counts_vector.push_back(observed_counts[insect]);
    }
    
    std::vector<float> observed_probabilities = probabilities_from_count(observed_counts_vector);
    
    std::cout << "\nProbabilities of observed insects vs expected probabilities" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    
    const float THRESHOLD = 0.01; 
    
    for (size_t i = 0; i < insect_values.size(); ++i) {
        Insect insect = insect_values[i];
        float observed_prob = observed_probabilities[i];
        float expected_prob = expected_probabilities[i];
        float diff = std::abs(observed_prob - expected_prob);
        
        std::cout << insect_to_string.at(insect) << " : " 
                  << observed_prob << " vs " << expected_prob << " "
                  << (diff <= THRESHOLD ? "OK" : "BAD") << std::endl;
    }
    
    return 0;
}