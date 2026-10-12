#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "http/HttpCommon.hpp"
#include <map>
#include <string>

namespace http {

class Response {
  public:
	Response();
	Response(Status status);
	Response(const Response &other);
	~Response();

	Response &operator=(const Response &other);

	// Getters
	Status                                    getStatus() const;
	const std::string                        &getVersion() const;
	const std::map<std::string, std::string> &getHeaders() const;
	const std::string                        &getBody() const;

	// Setters
	void setStatus(Status status);
	void setVersion(const std::string &version);
	void setHeader(const std::string &name, const std::string &value);
	void setBody(const std::string &body, const std::string &contentType = "");

	// Serialization
	std::string serialize() const;

	// Helpers
	static Response makeError(Status             status,
	                          const std::string &customBody = "");
	static Response makeRedirect(Status status, const std::string &location);

  private:
	Status                             status;
	std::string                        version;
	std::map<std::string, std::string> headers;
	std::string                        body;
};

} // namespace http

#endif
