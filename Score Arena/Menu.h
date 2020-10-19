#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Menu {
	int page = 0;
	Texture title;
	string labels[4]{
		"SINGLE PLAYER",
		"MULTI PLAYER",
		"OPTIONS",
		"EXIT"
	};
	Texture bg;
	Image cursorImg;
	Font font;
	Text text;
	Sprite sprite;
	bool active = false;

	Clock clock;
	const float SEGMENTS = 7;//segments to divide screen height by
	RectangleShape selector;
	int selected = 0;//the selected option
	const float SELECT_MOD = 2;
	int width, height;

public:
	Menu(int, int);
	void draw(RenderWindow &window);
	void mouseMoved();
	void mousePressed();
	void mouseReleased();
	bool isActive() { return active; }
	void setActive(bool val, RenderWindow& window);

	bool queueExit = false;//if the user queues to exit the game
};