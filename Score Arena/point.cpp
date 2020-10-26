#include <stdlib.h>
#include <time.h>
#include "point.h"

using namespace Game;

Point::Point() {
	shadowColor = Color(50, 50, 50, 127);
	shadow.setFillColor(shadowColor);
}

void Point::draw(RenderWindow& window) {
	window.draw(shadow);
	window.draw(*this);
}

void Point::setPosition(Vector2f pos) {
	RectangleShape::setPosition(pos);
	shadow.setPosition(Vector2f(pos.x + SHADOW_DISTANCE, pos.y + SHADOW_DISTANCE));
}

void Point::setSize(Vector2f size) {
	RectangleShape::setSize(size);
	shadow.setSize(size);
}