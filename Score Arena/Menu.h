#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Menu {
	int page = 0;
	Texture title;
	string labels[4]{
		"Single Player",
		"Multi Player",
		"Options",
		"Exit"
	};
	Texture bg;
	Sprite sprite;
	Image cursorImg;
	bool active = false;

	int width, height;

public:
	Menu(int, int);
	void draw(RenderWindow &window);
	bool isActive() { return active; }
	void setActive(bool val, RenderWindow& window);
};