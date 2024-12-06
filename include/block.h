//
// Created by vineet on 12/6/24.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "utility.h"
#include <ctime>
#include <sodium.h>
#include <sstream>
namespace IronBlock {
class Block {
public:
  int index;
  std::string data;
  std::string previous_block_hash;
  std::time_t timestamp;
  std::string block_hash;

  Block(int index, std::string &data, std::string &previous_block_hash)
      : index(index), data(data), previous_block_hash(previous_block_hash) {
    timestamp = std::time(nullptr);
  }
  
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




};
} // namespace IronBlock

#endif // BLOCK_H
