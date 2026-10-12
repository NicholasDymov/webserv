#include "http/HttpRequest.hpp"
#include "utils/StringUtils.hpp"

namespace http {

Request::Request() :
		method(METHOD_UNKNOWN),
		path(""),
		queryString(""),
		version("HTTP/1.1"),
		body(""),
		complete(false) {}

Request::Request(const Request &other) :
		method(other.method),
		path(other.path),
		queryString(other.queryString),
		version(other.version),
		headers(other.headers),
		body(other.body),
		complete(other.complete) {}

Request::~Request() {}

Request &Request::operator=(const Request &other) {
	if (this != &other) {
		method      = other.method;
		path        = other.path;
		queryString = other.queryString;
		version     = other.version;
		headers     = other.headers;
		body        = other.body;
		complete    = other.complete;
	}
	return *this;
}

Method Request::getMethod() const {
	return method;
}

const std::string &Request::getPath() const {
	return path;
}

const std::string &Request::getQueryString() const {
	return queryString;
}

const std::string &Request::getVersion() const {
	return version;
}

const std::map<std::string, std::string> &Request::getHeaders() const {
	return headers;
}

const std::string &Request::getBody() const {
	return body;
}

bool Request::hasHeader(const std::string &name) const {
	return headers.find(utils::toLower(name)) != headers.end();
}

std::string Request::getHeader(const std::string &name) const {
	std::map<std::string, std::string>::const_iterator it =
		headers.find(utils::toLower(name));
	if (it != headers.end()) {
		return it->second;
	}
	return "";
}

bool Request::isComplete() const {
	return complete;
}

void Request::setMethod(Method method) {
	this->method = method;
}

void Request::setPath(const std::string &path) {
	this->path = path;
}

void Request::setQueryString(const std::string &queryString) {
	this->queryString = queryString;
}

void Request::setVersion(const std::string &version) {
	this->version = version;
}

void Request::setHeader(const std::string &name, const std::string &value) {
	headers[utils::toLower(name)] = value;
}

void Request::setBody(const std::string &body) {
	this->body = body;
}

void Request::appendBody(const std::string &chunk) {
	body.append(chunk);
}

void Request::setComplete(bool complete) {
	this->complete = complete;
}

void Request::clear() {
	method = METHOD_UNKNOWN;
	path.clear();
	queryString.clear();
	version = "HTTP/1.1";
	headers.clear();
	body.clear();
	complete = false;
}

} // namespace http
