#include "selector.h"

using namespace MenuItems;

Selector::Selector() {
	setFillColor(Color(255, 255, 255, 127));
}

void Selector::select(int selected, int page) {
	if (selected > 0) {
		Vector2f location = sets[page].getLocation(selected - 1);
		setPosition(Vector2f(location.x, location.y + SELECTOR_SPACE));
		setSize(Vector2f(SELECTOR_HEIGHT, SELECTOR_HEIGHT));
	}

	clock.restart();
}

void Selector::draw(RenderWindow& window, int page, Text t) {
	int selected = sets[page].getSelected();

	if (selected > 0) {
		int size = clock.getElapsedTime().asMilliseconds() * 2;
		t.setString(sets[page].getLabel(selected - 1));
		int maxSize = t.getLocalBounds().width + 25;
		if (size > maxSize)
			size = maxSize;

		setSize(Vector2f(size, SELECTOR_HEIGHT));
		setPosition(Vector2f(sets[page].getLocation(selected - 1).x - size / 2, getPosition().y));

		window.draw(*this);
	}
}

void Selector::Set::push_back(string label, Vector2f location) {
	this->labels.push_back(label);
	this->locations.push_back(location);
}

void Selector::Set::draw(RenderWindow& window, Text text) {
	for (int i = 0; i < labels.size(); i++) {
		if (getSelected() == i + 1)
			text.setFillColor(Color::Yellow);
		else
			text.setFillColor(Color::White);

		text.setString(getLabel(i));
		text.setPosition(getLocation(i));
		//center text at coordinates
		FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		window.draw(text);
	}
}

void Selector::Set::select(int selected) {
	this->selected = selected;
}