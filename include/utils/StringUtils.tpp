#ifndef STRING_UTILS_TPP
#define STRING_UTILS_TPP

#include <new>
#include <sstream>
#include <stdexcept>
#include <string>

namespace utils {

template <typename T> bool tryToString(const T &value, std::string &out) {
	try {
		std::ostringstream ss;
		if (!(ss << value)) {
			return false;
		}
		std::string temp = ss.str();
		out.swap(temp);
		return true;
	} catch (const std::bad_alloc &) {
		return false;
	} catch (...) {
		return false;
	}
}

template <typename T> std::string toString(const T &value) {
	std::string out;
	if (!tryToString(value, out)) {
		return "";
	}
	return out;
}

template <typename Target>
bool tryFromString(const std::string &str, Target &result) {
	try {
		std::istringstream ss(str);
		char			   leftover;
		if (!(ss >> result) || (ss >> leftover)) {
			return false;
		}
		return true;
	} catch (const std::bad_alloc &) {
		return false;
	} catch (...) {
		return false;
	}
}

template <typename Target> Target fromString(const std::string &str) {
	Target result;
	if (!tryFromString(str, result)) {
		throw std::runtime_error("fromString failed: invalid conversion for '" +
								 str + "'");
	}
	return result;
}

} // namespace utils

#endif
