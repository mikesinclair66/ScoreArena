#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "selector.h"

using namespace std;
using namespace sf;

class Menu {
	bool active = false;
	int width, height;
	const int SEGMENTS = 7;//segments to divide height by when coordinating options
	int page = 0;
	Image cursorImg;
	Cursor cursor;
	Texture bg, title;
	Sprite sprite;
	Font font;
	Text text;
	Selector selector;
	bool queueExit = false;

public:
	Menu(int, int);
	void draw(RenderWindow&);
	bool isActive() { return active; }
	void setActive(bool active, RenderWindow&);
	void activateSelected();
	void keyPressed();
	void keyReleased(Event);
	void mouseMoved();
	void setExitQueue(bool val) { queueExit = val; }
	bool getExitQueue() { return queueExit; }
};