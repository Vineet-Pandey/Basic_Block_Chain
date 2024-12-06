/**
 * @file blockchain.h
 * @brief Header file for the Blockchain class in the IronBlock namespace.
 *
 * This file contains the definition of the Blockchain class, which is used to
 * manage a simple chain of blocks.
 *
 * @author vineet
 * @date 12/6/24
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"
#include <vector>
namespace IronBlock {
/**
 * @class Blockchain
 * @brief A class representing a blockchain.
 *
 * The Blockchain class is responsible for maintaining a chain of blocks. It
 * provides methods for adding new blocks and displaying the entire chain.
 */
class Blockchain {

private:
  /**
   * @brief A vector storing the chain of blocks.
   */
  std::vector<IronBlock::Block> chain;

public:
  /**
   * @brief Constructor for Blockchain.
   *
   * Initializes the blockchain with a genesis block.
   */
  Blockchain() {
    std::string data = "Iron Block Genesis";
    std::string previousBlockHash = "0";
    IronBlock::Block genesisBlock =
        IronBlock::Block(0, data, previousBlockHash);
    chain.push_back(genesisBlock);
  }
  /**
   * @brief Adds a new block to the blockchain.
   *
   * @param data The data to be stored in the new block.
   */

  void addBlock(std::string &data) {
    int index = chain.size();
    std::string previous_block_hash = chain.back().returnBlockHash();
    IronBlock::Block *newBlock =
        new IronBlock::Block(index, data, previous_block_hash);
    newBlock->block_hash = newBlock->returnBlockHash();
    chain.push_back(*newBlock);
  }
  /**
   * @brief Displays the entire blockchain.
   *
   * Prints the details of each block in the blockchain, including index, data,
   * previous block hash, timestamp, and block hash.
   */
  void displayBlockChain() {
    for (const auto &block : chain) {
      std::cout << "Block Index: " << block.index << std::endl;
      std::cout << "Data: " << block.data << std::endl;
      std::cout << "Previous Block Hash: " << block.previous_block_hash
                << std::endl;
      std::cout << "Timestamp: " << block.timestamp << std::endl;
      std::cout << "Block Hash: " << block.block_hash << std::endl;
      std::cout << "------------------------" << std::endl;
    }
  }
};
} // namespace IronBlock

#endif // BLOCKCHAIN_H
