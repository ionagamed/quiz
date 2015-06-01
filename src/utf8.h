#pragma once

#include <SFML/System.hpp>
#include <string>

// Just a header for convenient std::string (utf8) to sf::String (utf32) in-place conversion

namespace sf {

sf::String toUtf32(std::string str);

}
