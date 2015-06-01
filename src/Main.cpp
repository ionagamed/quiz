#include "Main.h"

#include <iostream>
#include <cstdlib>

#include <X11/Xlib.h>

Main* Main::getInstance() {
	static Main* instance = NULL;
	if (instance) {
		return instance;
	}
	return instance = new Main();
}

void Main::init(std::string filename) {
	conf.init(filename);

	//window = new sf::RenderWindow(
			//sf::VideoMode::getDesktopMode(),
			//"quiz",
			//sf::Style::Fullscreen
			//);
	window = new sf::RenderWindow(
			sf::VideoMode(800, 640),
			"quiz"
			);
	window->setFramerateLimit(60);

	// Anyway, doesn't work with ctrl-alt-f# tty switches
	// And the app is meant to be launched before the WM
	//XGrabKeyboard(XOpenDisplay(NULL), window->getSystemHandle(), true, GrabModeAsync, GrabModeAsync, CurrentTime);

	font.loadFromFile(conf.settings.fontName);
	msgText.setFont(font);

	currentPointer = 0;
	currentInputLocale = "ru";
	altPressed = shiftPressed = false;

	bgr = bgg = bgb = 255.0;
}

void Main::draw() {
	for (size_t i = 0; i < conf.questions.size(); i++) {
		// Calculate the position relative to the currentPointer
		conf.questions[i]->draw(i - currentPointer);
	}
}

void Main::loop(sf::Time dt) {
	for (Question* i : conf.questions) {
		i->loop(dt);
	}

	if (currentPointer >= (int) conf.questions.size()) {
		exit();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
		!(shiftPressed && altPressed)) {
		if (currentInputLocale == "en_US") {
			currentInputLocale = "ru";
		} else {
			currentInputLocale = "en_US";
		}
		system(("setxkbmap " + currentInputLocale).c_str());
	}

	shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	altPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);

	if (sf::Color(bgr, bgg, bgb) != sf::Color::White) {
		bgr += (sf::Color::White.r - bgr) * conf.settings.colorStep;
		bgg += (sf::Color::White.g - bgg) * conf.settings.colorStep;
		bgb += (sf::Color::White.b - bgb) * conf.settings.colorStep;
	}
}

void Main::runLoop() {
	sf::Clock clock;
	while (window->isOpen()) {
		sf::Event ev;
		while (window->pollEvent(ev)) {
			handle(ev);
		}
		window->clear(sf::Color(bgr, bgg, bgb));
		
		loop(clock.restart());
		draw();

		window->display();
	}
}

void Main::handle(sf::Event ev) {
	std::string tmp;
	std::string& currentInput = conf.questions[currentPointer]->input;
	switch (ev.type) {
		case sf::Event::Closed:
			break;
		case sf::Event::KeyPressed:
			switch (ev.key.code) {
				case sf::Keyboard::Escape:
					if (debug) {
						this->exit();
					}
					break;
				default:
					break;
			}
			break;
		case sf::Event::TextEntered:
			switch (ev.text.unicode) {
				case '\b':
					if (!currentInput.empty()) {
						currentInput.pop_back();
						if (!currentInput.empty()) {
							if (*(currentInput.end() - 1) == '\xd0' || *(currentInput.end() - 1) == '\xd1') {
								currentInput.pop_back();
							}
						}
					}
					break;
				case '\r':
					if (conf.questions[currentPointer]->check(
						conf.questions[currentPointer]->answer,
						conf.questions[currentPointer]->input)) {
						bgr = bgb = 0; // Green
						conf.questions[currentPointer]->input += " " + msgFromChecker;
						currentPointer++;
					} else {
						bgg = bgb = 0; // Red
						conf.questions[currentPointer]->input = "";
					}
					break;
				default:
					sf::Utf8::encode(ev.text.unicode, std::back_inserter(tmp));
					currentInput.append(tmp);
					break;
			}
			break;
		default:
			break;
	}
}

void Main::exit() {
	window->close();
	system("setxkbmap en_US");
}

int main(int argc, char** argv) {
	std::string usage = std::string("Usage:\n    ") + argv[0] + " [-d] <conf.py>";
	if (argc < 2) {
		std::cout << usage;
		return 1;
	}
	// FIXME: For some unknown reason language switch won't work
	system("setxkbmap ru");
	if (argc > 2) {
		if (std::string(argv[1]) != "-d") {
			std::cout << usage;
		} else {
			Main::getInstance()->debug = true;
		}
		argv++;
	}
	Main::getInstance()->init(argv[1]);
	Main::getInstance()->runLoop();
	return 0;
}
