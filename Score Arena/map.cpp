#include <math.h>
#include "map.h"
#include "menu.h"
#include <iostream>
#include <string>

using namespace Game;

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;
	resolution = sqrt(pow(width, 2) + pow(height, 2));

	//pointSize is calculated using pythagorean theorem (resolution)
	pointSize = resolution / POINT_SIZE_MOD;

	//set size and location of players based on screen size
	players[0].setRadius(resolution / (POINT_SIZE_MOD / 3));
	players[1].setRadius(resolution / (POINT_SIZE_MOD / 3));
	players[0].setPosition(Vector2f(width / 4 - players[0].getRadius() / 2,
		height / 2 - players[0].getRadius() / 2));
	players[1].setPosition(Vector2f(width * 3 / 4 - players[1].getRadius() / 2,
		height / 2 - players[1].getRadius() / 2));
	players[0].setMapSize(Vector2f(width, height));
	players[1].setMapSize(Vector2f(width, height));

	for(int i = 0; i < POINTS; i++)
		points[i].setSize(Vector2f(pointSize, pointSize));

	srand(time(NULL));

	if (!font.loadFromFile("res\\Sinclairscript-Regular.ttf")) {
		if (!font.loadFromFile("res\\Sinclairscript-Regular.otf"))
			throw runtime_error("Could not load Sinclair_Script font.");
	}
	text.setFont(font);
	text.setCharacterSize(MenuItems::Menu::CHAR_SIZE);
	text.setStyle(Text::Bold);
}

void Map::draw(RenderWindow& window) {
	if (isActive()) {
		//draw bg
		sprite.setTexture(t);
		Vector2u bgSize = t.getSize();
		for (int i = 0; i < height; i += bgSize.y) {
			for (int j = 0; j < width; j += bgSize.x) {
				sprite.setPosition(Vector2f(j, i));
				window.draw(sprite);
			}
		}

		for (int i = 0; i < POINTS; i++)
			points[i].draw(window);

		int curFrame = clock.getElapsedTime().asMilliseconds() / 20;
		if (curFrame != frameCount) {
			Vector2f mapSize = Vector2f(width, height);

			for (int i = 0; i < 2; i++) {
				players[i].move();
				requestPointCollision(players[i]);
			}

			//update active/toggled powers
			for (int i = 0; i < 3; i++) {
				if (powers1[i]->isActive())
					powers1[i]->update(players[0], players[1]);
				if (powers2[i]->isActive())
					powers2[i]->update(players[1], players[0]);
			}

			//check for p1 power queue
			int pq1 = players[0].getPowerQueue();
			if (pq1 > 0) {
				if (powers1[pq1 - 1]->requiresPrice() &&
					powers1[pq1 - 1]->canAfford(players[0].score) &&
					!powers1[pq1 - 1]->isActive()) {
					players[0].score -= powers1[pq1 - 1]->getPrice();
					powers1[pq1 - 1]->start(players[0], players[1]);
				}
				else if (powers1[pq1 - 1]->isActive())
					powers1[pq1 - 1]->activate();

				players[0].setPowerQueue(0);
			}

			//repeat process for p2
			int pq2 = players[1].getPowerQueue();
			if (pq2 > 0) {
				if (powers2[pq2 - 1]->requiresPrice() &&
					powers2[pq2 - 1]->canAfford(players[1].score) &&
					!powers2[pq2 - 1]->isActive()) {
					players[1].score -= powers2[pq2 - 1]->getPrice();
					powers2[pq2 - 1]->start(players[1], players[0]);
				}
				else if (powers2[pq2 - 1]->isActive())
					powers2[pq2 - 1]->activate();

				players[1].setPowerQueue(0);
			}
		}

		frameCount = curFrame;
		if (frameCount > FRAME_LIMIT) {
			clock.restart();
			frameCount = 0;
		}

		players[0].draw(window, text);
		players[1].draw(window, text);

		//draw powers which need to be drawn
		for (int i = 0; i < 3; i++) {
			if (powers1[i]->getDrawable())
				powers1[i]->draw(window, players[0], players[1]);
			if (powers2[i]->getDrawable())
				powers2[i]->draw(window, players[1], players[0]);
		}
	}
}

void Map::loadTexture(Texture t) {
	this->t = t;
}

void Map::loadMenuStats(MenuItems::Menu& menu) {
	loadTexture(menu.getMapTexture());
	players[0].setFillColor(menu.getPlayerColor(0));
	players[0].setOutlineColor(menu.getPlayerOutlineColor(0));
	players[1].setFillColor(menu.getPlayerColor(1));
	players[1].setOutlineColor(menu.getPlayerOutlineColor(1));
	players[1].setCpu(menu.isCpu());
	players[0].setKeyBindings(menu.getBindings(0));
	players[1].setKeyBindings(menu.getBindings(1));
	//gets the power slots from the menu
	for (int i = 0; i < 3; i++) {
		players[0].arsenal.setPowerSlot(i, menu.getPowerSlot(0, i));
		players[1].arsenal.setPowerSlot(i, menu.getPowerSlot(1, i));
	}
	initPowers();
}

void Map::initPoints() {
	//relocate and color points
	for (int i = 0; i < POINTS; i++) {
		randomizeLocation(i);
		points[i].setFillColor(getSkinColor(rand() % 7));
	}
}

void Map::initPowers() {
	if (players[1].getCpu())
		srand(time(NULL));

	for (int i = 0; i < 3; i++) {
		switch (players[0].arsenal.getPowerSlot(i)) {
		case 1:
			powers1[i] = new Attack();
			break;
		case 2:
			powers1[i] = new Absorb();
			break;
		case 3:
			powers1[i] = new Fire();
			break;
		case 4:
			powers1[i] = new Freeze();
			break;
		case 5:
			powers1[i] = new Shield();
			break;
		case 6:
			powers1[i] = new Speed();
			break;
		default:
			throw std::runtime_error("Power was not properly stored.");
			break;
		}

		//get the second player arsenal slot if in multiplayer; otherwise randomly assign power
		int slot = ((!players[1].getCpu()) ? players[1].arsenal.getPowerSlot(i) : rand() % 6 + 1);
		switch (slot) {
		case 1:
			powers2[i] = new Attack();
			break;
		case 2:
			powers2[i] = new Absorb();
			break;
		case 3:
			powers2[i] = new Fire();
			break;
		case 4:
			powers2[i] = new Freeze();
			break;
		case 5:
			powers2[i] = new Shield();
			break;
		case 6:
			powers2[i] = new Speed();
			break;
		default:
			throw std::runtime_error("Power was not properly stored.");
			break;
		}
	}
}

void Map::randomizeLocation(int i) {
	bool overlapSquares = false;
	//keep randomizing location of point until it doesn't overlap with other points
	do {
		Vector2f pos = Vector2f(rand() % (width - pointSize),
			rand() % (height - pointSize));
		points[i].setPosition(pos);

		overlapSquares = false;

		//check previous point positions to see if they overlap with current point
		for (int j = 0; j < i; j++) {
			Vector2f otherPos = points[j].getPosition();
			if (((pos.x >= otherPos.x && pos.x <= otherPos.x + pointSize) ||
				(pos.x <= otherPos.x && pos.x + pointSize >= otherPos.x)) &&
				((pos.y <= otherPos.y && pos.y + pointSize >= otherPos.y) ||
					(pos.y >= otherPos.y && pos.y <= otherPos.y + pointSize))) {
				overlapSquares = true;
				break;
			}
		}
	} while (overlapSquares);
}

void Map::requestPointCollision(Player& p) {
	Vector2f pos = p.getPosition();
	int size = p.getRadius() * 2;

	for (int i = 0; i < POINTS; i++) {
		Vector2f pointPos = points[i].getPosition();
		if (pointPos.x >= pos.x - pointSize && pointPos.x <= pos.x + size
			&& pointPos.y >= pos.y - pointSize && pointPos.y <= pos.y + size) {
			p.score++;
			randomizeLocation(i);
		}
	}
}

Color Map::getSkinColor(int slot) {
	Color c;

	switch (slot) {
	case 0:
		c = Color(0, 255, 68);//green
		break;
	case 1:
		c = Color(255, 251, 0);//yellow
		break;
	case 2:
		c = Color::Red;//red
		break;
	case 3:
		c = Color(0, 255, 255);//cyan
		break;
	case 4:
		c = Color::Blue;//blue
		break;
	case 5:
		c = Color(208, 0, 255);//magenta
		break;
	case 6:
		c = Color(255, 0, 166);//pink
		break;
	}

	return c;
}