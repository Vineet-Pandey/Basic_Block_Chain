#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <sodium.h>
#include "utility.h"
#include "block.h"
#include "blockOperation.h"


using namespace IronBlock::Utility;       // For using serialize function
using namespace IronBlock::BlockOperation; // For using makeTransaction and other block operations

int main() {
    // Initialize Sodium
    if (sodium_init() < 0) {
        std::cerr << "Failed to initialize libsodium." << std::endl;
        return 1;
    }

    // Example map data to serialize
    IronBlock::UserBalanceMap data = {{"age", 25}, {"height", 175}};
    std::string s1 = serialize(data);
    std::cout << "Serialized Data: " << s1 << std::endl;

    // Creating a Block instance and hashing data using the hashWithSodium function
    std::string prev_hash_init ="0";
    IronBlock::Block block(0, s1, prev_hash_init);
    std::string block_hash = block.hashWithSodium(s1);  // Make hashWithSodium public to use it here
    std::cout << "Block Hash: " << block_hash << std::endl;

    // Generating multiple transactions
    int num_transactions = 30;
    std::vector<IronBlock::UserBalanceMap> transactions_buffer;
    for (size_t i = 0; i < num_transactions; i++) {
        transactions_buffer.push_back(makeTransaction());
    }

    // Example initial state and transaction validation
    IronBlock::UserBalanceMap initial_state = {{"Alice", 50}, {"Bob", 50}};
    bool valid = isValidTransaction({{"Alice", -3}, {"Bob", 3}}, initial_state);
    std::cout << "Is it a valid transaction: " << (valid ? "Yes" : "No") << std::endl;

    return 0;
}
