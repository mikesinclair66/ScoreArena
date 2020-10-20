#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Selector : public RectangleShape {
	RectangleShape shadow;
	Color c1 = Color::White, c2 = Color::Black;

public:
	Selector();
	void setFillColor(Color, Color c2=Color::Black);
};