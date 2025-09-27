#include "reedsolomon.h"
#include <iostream>

int main() {
    std::cout << "Reed-Solomon Error Correction Code Example\n";
    std::cout << "==========================================\n\n";

    // Create sample data
    unsigned char data[] = {'H', 'e', 'l', 'l', 'o', '!', '\0'};
    
    std::cout << "Original message: " << data << "\n";
    std::cout << "Message length: " << sizeof(data) - 1 << " bytes\n";

    // Example 1: Basic usage demonstration
    std::cout << "\nExample 1: Reed-Solomon Encoding\n";
    std::cout << "--------------------------------\n";
    
    int parity_length = 4;  // Number of parity bytes
    std::cout << "Would generate " << parity_length << " parity bytes for error correction.\n";
    
    // TODO: Uncomment when rs_encode is implemented
    /*
    std::vector<unsigned char> input_data(data, data + sizeof(data) - 1);
    std::vector<unsigned char> parity = rs_encode(input_data, parity_length);
    
    std::cout << "Parity bytes generated: ";
    for (size_t i = 0; i < parity.size(); ++i) {
        std::cout << std::hex << std::uppercase << (int)parity[i] << " ";
    }
    std::cout << std::dec << "\n";
    */

    // Example 2: Decoding demonstration
    std::cout << "\nExample 2: Reed-Solomon Decoding with Error Correction\n";
    std::cout << "-----------------------------------------------------\n";
    
    // TODO: Uncomment when rs_decode is implemented
    /*
    std::vector<unsigned char> encoded_data = input_data;
    encoded_data.insert(encoded_data.end(), parity.begin(), parity.end());
    
    // Simulate errors
    encoded_data[2] = '?';  // Introduce error
    
    std::vector<int> erasures;  // No erasures
    bool success = rs_decode(encoded_data, parity_length, erasures);
    
    if (success) {
        printf("Error correction successful!\n");
        printf("Corrected message: ");
        for (size_t i = 0; i < input_data.size(); ++i) {
            printf("%c", encoded_data[i]);
        }
        printf("\n");
    } else {
        printf("Error correction failed.\n");
    }
    */

    printf("\nNote: This is a template example.\n");
    printf("Implement rs_encode() and rs_decode() in reedsolomon.cc to see it work.\n");
    
    return 0;
}