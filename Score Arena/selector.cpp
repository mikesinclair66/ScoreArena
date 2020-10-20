#include "selector.h"

Selector::Selector() {
	RectangleShape::setFillColor(c1);
	shadow.setFillColor(c2);
}

void Selector::setFillColor(Color c1, Color c2) {
	this->c1 = c1;
	this->c2 = c2;

	RectangleShape::setFillColor(c1);
	shadow.setFillColor(c2);
}