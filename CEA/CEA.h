#pragma once

#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <unordered_map>

/*This function returns the first index of a given item in a standard library vector container.

Parameters:
    list: A standard vector.
    item: The character to find the first index of.*/
template <typename T>
int indexOf(std::vector<T> list, T item);

/*This function reads text data into a standard character vector/

Parameters: 
    file_location: A string representing the location of the file you wish to read.*/
std::vector<char> getTextData(const char* file_location);

/*This function returns a random alphabet including the characters index (33-127].

Parameters:
    seed: A uint_fast32_t (32-64 bit integer number also represented by the type "Seed") used to seed a random number generator.*/
std::vector<char> generateRandomAlphabet(uint_fast32_t seed);

/*This function returns a standard vector of uint_fast32_t (32-64 bit integer number also represented by the type "Seed")
that contains any number of random Seeds.

Parameters:
    seed: A uint_fast32_t (32-64 bit integer number also represented by the type "Seed").
    number_of_seeds: An integer number representing the amount of seeds returned.*/
std::vector<uint_fast32_t> generateSeeds(uint_fast32_t seed, int number_of_seeds);

/*This function uses generateSeeds() in order to randomly generate and return a standard vector of any number of random alphabets.
See generateRandomAlphabet().

Parameters:
    seed: A uint_fast32_t (32-64 bit integer number also represented by the type "Seed").
    num_alphabets: An integer number representing the number of alphabets to generate.*/
std::vector<std::vector<char>> generateAlphabets(uint_fast32_t seed, int num_alphabets);

/*Encrypts a given text file with 2 keys of type uint_fast32_t.
This function requires 2 keys to work properly, save the keys used as they are what you use to unencrypt the data later.
Saves data to ./encrypted_data.txt

Parameters:
    file_location: A string representing the file location of the text to be encrypted.
    seed_packet: A standard library vector<uint_fast32_t> that contains 2 keys.*/
void encrypt(const char* file_location, std::vector<uint_fast32_t> seed_packet);

/*Unencrypts a given text file with 2 keys of type uint_fast32_t.
This function requires 2 keys to work properly, they are the 2 keys used to encrypt the data originally.
Saves data to ./unencrypted_data.txt

Parameters:
    file_location: A string representing the file location of the text to be unencrypted.
    seed_packet: A standard library vector<uint_fast32_t> that contains 2 keys.*/
void decrypt(const char* file_location, std::vector<uint_fast32_t> seed_packet);