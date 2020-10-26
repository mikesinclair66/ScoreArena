#include "message.h"

using namespace MenuItems;

void Message::draw(RenderWindow& window, Text t) {
	if (checkActive() && activated) {
		t.setFillColor(Color::Red);
		t.setString(msg);
		
		//locate text before drawing
		t.setPosition(getPosition());
		FloatRect textRect = t.getLocalBounds();
		t.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		window.draw(t);
	}
}

void Message::activate() {
	clock.restart();
	activated = true;
}

void Message::deactivate() {
	activated = false;
}

bool Message::checkActive() {
	return (clock.getElapsedTime().asSeconds() < 6);
}