#include "mapIcon.h"

using namespace MenuItems;

MapIcon::MapIcon() {
	setOutlineColor(Color::Black);
	setOutlineThickness(8);
}

void MapIcon::draw(RenderWindow& window, Text t) {
	window.draw(*this);

	if (disabled) {
		t.setString("?");
		t.setFillColor(Color::White);
		t.setPosition(getPosition());
		FloatRect textRect = t.getLocalBounds();
		t.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		window.draw(t);
	}
}

bool MapIcon::loadImage(string path) {
	if (!t.loadFromFile(path))
		throw runtime_error("Map image couldn\'t be loaded in menu.");

	setTexture(&t);
}

bool MapIcon::requestSelect(Vector2i pos) {
	if (!disabled) {
		Vector2f location = getPosition();
		FloatRect rect = getLocalBounds();

		if (pos.x >= location.x - rect.width / 2 && pos.x <= location.x + rect.width / 2
			&& pos.y >= location.y - rect.height / 2 && pos.y <= location.y + rect.height / 2) {
			setOutlineColor(Color::White);
			return true;
		}
		else
			setOutlineColor(Color::Black);
	}

	return false;
}

void MapIcon::setDisabled(bool disabled) {
	this->disabled = disabled;

	if (disabled)
		setFillColor(Color::Black);
}