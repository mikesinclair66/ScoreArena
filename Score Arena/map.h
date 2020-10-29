#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "player.h"
#include "point.h"
#include "power.h"

using namespace sf;

namespace Game {
	class Map {
		bool active = false;
		int width, height;
		int resolution;
		Texture t;
		Sprite sprite;
		Font font;
		Text text;
		const static int POINTS = 100;//number of points on the map at a time
		int pointSize;
		const int POINT_SIZE_MOD = 75;
		Point points[POINTS];
		Power *powers1[3], *powers2[3];

	public:
		Player players[2];
		Clock clock;
		int frameCount = 0;//frames since clock last restarted
		const int FRAME_LIMIT = 40;

		Map(int, int);
		void draw(RenderWindow&);
		void loadTexture(Texture);
		void loadMenuStats(MenuItems::Menu&);
		void initPoints();
		void initPowers();
		//randomizes location of specified point
		void randomizeLocation(int);
		void requestPointCollision(Player&);
		void setActive(bool active) { this->active = active; }
		bool isActive() { return active; }
		Color getSkinColor(int slot);
	};
}