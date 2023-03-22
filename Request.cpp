#include "Request.hpp"
#include "ConfigFile.hpp"

#define NEWLINE "\n"

Request::Request() {}
Request::~Request() {}

std::string Request::getHTTPMethod() const {
    return HTTPMethod;
}

std::string Request::getPath() const {
    return Path;
}
std::string Request::getBody() const {
    return Body;
}

std::string Request::getHTTPVersion() const {
    return HTTPVersion;
}
std::map<std::string, std::string> Request::getRequestHeader() const {
    return RequestMap;
}

void Request::RequestParse(std::string s) {
    std::string Key, Value, Line;
    // -------------Request Line------------------
    Line = s.substr(0, s.find(NEWLINE));
    s = s.substr(s.find(NEWLINE) + 1);
    std::stringstream ss(Line);
    ss >> HTTPMethod >> Path >> HTTPVersion;
    // -------------HTTP Headers------------------
    Line = s.substr(0, s.find(NEWLINE));
    while (Line.length() > 1) {
        std::stringstream ss(Line);
        ss >> Key >> Value;
        RequestMap.insert(std::make_pair(Key.substr(0, Key.length() - 1), Value));
        s = s.substr(s.find(NEWLINE) + 1);
        Line = s.substr(0, s.find(NEWLINE));
    }
    s = s.substr(s.find(NEWLINE) + 1);
    if (s.length()) Body = s;
    if (HTTPMethod == "GET" && Path.find("?") != std::string::npos) {
        Body = Path.substr(Path.find("?") + 1);
        Path = Path.substr(0, Path.find("?"));
    }
}