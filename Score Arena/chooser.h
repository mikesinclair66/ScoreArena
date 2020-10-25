#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Chooser {
	const int ARROW_SIZE = 100;
	const int ARROW_OUTLINE = 10;
	CircleShape a1, a2;
	void initArrow(CircleShape&, bool);

public:
	Chooser();
	void draw(RenderWindow&);
	void setPosition(Vector2f, int);
};