# Custom Encryption Algorithm
A multi-key text encryption algorithm with an example program.


## Encrypting Text
### BE SURE TO SAVE YOUR KEYS IN A SAFE LOCATION.
Include the CEA.h file to begin using this software.
>In this case the encrypted data will be outputted to the file "./encrypted_data.txt":
```c++
#include "CEA.h"
int main(void) {
  const char* input_file_location = "./input.txt";
  std::vector<uint_fast32_t> seed_packet;
  seed_packet.push_back(99247852);  //SEED ONE
  seed_packet.push_back(47582120);  //SEED TWO
  encrypt(input_file_location, seed_packet);
  return 0;
}
```

## Decrypting Text
>The decrypt function is used exactly the same as the encrypt function:
```c++
#include "CEA.h"
int main(void) {
  const char* input_file_location = "./input.txt";
  std::vector<uint_fast32_t> seed_packet;
  seed_packet.push_back(99247852);  //SEED ONE
  seed_packet.push_back(47582120);  //SEED TWO
  decrypt(input_file_location, seed_packet);
  return 0;
}
```

## How It Works
>First, we read the input file:
```c++
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
```
>Then, we generate a random number for each character in the input. We seed this with SEED/KEY ONE:
```c++
std::vector<int> generateSeeds(int seed, int number_of_seeds) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> output_vector;
    
    gen.seed(seed);
    for(int s = 0; s < number_of_seeds; s++) {
        output_vector.push_back(gen());
    }
    return output_vector;
}
```
>Next, we generate a random alphabet from each random number:
```c++
std::vector<char> generateRandomAlphabet(int seed) {
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
```
>After that, we replace each character in our input file with one at the same index in each character's respective random alphabet:
```c++
for(char c : input_data) {
    replacement_character = random_alphabets.at(current_alphabet).at((int)c - 32);  //random_alphabet -> current_alphabet -> c-32
    encrypted_data.push_back(replacement_character);
    current_alphabet++;
}
```
>Finally, we shift each character a random amount using a similar process:
```c++
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
```
>Decryption follows the same steps backwards.
```c++
void decrypt(const char* file_location, std::vector<int> seed_packet) {
    std::random_device rd;
    std::mt19937 SEED_ONE(rd());

    std::vector<std::vector<char>> random_alphabets;
    std::unordered_map<char, int> char_map;
    std::vector<char> unencrypted_data;
    std::vector<char> data;
    std::ofstream ofstream;
    int current_seed;

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
```
