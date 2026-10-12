#include "http/Uri.hpp"
#include <sstream>
#include <vector>

namespace http {

Uri::Uri()
	: raw("/"),
	  path("/"),
	  query(""),
	  fragment("") {}

Uri::Uri(const std::string &rawUri)
	: raw(rawUri),
	  path("/"),
	  query(""),
	  fragment("") {
	parse();
}

Uri::Uri(const Uri &other)
	: raw(other.raw),
	  path(other.path),
	  query(other.query),
	  fragment(other.fragment) {}

Uri::~Uri() {}

Uri &Uri::operator=(const Uri &other) {
	if (this != &other) {
		raw      = other.raw;
		path     = other.path;
		query    = other.query;
		fragment = other.fragment;
	}
	return *this;
}

const std::string &Uri::getRaw() const {
	return raw;
}

const std::string &Uri::getPath() const {
	return path;
}

const std::string &Uri::getQuery() const {
	return query;
}

const std::string &Uri::getFragment() const {
	return fragment;
}

void Uri::parse() {
	if (raw.empty()) {
		path = "/";
		return;
	}

	std::string uri = raw;

	// Extract fragment (#...)
	size_t hashPos = uri.find('#');
	if (hashPos != std::string::npos) {
		fragment = uri.substr(hashPos + 1);
		uri      = uri.substr(0, hashPos);
	}

	// Extract query string (?...)
	size_t questionPos = uri.find('?');
	if (questionPos != std::string::npos) {
		query = uri.substr(questionPos + 1);
		uri   = uri.substr(0, questionPos);
	}

	// Decode and sanitize path
	path = sanitize(decode(uri));
}

static int hexValue(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return -1;
}

std::string Uri::decode(const std::string &str) {
	std::string result;
	result.reserve(str.size());

	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '%' && i + 2 < str.size()) {
			int h1 = hexValue(str[i + 1]);
			int h2 = hexValue(str[i + 2]);
			if (h1 != -1 && h2 != -1) {
				result += static_cast<char>((h1 << 4) | h2);
				i += 2;
				continue;
			}
		}
		result += str[i];
	}
	return result;
}

std::string Uri::sanitize(const std::string &path) {
	if (path.empty() || path[0] != '/') {
		return "/";
	}

	std::vector<std::string> segments;
	std::istringstream       ss(path);
	std::string              part;

	while (std::getline(ss, part, '/')) {
		if (part.empty() || part == ".") {
			continue;
		}
		if (part == "..") {
			if (!segments.empty()) {
				segments.pop_back();
			}
		} else {
			segments.push_back(part);
		}
	}

	std::string sanitized = "";
	for (size_t i = 0; i < segments.size(); ++i) {
		sanitized += "/" + segments[i];
	}

	if (sanitized.empty()) {
		sanitized = "/";
	}

	// Preserve trailing slash if original path ended with one
	if (path.size() > 1 && path[path.size() - 1] == '/' &&
		sanitized[sanitized.size() - 1] != '/') {
		sanitized += "/";
	}

	return sanitized;
}

} // namespace http
