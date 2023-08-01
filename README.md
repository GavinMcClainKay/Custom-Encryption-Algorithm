# Custom Encryption Algorithm
A multi-key text encryption algorithm with an example program.
**NOT TO BE USED FOR SERIOUS SECURITY MEASURES UNLESS YOU UNDERSTAND THE RISKS INVOLVED.**

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

## Information Regarding Encryption Generation
This program uses the standard template library `mersenne_twister_engine` to generate random `alphabets`.
Each `character` has it's own unique `alphabet`, where the `value` of the original `character` corresponds to the `index` of the `random_character` in the generated `alphabet`.
This is easily reversable with the `seed` used to originally generate the `alphabets`.
This represents a `substitution`.
A second `seed` is then used to generate a `random_number` for each `character` in the already randomized data.
Each `random_number` is then cut off at the thousands place, and is added or subtracted to the data `character` by `character`. 
This represents a `shift`. 
