#ifndef MIME_TYPES_HPP
#define MIME_TYPES_HPP

#include <map>
#include <string>

namespace http {

class MimeTypes {
  public:
	static std::string getType(const std::string &path);

  private:
	MimeTypes();
	static void								  initMap();
	static std::map<std::string, std::string> types;
	static bool								  initialized;
};

} // namespace http

#endif
