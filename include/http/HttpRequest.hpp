#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "http/HttpCommon.hpp"
#include <map>
#include <string>

namespace http {

class Request {
  public:
	Request();
	Request(const Request &other);
	~Request();

	Request &operator=(const Request &other);

	// Getters
	Method                                    getMethod() const;
	const std::string                        &getPath() const;
	const std::string                        &getQueryString() const;
	const std::string                        &getVersion() const;
	const std::map<std::string, std::string> &getHeaders() const;
	const std::string                        &getBody() const;
	bool        hasHeader(const std::string &name) const;
	std::string getHeader(const std::string &name) const;
	bool        isComplete() const;

	// Setters / Modifiers
	void setMethod(Method method);
	void setPath(const std::string &path);
	void setQueryString(const std::string &queryString);
	void setVersion(const std::string &version);
	void setHeader(const std::string &name, const std::string &value);
	void setBody(const std::string &body);
	void appendBody(const std::string &chunk);
	void setComplete(bool complete);
	void clear();

  private:
	Method                             method;
	std::string                        path;
	std::string                        queryString;
	std::string                        version;
	std::map<std::string, std::string> headers;
	std::string                        body;
	bool                               complete;
};

} // namespace http

#endif
