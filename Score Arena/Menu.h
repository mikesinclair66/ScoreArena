#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "selector.h"
#include "chooser.h"

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

	//power select page
	bool singlePlayer;
	Chooser colorSelect[2];
	Chooser powerSelect;
	const int SPACE_CSELECT = 80, SPACE_PSELECT = 100;

public:
	static const int CHAR_SIZE = 45;//the size of a character in a label

	Menu(int, int);
	void draw(RenderWindow&);
	void select(int);
	bool isActive() { return active; }
	void setActive(bool active, RenderWindow&);
	void activateSelected();
	void keyPressed();
	void keyReleased(Event);
	void mouseMoved();
	void mouseReleased();
	void setExitQueue(bool val) { queueExit = val; }
	bool getExitQueue() { return queueExit; }
};