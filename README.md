# Custom Encryption Algorithm
A multi-key text encryption algorithm with an example program.


## Encrypting Text
### BE SURE TO SAVE YOUR KEYS IN A SAFE LOCATION.
Include the CEA.h file to begin using this software.
>`In this case the encrypted data will be outputted to the file "./encrypted_data.txt":`
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
>`The decrypt function is used exactly the same as the encrypt function:`
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
>`First, we read the input file. Then we generate a random number for each character in the input. We seed this with SEED/KEY ONE.`
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
