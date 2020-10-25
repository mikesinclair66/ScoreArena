#include <iostream>
#include "chooser.h"

using namespace std;

Chooser::Chooser() {
	initArrow(a1, true);
	initArrow(a2, false);
}

void Chooser::draw(RenderWindow& window) {
	window.draw(a1);
	window.draw(a2);
}

void Chooser::requestSelect(Vector2i mouse) {
	Vector2f pos1 = a1.getPosition(), pos2 = a2.getPosition();

	if (mouse.x >= pos1.x - a1.getRadius() && mouse.x <= pos1.x + a1.getRadius()
		&& mouse.y >= pos1.y - a1.getRadius() && mouse.y <= pos1.y + a1.getRadius())
		select(1);
	else if (mouse.x >= pos2.x - a2.getRadius() && mouse.x <= pos2.x + a2.getRadius()
		&& mouse.y >= pos2.y - a2.getRadius() && mouse.y <= pos2.y + a2.getRadius())
		select(2);
	else
		select(0);
}

void Chooser::activateSelected() {
	if (selected == 1)
		slot--;
	else if (selected == 2)
		slot++;

	if (slot < 0)
		slot = slotMax - 1;
	else if (slot > slotMax - 1)
		slot = 0;
}

void Chooser::initArrow(CircleShape& c, bool first) {
	c = CircleShape(ARROW_SIZE, 3);
	if (first)
		c.rotate(270);
	else
		c.rotate(90);
	Color gray = Color(127, 127, 127);
	c.setFillColor(gray);
	c.setOutlineColor(Color::Black);
	c.setOutlineThickness(ARROW_OUTLINE);
}

/// <summary>
/// Sets the position with the first arrow starting at pos.
/// Variable space determines the space between the two arrows.
/// </summary>
void Chooser::setPosition(Vector2f pos, int space) {
	this->pos = pos;

	a1.setPosition(Vector2f(pos.x - space / 2 - a1.getRadius(), pos.y));
	a2.setPosition(Vector2f(pos.x + space / 2 + a1.getRadius(), pos.y));

	FloatRect o1 = a1.getLocalBounds(), o2 = a2.getLocalBounds();
	a1.setOrigin(o1.left + o1.width / 2.0f, o1.top + o1.height / 2);
	a2.setOrigin(o2.left + o2.width / 2.0f, o2.top + o2.height / 2);
}

void Chooser::select(int s) {
	selected = s;

	switch (s) {
	case 0:
		a1.setOutlineColor(Color::Black);
		a2.setOutlineColor(Color::Black);
		break;
	case 1:
		a1.setOutlineColor(Color::White);
		a2.setOutlineColor(Color::Black);
		break;
	case 2:
		a1.setOutlineColor(Color::Black);
		a2.setOutlineColor(Color::White);
		break;
	default:
		throw runtime_error("A chooser object can only select from 0-2.");
	}
}