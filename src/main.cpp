#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <sodium.h>
#include "utility.h"
#include "block.h"
#include "blockOperation.h"
#include "blockchain.h"

int main() {
    // Initialize Sodium
    if (sodium_init() < 0) {
        std::cerr << "Failed to initialize libsodium." << std::endl;
        return 1;
    }

    IronBlock::Blockchain blockchain;

    int num_coins=20;
    IronBlock::UserBalanceMap initial_state = {{"Alice", num_coins}, {"Bob", num_coins}};
    std::string data = IronBlock::Utility::serialize(initial_state);
    blockchain.addBlock(data);

    // Generating multiple transactions
    int num_transactions = 30;
    std::vector<IronBlock::UserBalanceMap> transactions_buffer;
    IronBlock::UserBalanceMap state=initial_state;
    for (size_t i = 0; i < num_transactions-1; i++) {
        transactions_buffer.push_back(IronBlock::BlockOperation::makeTransaction());
        state = IronBlock::BlockOperation::updateState(state, transactions_buffer[i]);
        if (IronBlock::BlockOperation::isValidTransaction(transactions_buffer[i], state )) {
            std::string data = IronBlock::Utility::serialize(transactions_buffer[i]);
            blockchain.addBlock(data);
        }
        else {std::cout<<"Transaction update failed"<<std::endl;}
    }

    blockchain.displayBlockChain();


    return 0;
}
