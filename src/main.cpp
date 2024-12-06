/**
 * @file main.cpp
 * @brief Entry point for the IronBlock blockchain program.
 *
 * This program initializes the Sodium library, creates a simple blockchain,
 * and generates multiple transactions to update the blockchain state.
 * The blockchain operations are performed using the IronBlock namespace and
 * related utility functions.
 * @author vineet
 * @date 12/6/24
 */

#include "block.h"
#include "blockOperation.h"
#include "blockchain.h"
#include "utility.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sodium.h>
#include <vector>
/**
 * @brief Main function that initializes the blockchain and processes
 * transactions.
 *
 * This function initializes the Sodium cryptographic library, sets up an
 * initial state with two users (Alice and Bob), and creates a blockchain. It
 * then generates multiple transactions, validates them, and adds them to the
 * blockchain if valid.
 *
 * @return int Returns 0 on successful execution, 1 if Sodium initialization
 * fails.
 */
int main() {
  // Initialize Sodium
  if (sodium_init() < 0) {
    std::cerr << "Failed to initialize libsodium." << std::endl;
    return 1;
  }

  IronBlock::Blockchain blockchain;
  // Initial state with coins for Alice and Bob
  int num_coins = 20;
  IronBlock::UserBalanceMap initial_state = {{"Alice", num_coins},
                                             {"Bob", num_coins}};
  std::string data = IronBlock::Utility::serialize(initial_state);
  blockchain.addBlock(data);

  // Generating multiple transactions
  int num_transactions = 30;
  std::vector<IronBlock::UserBalanceMap> transactions_buffer;
  IronBlock::UserBalanceMap state = initial_state;
  for (size_t i = 0; i < num_transactions - 1; i++) {
    transactions_buffer.push_back(IronBlock::BlockOperation::makeTransaction());
    state =
        IronBlock::BlockOperation::updateState(state, transactions_buffer[i]);
    if (IronBlock::BlockOperation::isValidTransaction(transactions_buffer[i],
                                                      state)) {
      std::string data = IronBlock::Utility::serialize(transactions_buffer[i]);
      blockchain.addBlock(data);
    } else {
      std::cout << "Transaction update failed" << std::endl;
    }
  }
  // Display the blockchain
  blockchain.displayBlockChain();

  return 0;
}
