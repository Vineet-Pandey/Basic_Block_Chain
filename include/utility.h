/// @file utility.h
/// @brief Utility functions for serialization.
/// @author Vineet
/// @date 12/6/24
#ifndef UTILITY_H
#define UTILITY_H
#include <string>

namespace IronBlock {

namespace Utility {
/**
 * @brief Serializes data of type T to a string.
 *
 * @tparam T The type of data to serialize.
 * @param data The data to serialize.
 * @return A string representation of the data.
 */
template <typename T> std::string serialize(const T &data);

/**
 * @brief Specialization for serializing integers to a string.
 *
 * @param data The integer to serialize.
 * @return A string representation of the integer.
 */
template <> std::string serialize(const int &data) {
  return std::to_string(data);
}
/**
 * @brief Specialization for serializing doubles to a string.
 *
 * @param data The double to serialize.
 * @return A string representation of the double.
 */
template <> std::string serialize(const double &data) {
  return std::to_string(data);
}

/**
 * @brief Specialization for serializing strings.
 *
 * @param data The string to serialize.
 * @return The original string.
 */
template <> std::string serialize(const std::string &data) { return data; }

/**
 * @brief Serializes a vector of data to a string.
 *
 * @tparam T The type of elements in the vector.
 * @param data The vector to serialize.
 * @return A string representation of the vector.
 */
template <typename T> std::string serialize(const std::vector<T> &data) {
  std::stringstream ss;
  for (size_t i = 0; i < data.size(); i++) {
    ss << serialize(data[i]);
  }
  return ss.str();
}

/**
 * @brief Serializes a map of data to a string.
 *
 * @tparam T The type of keys in the map.
 * @tparam K The type of values in the map.
 * @param data The map to serialize.
 * @return A string representation of the map.
 */
template <typename T, typename K>
std::string serialize(const std::map<T, K> &data) {
  std::stringstream ss;

  for (auto it = data.begin(); it != data.end(); it++) {
    ss << serialize(it->first);
    ss << ":";
    ss << serialize(it->second);
    ss << " ";
  }
  return ss.str();
}

}; // namespace Utility

} // namespace IronBlock

#endif // UTILITY_H
