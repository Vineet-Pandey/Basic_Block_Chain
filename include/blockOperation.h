//
// Created by vineet on 12/6/24.
//

#ifndef BLOCKOPERATION_H
#define BLOCKOPERATION_H
#include "utility.h"
#include <map>

namespace IronBlock {
typedef std::map<std::string, int> UserBalanceMap;

namespace BlockOperation {
UserBalanceMap makeTransaction(int maxValue = 3) {
  int max = 1;
  int min = 0;
  int sign = (min + randombytes_uniform(max - min + 1)) * 2 - 1;
  int amount = (1 + randombytes_uniform(maxValue));
  int alicePays = sign * amount;
  int bobPays = -1 * alicePays;

  return {{"Alice", alicePays}, {"Bob", bobPays}};
}

UserBalanceMap updateState(UserBalanceMap state, UserBalanceMap txn) {
  for (auto it = txn.begin(); it != txn.end(); it++) {
    state[it->first] += it->second;
  }

  return state;
}

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
