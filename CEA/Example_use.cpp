#include "CEA.cpp"
#include <iostream>
#include <stdlib.h>

int main(void) {
    int input = 0; 
    char* file_location = (char*) malloc(sizeof(char) * 256);
    std::vector<uint_fast32_t> seed_packet;
    uint_fast32_t temp = 0; 
    //check for valid input
    while(true) {
        std::cout << "Would you like to encrypt(1) or decrypt(2) a text file? \n Please select a number 1 or 2.\n";
        std::cin >> input; 
        
        if(input < 1 || input > 2) continue;
        std::cout << "Please input the file location:\n";
        std::cin >> file_location;

        std::cout << "Please enter the first key:\n";
        std::cin >> temp; 
        seed_packet.push_back(temp);

        std::cout << "Please enter the second key:\n";
        std::cin >> temp; 
        seed_packet.push_back(temp);
        
        switch (input)
        {
        case 1:
            encrypt(file_location, seed_packet);
            std::cout << "File successfully encrypted to ./encrypted_data.txt, SAVE YOUR KEYS!!!" << std::endl;
            break;
        
        case 2:
            decrypt(file_location, seed_packet);
            std::cout << "File successfully unencrypted to ./unencrypted_data.txt" << std::endl; 
            break;
        }
        break;
    }
    std::cout << "Press any key to exit the program." << std::endl;
    std::cin;
    return 0;

}