#ifndef REEDSOLOMON_H
#define REEDSOLOMON_H

#include <vector>
/**
 * @brief Encode data using the Reed-Solomon algorithm.
 *
 * Generates parity bytes for the given input data.
 *
 * @param data Input data to encode.
 * @param parity_len Number of parity bytes to generate.
 * @return std::vector<unsigned char> Vector containing the generated parity bytes.
 */
std::vector<unsigned char> rs_encode(const std::vector<unsigned char>& data, int parity_len);

/**
 * @brief Decode data using the Reed-Solomon algorithm.
 *
 * Attempts to recover erased bytes in the received data using the provided parity information.
 *
 * @param data Received data (including parity bytes). This vector may be modified during decoding.
 * @param parity_len Number of parity bytes present in the data.
 * @param erasures Indices of erased bytes in the data vector.
 * @return true if decoding was successful, false otherwise.
 */
bool rs_decode(std::vector<unsigned char>& data, int parity_len, const std::vector<int>& erasures);

#endif // REEDSOLOMON_H
