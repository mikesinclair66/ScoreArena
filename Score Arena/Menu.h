#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "arsenal.h"
#include "chooser.h"
#include "mapIcon.h"
#include "message.h"
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
	bool queueExit = false, queueStartGame = false;

	//power select page
	bool singlePlayer;
	Chooser colorSelect[2];
	CircleShape pSkins[2];
	int pSkinColors[2];
	Chooser powerSelect;
	const int SPACE_CSELECT = 200, SPACE_PSELECT = 175;
	Texture powerTextures[6];
	int powerPrices[6] = {
		20,//attack
		30,//absorb
		40,//fire
		//TODO change the following
		40,//freeze
		40,//shield
		40//speed
	};
	int powerDmg[3] = {
		30,
		20,
		15,//damage for each shot
	};
	Arsenal arsenals[2];
	Message msg;

	//map select page
	MapIcon maps[6];
	int selectedMap;

public:
	static const int CHAR_SIZE = 45;//the size of a character in a label

	Menu(int, int);
	void draw(RenderWindow&);
	void drawStats(RenderWindow&, Text, Vector2f, int);
	void select(int);
	bool isActive() { return active; }
	void setActive(bool active, RenderWindow&);
	void setActive(bool active) { this->active = false; }
	void activateSelected();
	void clear(int);
	bool checkPowersFilled();
	void keyPressed();
	void keyReleased(Event);
	void mouseMoved();
	void mouseReleased();
	void setExitQueue(bool val) { queueExit = val; }
	void setStartGameQueue(bool val) { queueStartGame = val; }
	bool getExitQueue() { return queueExit; }
	bool getStartGameQueue() { return queueStartGame; }
	Color getSkinColor(int slot);
	Color getSkinOutlineColor(int slot);
};