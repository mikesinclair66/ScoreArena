#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "point.h"

using namespace sf;

namespace Game {
	class Map {
		bool active = false;
		int width, height;
		int resolution;
		Texture t;
		Sprite sprite;
		const static int POINTS = 100;//number of points on the map at a time
		int pointSize;
		const int POINT_SIZE_MOD = 75;
		Point points[POINTS];

	public:
		Player players[2];

		Map(int, int);
		void draw(RenderWindow&);
		void loadTexture(Texture);
		void initPoints();
		//randomizes location of specified point
		void randomizeLocation(int);
		void setActive(bool active) { this->active = active; }
		bool isActive() { return active; }
		Color getSkinColor(int slot);
	};
}