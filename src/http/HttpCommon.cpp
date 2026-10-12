#include "http/HttpCommon.hpp"

namespace http {

std::string methodToString(Method method) {
	switch (method) {
		case METHOD_GET:	return "GET";
		case METHOD_POST:	return "POST";
		case METHOD_DELETE: return "DELETE";
		default:			return "UNKNOWN";
	}
}

Method stringToMethod(const std::string &str) {
	if (str == "GET") return METHOD_GET;
	if (str == "POST") return METHOD_POST;
	if (str == "DELETE") return METHOD_DELETE;
	return METHOD_UNKNOWN;
}

std::string getStatusReason(Status status) {
	switch (status) {
		case STATUS_OK:					   return "OK";
		case STATUS_CREATED:			   return "Created";
		case STATUS_NO_CONTENT:			   return "No Content";
		case STATUS_MOVED_PERMANENTLY:	   return "Moved Permanently";
		case STATUS_FOUND:				   return "Found";
		case STATUS_BAD_REQUEST:		   return "Bad Request";
		case STATUS_FORBIDDEN:			   return "Forbidden";
		case STATUS_NOT_FOUND:			   return "Not Found";
		case STATUS_METHOD_NOT_ALLOWED:	   return "Method Not Allowed";
		case STATUS_PAYLOAD_TOO_LARGE:	   return "Payload Too Large";
		case STATUS_INTERNAL_SERVER_ERROR: return "Internal Server Error";
		case STATUS_NOT_IMPLEMENTED:	   return "Not Implemented";
		case STATUS_BAD_GATEWAY:		   return "Bad Gateway";
		case STATUS_GATEWAY_TIMEOUT:	   return "Gateway Timeout";
		default:						   return "Unknown Status";
	}
}

std::ostream &operator<<(std::ostream &os, Method method) {
	return os << methodToString(method);
}

std::ostream &operator<<(std::ostream &os, Status status) {
	return os << static_cast<int>(status) << " " << getStatusReason(status);
}

} // namespace http
