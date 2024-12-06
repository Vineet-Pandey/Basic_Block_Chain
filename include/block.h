/**
 * @file block.h
 * @brief Definition of the Block class used in the IronBlock namespace.
 *
 * This file contains the implementation of the Block class, which represents
 * a block in a blockchain. It includes methods for hashing data and
 * returning the block hash.
 *
 * @author vineet
 * @date 12/6/24
 */

#ifndef BLOCK_H
#define BLOCK_H
#include "utility.h"
#include <ctime>
#include <sodium.h>
#include <sstream>
namespace IronBlock {
/**
 * @class Block
 * @brief Represents a block in the blockchain.
 *
 * The Block class contains information such as the index, data, timestamp,
 * previous block hash, and the block hash itself. It also provides methods
 * to hash the block data using the Sodium library.
 */
class Block {

public:
  /**
   * @brief Index of the block in the blockchain.
   */
  int index;
  /**
   * @brief Data contained within the block.
   */
  std::string data;
  /**
   * @brief Hash of the previous block in the blockchain.
   */
  std::string previous_block_hash;
  /**
   * @brief Timestamp of when the block was created.
   */
  std::time_t timestamp;
  /**
   * @brief Hash of the current block.
   */
  std::string block_hash;
  /**
   * @brief Constructs a new Block object.
   *
   * @param index The index of the block in the blockchain.
   * @param data The data to be stored in the block.
   * @param previous_block_hash The hash of the previous block in the
   * blockchain.
   */
  Block(int index, std::string &data, std::string &previous_block_hash)
      : index(index), data(data), previous_block_hash(previous_block_hash) {
    timestamp = std::time(nullptr);
  }
  /**
   * @brief Hashes the provided data using the Sodium library.
   *
   * This method generates a cryptographic hash of the given data using the
   * Sodium library's generic hash function.
   *
   * @param data The data to be hashed.
   * @return A hexadecimal string representing the hash of the data.
   * @throw std::runtime_error If the hashing operation fails.
   */
  std::string hashWithSodium(const std::string &data) {
    size_t HASH_SIZE = crypto_generichash_BYTES;
    unsigned char hash[HASH_SIZE];
    // hashing unkeyed data
    if (crypto_generichash(
            hash, HASH_SIZE,
            reinterpret_cast<const unsigned char *>(data.c_str()), data.size(),
            nullptr, 0) != 0) {
      throw std::runtime_error("Failed to hash data");
    }

    // convert binary to hex
    std::ostringstream oss;
    for (size_t i = 0; i < HASH_SIZE; ++i) {
      oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
  }
  /**
   * @brief Returns the hash of the block's data.
   *
   * This method computes the hash of the block's data using the hashWithSodium
   * method and returns it as a string.
   *
   * @return A string representing the hash of the block's data.
   */
  std::string returnBlockHash() { return hashWithSodium(data); }
};
} // namespace IronBlock

#endif // BLOCK_H
