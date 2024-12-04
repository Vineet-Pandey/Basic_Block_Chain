//
// Created by vineet on 12/4/24.
//

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

int main() {
   if (sodium_init() < 0) {
      printf("Failed to initialize libsodium.\n");
   }


   return 0;
}