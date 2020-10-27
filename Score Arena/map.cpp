#include <math.h>
#include "map.h"

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

	for(int i = 0; i < POINTS; i++)
		points[i].setSize(Vector2f(pointSize, pointSize));

	srand(time(NULL));
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

		
		players[0].draw(window);
		players[1].draw(window);
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
}

void Map::initPoints() {
	//relocate and color points
	for (int i = 0; i < POINTS; i++) {
		randomizeLocation(i);
		points[i].setFillColor(getSkinColor(rand() % 7));
	}
}

void Map::randomizeLocation(int i) {
	bool overlap = false;
	//keep randomizing location of point until it doesn't overlap with other points
	do {
		Vector2f pos = Vector2f(rand() % (width - pointSize),
			rand() % (height - pointSize));
		points[i].setPosition(pos);

		overlap = false;

		//check previous point positions to see if they overlap with current point
		for (int j = 0; j < i; j++) {
			Vector2f otherPos = points[j].getPosition();
			if (((pos.x >= otherPos.x && pos.x <= otherPos.x + pointSize) ||
				(pos.x <= otherPos.x && pos.x + pointSize >= otherPos.x)) &&
				((pos.y <= otherPos.y && pos.y + pointSize >= otherPos.y) ||
					(pos.y >= otherPos.y && pos.y <= otherPos.y + pointSize))) {
				overlap = true;
				break;
			}
		}
	} while (overlap);
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