#include "http/HttpResponse.hpp"
#include <sstream>

namespace http {

Response::Response() :
		status(STATUS_OK),
		version("HTTP/1.1"),
		body("") {}

Response::Response(Status status) :
		status(status),
		version("HTTP/1.1"),
		body("") {}

Response::Response(const Response &other) :
		status(other.status),
		version(other.version),
		headers(other.headers),
		body(other.body) {}

Response::~Response() {}

Response &Response::operator=(const Response &other) {
	if (this != &other) {
		status	= other.status;
		version = other.version;
		headers = other.headers;
		body	= other.body;
	}
	return *this;
}

Status Response::getStatus() const {
	return status;
}

const std::string &Response::getVersion() const {
	return version;
}

const std::map<std::string, std::string> &Response::getHeaders() const {
	return headers;
}

const std::string &Response::getBody() const {
	return body;
}

void Response::setStatus(Status newStatus) {
	status = newStatus;
}

void Response::setVersion(const std::string &newVersion) {
	version = newVersion;
}

void Response::setHeader(const std::string &name, const std::string &value) {
	headers[name] = value;
}

void Response::setBody(const std::string &newBody,
					   const std::string &contentType) {
	body = newBody;
	std::ostringstream ss;
	ss << body.size();
	headers["Content-Length"] = ss.str();
	if (!contentType.empty()) {
		headers["Content-Type"] = contentType;
	}
}

std::string Response::serialize() const {
	std::ostringstream ss;
	// Status line
	ss << version << " " << static_cast<int>(status) << " "
	   << getStatusReason(status) << "\r\n";

	// Headers
	for (std::map<std::string, std::string>::const_iterator it =
			 headers.begin();
		 it != headers.end(); ++it) {
		ss << it->first << ": " << it->second << "\r\n";
	}
	ss << "\r\n";

	// Body
	ss << body;
	return ss.str();
}

Response Response::makeError(Status				errorStatus,
							 const std::string &customBody) {
	Response res(errorStatus);
	if (!customBody.empty()) {
		res.setBody(customBody, "text/html");
	} else {
		std::ostringstream html;
		int				   code	  = static_cast<int>(errorStatus);
		std::string		   reason = getStatusReason(errorStatus);
		html << "<!DOCTYPE html>\n"
			 << "<html>\n<head><title>" << code << " " << reason
			 << "</title></head>\n"
			 << "<body style=\"text-align: center; font-family: sans-serif; "
				"padding-top: 50px;\">\n"
			 << "<h1>" << code << " " << reason << "</h1>\n"
			 << "<hr><p>webserv/1.0</p>\n"
			 << "</body>\n</html>\n";
		res.setBody(html.str(), "text/html");
	}
	res.setHeader("Connection", "close");
	return res;
}

Response Response::makeRedirect(Status			   redirectStatus,
								const std::string &location) {
	Response res(redirectStatus);
	res.setHeader("Location", location);
	res.setBody("", "text/html");
	return res;
}

} // namespace http
