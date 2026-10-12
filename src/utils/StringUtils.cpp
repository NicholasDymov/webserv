#include "utils/StringUtils.hpp"
#include <algorithm>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <new>

namespace utils {

static char toLowerChar(char c) {
	return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

static char toUpperChar(char c) {
	return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
}

std::string toLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), toLowerChar);
	return str;
}

std::string toUpper(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), toUpperChar);
	return str;
}

std::string trim(const std::string &str) {
	size_t start = 0;
	while (start < str.size() &&
		   std::isspace(static_cast<unsigned char>(str[start]))) {
		++start;
	}

	if (start == str.size()) {
		return "";
	}

	size_t end = str.size() - 1;
	while (end > start && std::isspace(static_cast<unsigned char>(str[end]))) {
		--end;
	}

	return str.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = str.find(delimiter);

	while (end != std::string::npos) {
		if (end > start) {
			tokens.push_back(str.substr(start, end - start));
		}
		start = end + 1;
		end = str.find(delimiter, start);
	}

	if (start < str.size()) {
		tokens.push_back(str.substr(start));
	}
	return tokens;
}

bool tryToString(int value, std::string &out) {
	try {
		char buf[24];
		int	 len = std::sprintf(buf, "%d", value);
		if (len < 0) return false;
		out.assign(buf, static_cast<size_t>(len));
		return true;
	} catch (const std::bad_alloc &) {
		return false;
	} catch (...) {
		return false;
	}
}

bool tryToString(size_t value, std::string &out) {
	try {
		char buf[24];
		int	 len = std::sprintf(buf, "%lu", static_cast<unsigned long>(value));
		if (len < 0) return false;
		out.assign(buf, static_cast<size_t>(len));
		return true;
	} catch (const std::bad_alloc &) {
		return false;
	} catch (...) {
		return false;
	}
}

bool tryFromString(const std::string &str, int &result) {
	if (str.empty()) return false;

	char *end = NULL;
	errno	  = 0;
	long val  = std::strtol(str.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX ||
		end == str.c_str()) {
		return false;
	}
	result = static_cast<int>(val);
	return true;
}

bool tryFromString(const std::string &str, size_t &result) {
	if (str.empty()) return false;

	size_t i = 0;
	while (i < str.size() && std::isspace(static_cast<unsigned char>(str[i]))) {
		++i;
	}
	if (i < str.size() && str[i] == '-') {
		return false;
	}

	char *end		  = NULL;
	errno			  = 0;
	unsigned long val = std::strtoul(str.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE || end == str.c_str()) {
		return false;
	}
	result = static_cast<size_t>(val);
	return true;
}

} // namespace utils
