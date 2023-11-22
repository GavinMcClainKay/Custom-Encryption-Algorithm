#include "CEA.h"

int main(void) {
    const char* inputfile_location = "./example_input.txt";
    std::vector<int> seed_packet = std::vector<int>();
    seed_packet.push_back(115091215); //seed one
    seed_packet.push_back(257881923); //seed two

    encrypt(inputfile_location, seed_packet);
    return 0;
}