#include "http/MimeTypes.hpp"
#include "utils/StringUtils.hpp"

namespace http {

std::map<std::string, std::string> MimeTypes::types;
bool                               MimeTypes::initialized = false;

void MimeTypes::initMap() {
	if (initialized) return;

	// Text
	types[".html"] = "text/html";
	types[".htm"]  = "text/html";
	types[".css"]  = "text/css";
	types[".txt"]  = "text/plain";
	types[".csv"]  = "text/csv";

	// Application
	types[".js"]   = "application/javascript";
	types[".json"] = "application/json";
	types[".pdf"]  = "application/pdf";
	types[".zip"]  = "application/zip";
	types[".tar"]  = "application/x-tar";
	types[".gz"]   = "application/gzip";

	// Images
	types[".png"]  = "image/png";
	types[".jpg"]  = "image/jpeg";
	types[".jpeg"] = "image/jpeg";
	types[".gif"]  = "image/gif";
	types[".svg"]  = "image/svg+xml";
	types[".ico"]  = "image/x-icon";
	types[".webp"] = "image/webp";

	// Audio / Video
	types[".mp3"]  = "audio/mpeg";
	types[".mp4"]  = "video/mp4";
	types[".webm"] = "video/webm";

	initialized = true;
}

std::string MimeTypes::getType(const std::string &path) {
	initMap();

	size_t dotPos = path.find_last_of('.');
	if (dotPos == std::string::npos) {
		return "application/octet-stream";
	}

	std::string ext = utils::toLower(path.substr(dotPos));

	std::map<std::string, std::string>::const_iterator it = types.find(ext);
	if (it != types.end()) {
		return it->second;
	}

	return "application/octet-stream";
}

} // namespace http
