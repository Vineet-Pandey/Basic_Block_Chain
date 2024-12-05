//
// Created by vineet on 12/4/24.
//

#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include<sodium.h>

template<typename T>
std::string serialize(const T &data);

// for integers
template<>
std::string serialize(const int &data) {
   return std::to_string(data);
}
// for doubles
template<>
std::string serialize(const double &data) {
   return std::to_string(data);
}

// for strings
template<>
std::string serialize(const std::string &data) {
   return data;
}

//for vectors
template<typename T>
std::string serialize(const std::vector<T> &data) {
   std::stringstream ss;
   for (size_t i=0; i<data.size(); i++) {
      ss<<serialize(data[i]);
   }
   return ss.str();
}

//for maps
template<typename T, typename K>
std::string serialize(const std::map<T,K> &data) {
   std::stringstream ss;

   for (auto it = data.begin(); it != data.end(); it++) {
      ss<<serialize(it->first);
      ss<<":";
      ss<<serialize(it->second);
   }
   return ss.str();
}


std::string hashWithSodium(const std::string &data) {

   size_t HASH_SIZE = crypto_generichash_BYTES;
   unsigned char hash[HASH_SIZE];

   //hashing unkeyed data
   if (crypto_generichash(hash,
      HASH_SIZE,
      reinterpret_cast<const unsigned char *>(data.c_str()), data.size(),nullptr,0)!=0) {
      throw std::runtime_error("Failed to hash data");
   }

   //convert binary to hex
   std::ostringstream oss;
   for (size_t i = 0; i < HASH_SIZE; ++i) {
      oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
   }
   return oss.str();



}

std::map<std::string, int> makeTransaction(int maxValue=3) {
   int max=1;
   int min =0;
   int sign = (min+randombytes_uniform(max-min+1))*2-1;
   int amount = (1+randombytes_uniform(maxValue));
   int alicePays = sign*amount;
   int bobPays = -1*alicePays;

   return {{"Alice",alicePays},{"Bob",bobPays}};

}

std::map<std::string,int> updateState(std::map<std::string,int> state,std::map<std::string,int> txn) {
   for (auto it = txn.begin(); it != txn.end(); it++) {
      state[it->first] += it->second;
   }

   return state;
}


bool isValidTransaction(const std::map<std::string,int> &transaction, std::map<std::string,int> state) {
   //since we are conserving the money here i.e., money is neither created nor destroyed, if the sum is not 0 then its an invalid transaction
   int sum=0;
   for (auto it = transaction.begin(); it != transaction.end(); it++) {
      sum+=it->second;
   }
   if (sum!=0) {
      return false;
   }
   int account_balance;
   for (auto &it:transaction) {
      if (state.find(it.first)!= state.end()) {
         account_balance = state.at(it.first);
      } else {
         account_balance = 0;
      }
      if (account_balance+it.second <0) {
         return false;
      }
   }

   return true;

}

int main() {
   if (sodium_init() < 0) {
      printf("Failed to initialize libsodium.\n");
   }
   std::map<std::string, int> data = {{"age", 25}, {"height", 175}};
   std::string s1= serialize(data);
   std::cout << "Hash: " << hashWithSodium(s1) << std::endl;
   int num_transactions=30;
   std::vector<std::map<std::string,int>> transactions_buffer;
 for (size_t i=0; i<num_transactions; i++) {
   transactions_buffer.push_back(makeTransaction());
 }

   std::map<std::string,int> state = {{"Alice",5}, {"Bob",5}};
   std::cout<<"Is it a valid transaction: "<<isValidTransaction({{"Alice",-3}, {"Bob",3}}, state)<<std::endl;



   return 0;
}