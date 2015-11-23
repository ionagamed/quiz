#include "Question.h"
#include "Main.h"
#include "utf8.h"

Question::Question(std::string que, std::string ans, std::function <bool(std::string, std::string)> check) {
	question = que;
	answer = ans;
	this->check = check;

	text.setFont(Main::getInstance()->font);
	text.setColor(sf::Color::Black);
	showTheThing = true;
}

void Question::draw(int pos) {
	std::string str = question;
	if (pos == 0) {
		text.setCharacterSize(32);
		text.setPosition(32, Main::getInstance()->window->getSize().y / 2 - 32);
		// Four spaces hardcoded
		str += "\n    " + input;
		if (showTheThing) {
			str += "|";
		}
	} else if (pos > 0) {
		text.setCharacterSize(24);
		text.setPosition(32, Main::getInstance()->window->getSize().y / 2 + 26 * pos + 36);
	} else {
		text.setCharacterSize(24);
		text.setPosition(32, Main::getInstance()->window->getSize().y / 2 + 52 * pos - 36);
		str += "\n    " + input;
	}
	// Very slow, but SFML can't get utf8 right
	text.setString(sf::toUtf32(str));

	Main::getInstance()->window->draw(text);
}

void Question::loop(sf::Time dt) {
	this->dt += dt;
	if (this->dt.asSeconds() > .5) {
		showTheThing ^= 1;
		this->dt = sf::Time();
	}
}
