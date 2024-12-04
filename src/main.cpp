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

int main() {
   if (sodium_init() < 0) {
      printf("Failed to initialize libsodium.\n");
   }


   return 0;
}