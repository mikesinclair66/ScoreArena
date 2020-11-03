#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "player.h"
#include "point.h"
#include "power.h"

using namespace sf;

namespace Game {
	class FinishAnimation {
		bool toggled = false;
		const int SPEED = 35;
		RectangleShape finishRect;
		Vector2f rectPos, textPos;
		Vector2f rectEndPos, textEndPos;
		string finishText;
		int frameCount = 0, frameDuration = 200;

	public:
		bool queueExit = false;

		void start(Player* winner, Vector2f screenSize);
		void draw(RenderWindow&, Text t);
		void update();
		void end();
		bool isActive() { return toggled; }
	};

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
		FinishAnimation finishAnimation;

	public:
		bool queueExit = false;
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
		void finish(Vector2f);
		void setActive(bool active) { this->active = active; }
		bool isActive() { return active; }
		Color getSkinColor(int slot);
	};

	class Map2 : public Map {
		
	public:
		Map2(int, int);
	};

	class Map3 : public Map {

	public:
		Map3(int, int);
	};
}