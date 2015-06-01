#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Config.h"

class Main {
public:
	static Main* getInstance();

	sf::Font font;
	sf::RenderWindow* window;

	// Just added after input with a space
	std::string msgFromChecker;
	sf::Text msgText;
	// For smooth bg color switch
	double bgr, bgg, bgb;

	Config conf;
	int currentPointer;

	std::string currentInputLocale;
	bool altPressed, shiftPressed;

	bool debug;

	void init(std::string filename);

	void runLoop();

	void draw();
	void loop(sf::Time dt);

	void exit();

	void handle(sf::Event ev);
};
