#include "selector.h"

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