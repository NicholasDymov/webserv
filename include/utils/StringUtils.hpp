#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

namespace utils {

std::string				 toLower(std::string str);
std::string				 toUpper(std::string str);
std::string				 trim(const std::string &str);
std::vector<std::string> split(const std::string &str, char delimiter);

bool tryToString(int value, std::string &out);
bool tryToString(size_t value, std::string &out);

bool tryFromString(const std::string &str, int &result);
bool tryFromString(const std::string &str, size_t &result);

template <typename T> bool tryToString(const T &value, std::string &out);

template <typename T> std::string toString(const T &value);

template <typename Target>
bool tryFromString(const std::string &str, Target &result);

template <typename Target> Target fromString(const std::string &str);

} // namespace utils

#include "utils/StringUtils.tpp"

#endif
