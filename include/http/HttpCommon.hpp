#ifndef HTTP_COMMON_HPP
#define HTTP_COMMON_HPP

#include <ostream>
#include <string>

namespace http {

enum Method {
	METHOD_UNKNOWN = 0,
	METHOD_GET,
	METHOD_POST,
	METHOD_DELETE
};

enum Status {
	STATUS_OK					 = 200,
	STATUS_CREATED				 = 201,
	STATUS_NO_CONTENT			 = 204,
	STATUS_MOVED_PERMANENTLY	 = 301,
	STATUS_FOUND				 = 302,
	STATUS_BAD_REQUEST			 = 400,
	STATUS_FORBIDDEN			 = 403,
	STATUS_NOT_FOUND			 = 404,
	STATUS_METHOD_NOT_ALLOWED	 = 405,
	STATUS_PAYLOAD_TOO_LARGE	 = 413,
	STATUS_INTERNAL_SERVER_ERROR = 500,
	STATUS_NOT_IMPLEMENTED		 = 501,
	STATUS_BAD_GATEWAY			 = 502,
	STATUS_GATEWAY_TIMEOUT		 = 504
};

std::string methodToString(Method method);
Method		stringToMethod(const std::string &str);
std::string getStatusReason(Status status);

std::ostream &operator<<(std::ostream &os, Method method);
std::ostream &operator<<(std::ostream &os, Status status);

} // namespace http

#endif
