#include "utf8.h"

namespace sf {
sf::String toUtf32(std::string str) { 
	std::basic_string<sf::Uint32> tmp;
	sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(tmp));
	return sf::String(tmp);
}
}
