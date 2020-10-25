#include "chooser.h"

Chooser::Chooser() {
	initArrow(a1, true);
	initArrow(a2, false);
}

void Chooser::draw(RenderWindow& window) {
	window.draw(a1);
	window.draw(a2);
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
	a1.setPosition(pos);
	a2.setPosition(Vector2f(pos.x + a1.getRadius() * 2 + space, pos.y));

	FloatRect o1 = a1.getLocalBounds(), o2 = a2.getLocalBounds();
	a1.setOrigin(o1.left + o1.width / 2.0f, o1.top + o1.height / 2);
	a2.setOrigin(o2.left + o2.width / 2.0f, o2.top + o2.height / 2);
}