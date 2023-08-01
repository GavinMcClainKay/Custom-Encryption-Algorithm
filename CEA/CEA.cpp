#include "CEA.h"

template <typename T>
int indexOf(std::vector<T> list, T item) {
    int current_char = 0;
    for(T c : list) {
        if(c == item) return current_char;
        current_char++;
    }
    return -1;
}

std::vector<char> getTextData(const char* file_location) {
    std::ifstream File(file_location);
    std::vector<char> full_file;

    char c = ' ';

    while(File.get(c)) {
        full_file.push_back(c);
    }
    File.close();
    return full_file;
}

std::vector<char> generateRandomAlphabet(uint_fast32_t seed) {
    std::uniform_int_distribution<> dist(33, 127); //uniform distribution of all characters on the keyboard
    std::unordered_map<char, bool> map_found; 
    std::vector<char> randomAlphabet;
    std::random_device rd;
    std::mt19937 gen(rd());

    int number_found_characters; 
    char generated_char;

    gen.seed(seed);
    number_found_characters = 0; 
    while(number_found_characters < 95) {
        generated_char = dist(gen);
        if(map_found[generated_char]) continue;
        else {
            randomAlphabet.push_back(generated_char); 
            map_found[generated_char] = true;
            number_found_characters++;
        }
    }

    return randomAlphabet;
}

std::vector<uint_fast32_t> generateSeeds(uint_fast32_t seed, int number_of_seeds) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<uint_fast32_t> output_vector;
    
    gen.seed(seed);
    for(int s = 0; s < number_of_seeds; s++) {
        output_vector.push_back(gen());
    }
    return output_vector;
}

std::vector<std::vector<char>> generateAlphabets(uint_fast32_t seed, int num_alphabets) {
    std::vector<std::vector<char>> alphabets;
    std::vector<uint_fast32_t> seeds;
    
    seeds = generateSeeds(seed, num_alphabets);
    for(int i = 0; i < num_alphabets; i++) {
        alphabets.push_back(generateRandomAlphabet(seeds[i]));
    }
    return alphabets;
}

void encrypt(const char* file_location, std::vector<uint_fast32_t> seed_packet) {
    std::random_device rd;
    std::mt19937 SEED_ONE(rd());

    std::vector<std::vector<char>> random_alphabets;
    std::unordered_map<char, int> char_map;
    std::vector<char> encrypted_data;
    std::vector<char> input_data;
    std::ofstream ofstream; 

    char replacement_character;
    int current_char_count;
    int current_alphabet;
    int index; 
    uint_fast32_t current_seed;

    //Replace characters in input file with random characters.
    current_alphabet = 0;
    input_data = getTextData(file_location);
    random_alphabets = generateAlphabets(seed_packet.at(1), input_data.size());  /*SEED TWO*/  
    for(char c : input_data) {
        replacement_character = random_alphabets.at(current_alphabet).at((int)c - 32);  //random_alphabet -> current_alphabet -> c-32
        encrypted_data.push_back(replacement_character);
        current_alphabet++;
    }

    //Shift characters a random amount.
    index = 0; 
    SEED_ONE.seed(seed_packet.at(0));
    for(char c : encrypted_data) {
        current_seed = SEED_ONE() % 1000;
        if(current_seed % 2 == 0) {
            encrypted_data.at(index) += current_seed;
        }
        else {
            encrypted_data.at(index) -= current_seed;
        }
        index++;
    }

    //Save to output file.
    ofstream.open("./encrypted_data.txt");
    for(char c : encrypted_data) {
        ofstream.put(c);
    }
    ofstream.close();
}

void decrypt(const char* file_location, std::vector<uint_fast32_t> seed_packet) {
    std::random_device rd;
    std::mt19937 SEED_ONE(rd());

    std::vector<std::vector<char>> random_alphabets;
    std::unordered_map<char, int> char_map;
    std::vector<char> unencrypted_data;
    std::vector<char> data;
    std::ofstream ofstream;
    uint_fast32_t current_seed;

    int current_char_count;
    int current_alphabet;
    int index;

    //Unshift characters a random amount.
    index = 0; 
    data = getTextData(file_location);
    SEED_ONE.seed(seed_packet.at(0));
    for(char c : data) {
        current_seed = SEED_ONE() % 1000;
        if(current_seed % 2 == 0) {
            data.at(index) -= current_seed;
        }
        else {
            data.at(index) += current_seed;
        }
        index++;
    }

    //Unrandomize characters.
    current_alphabet = 0;
    random_alphabets = generateAlphabets(seed_packet.at(1), data.size()); 
    for(char c : data) {
        index = indexOf(random_alphabets.at(current_alphabet), c);
        index += 32;
        unencrypted_data.push_back((char)index);
        current_alphabet++;
    }

    //Save to output file.
    ofstream.open("./unencrypted_data.txt");
    for(char c : unencrypted_data) {
        ofstream.put(c);
    }
    ofstream.close(); 
}