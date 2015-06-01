#pragma once

#include <string>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Question {
public:
	std::string question;
	std::string answer;
	std::string input;

	std::function <bool(std::string, std::string)> check;

	sf::Text text;
	bool showTheThing;

	Question();
	Question(std::string que, std::string ans, std::function <bool(std::string, std::string)> check);

	sf::Time dt;

	void draw(int pos);
	void loop(sf::Time dt);
};
