//
// Created by vineet on 12/6/24.
//

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"
#include <vector>
namespace IronBlock {
class Blockchain {
private:
  std::vector<IronBlock::Block> chain;

public:
  Blockchain() {
    std::string data = "Iron Block Genesis";
    std::string previousBlockHash = "0";
    IronBlock::Block genesisBlock =
        IronBlock::Block(0, data, previousBlockHash);
    chain.push_back(genesisBlock);
  }

  void addBlock(std::string &data) {
    int index = chain.size();
    std::string previous_block_hash = chain.back().returnBlockHash();
    IronBlock::Block *newBlock =
        new IronBlock::Block(index, data, previous_block_hash);
    newBlock->block_hash = newBlock->returnBlockHash();
    chain.push_back(*newBlock);
  }

  void displayBlockChain() {
    for (const auto &block : chain) {
      std::cout << "Block Index: " << block.index << std::endl;
      std::cout << "Data: " << block.data << std::endl;
      std::cout << "Previous Block Hash: " << block.previous_block_hash << std::endl;
      std::cout << "Timestamp: " << block.timestamp << std::endl;
      std::cout << "Block Hash: " << block.block_hash << std::endl;
      std::cout << "------------------------" << std::endl;
    }
  }
};
} // namespace IronBlock

#endif // BLOCKCHAIN_H
