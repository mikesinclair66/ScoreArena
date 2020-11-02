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

		//update per frame
		int curFrame = clock.getElapsedTime().asMilliseconds() / 20;
		if (curFrame != frameCount) {
			finish(Vector2f(width, height));

			if (finishAnimation.isActive())
				finishAnimation.update();
			if (finishAnimation.queueExit) {
				//exit to menu
				finishAnimation.queueExit = false;
				setActive(false);
				queueExit = true;
			}

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

		//draw finish animation if needed
		if (finishAnimation.isActive())
			finishAnimation.draw(window, text);
	}
}

void Map::loadTexture(Texture t) {
	this->t = t;
}

void Map::loadMenuStats(MenuItems::Menu& menu) {
	loadTexture(menu.getMapTexture());
	players[0].setName("Player 1");
	players[0].setFillColor(menu.getPlayerColor(0));
	players[0].setOutlineColor(menu.getPlayerOutlineColor(0));
	players[1].setName("Player 2");
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

void Map::finish(Vector2f mapSize) {
	if (!finishAnimation.isActive()) {
		if (players[0].score < 0)
			finishAnimation.start(&players[1], mapSize);
		else if (players[1].score < 0)
			finishAnimation.start(&players[0], mapSize);
		else
			return;
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

void FinishAnimation::start(Player* winner, Vector2f screenSize) {
	frameCount = 0;
	finishText = winner->getName() + " wins!";
	finishRect.setFillColor(winner->skinColor);
	finishRect.setOutlineColor(Color::Black);
	finishRect.setOutlineThickness(8);
	rectPos = Vector2f(-screenSize.x, -screenSize.y);
	finishRect.setPosition(rectPos);
	finishRect.setSize(screenSize);
	textPos = Vector2f(-screenSize.x / 2, -screenSize.y / 2);
	rectEndPos = Vector2f(0, 0);
	textEndPos = Vector2f(screenSize.x / 2, screenSize.y / 2);
	toggled = true;
}

void FinishAnimation::draw(RenderWindow& window, Text t) {
	int curCharSize = t.getCharacterSize();
	t.setCharacterSize(80);
	t.setString(finishText);
	t.setFillColor(Color::White);
	finishRect.setPosition(rectPos);
	t.setPosition(textPos);

	//set local bounds
	FloatRect rect = t.getLocalBounds();
	t.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);

	window.draw(finishRect);
	window.draw(t);
	t.setCharacterSize(curCharSize);
}

void FinishAnimation::update() {
	frameCount++;

	auto progress = [](Vector2f startPos, Vector2f endPos, int speed) {
		if (startPos.x < endPos.x)
			startPos.x += speed;
		else if (startPos.x > endPos.x)
			startPos.x = endPos.x;

		if (startPos.y < endPos.y)
			startPos.y += speed;
		else if (startPos.y > endPos.y)
			startPos.y = endPos.y;

		return startPos;
	};
	rectPos = progress(rectPos, rectEndPos, SPEED);
	textPos = progress(textPos, textEndPos, SPEED);

	if (frameCount >= frameDuration)
		end();
}

void FinishAnimation::end() {
	toggled = false;
	queueExit = true;
}