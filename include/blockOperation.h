/*
 * @file blockOperation.h
 * @brief Contains the implementation of block operations for user transactions
 * and state updates.
 * @author vineet
 * @date 12/6/24
 */

#ifndef BLOCKOPERATION_H
#define BLOCKOPERATION_H
#include "utility.h"
#include <map>

namespace IronBlock {
/*
 * @typedef UserBalanceMap
 * @brief A map to store user balances, where the key is the user's name and the
 * value is their balance.
 */
typedef std::map<std::string, int> UserBalanceMap;

namespace BlockOperation {
/*
 * @brief Creates a transaction between two users, Alice and Bob.
 * @param maxValue The maximum value of the transaction. Default is 3.
 * @return A UserBalanceMap representing the transaction, with Alice and Bob's
 * updated balances.
 */
UserBalanceMap makeTransaction(int maxValue = 3) {
  int max = 1;
  int min = 0;
  int sign = (min + randombytes_uniform(max - min + 1)) * 2 - 1;
  int amount = (1 + randombytes_uniform(maxValue));
  int alicePays = sign * amount;
  int bobPays = -1 * alicePays;

  return {{"Alice", alicePays}, {"Bob", bobPays}};
}
/*
 * @brief Updates the state of user balances based on a given transaction.
 * @param state The current state of user balances.
 * @param txn The transaction to be applied to the state.
 * @return A UserBalanceMap representing the updated state.
 */
UserBalanceMap updateState(UserBalanceMap state, UserBalanceMap txn) {
  for (auto it = txn.begin(); it != txn.end(); it++) {
    state[it->first] += it->second;
  }

  return state;
}
/*
 * @brief Validates if a given transaction is valid based on the current state.
 * @param transaction The transaction to be validated.
 * @param state The current state of user balances.
 * @return True if the transaction is valid, otherwise false.
 */
bool isValidTransaction(const UserBalanceMap &transaction,
                        UserBalanceMap state) {
  // since we are conserving the money here i.e., money is neither created nor
  // destroyed, if the sum is not 0 then its an invalid transaction
  int sum = 0;
  for (auto it = transaction.begin(); it != transaction.end(); it++) {
    sum += it->second;
  }
  if (sum != 0) {
    return false;
  }
  int account_balance;
  for (auto &it : transaction) {
    if (state.find(it.first) != state.end()) {
      account_balance = state.at(it.first);
    } else {
      account_balance = 0;
    }
    if (account_balance + it.second < 0) {
      return false;
    }
  }

  return true;
}
} // namespace BlockOperation
} // namespace IronBlock

#endif // BLOCKOPERATION_H
