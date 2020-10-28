#include "player.h"
#include <string>
#include <iostream>

using namespace Game;

Player::Player() {
	setOutlineThickness(5);
}

void Player::initPowers() {
	for (int i = 0; i < 3; i++) {
		switch (arsenal.getPowerSlot(i)) {
		case 1:
			powers[i] = Attack();
			break;
		case 2:
			powers[i] = Absorb();
			break;
		case 3:
			powers[i] = Fire();
			break;
		case 4:
			powers[i] = Freeze();
			break;
		case 5:
			powers[i] = Shield();
			break;
		case 6:
			powers[i] = Speed();
			break;
		default:
			throw std::runtime_error("Power was not properly stored.");
			break;
		}
	}
}

void Player::draw(RenderWindow& window, Text t) {
	window.draw(*this);

	//display score
	t.setString(std::to_string(score));
	Vector2f pos = getPosition();
	t.setPosition(Vector2f(pos.x - t.getCharacterSize() - 5, pos.y - t.getCharacterSize() - 5));
	t.setFillColor(Color::Yellow);
	window.draw(t);

	if (arsenal.isVisible())
		arsenal.draw(window, sprite, t);
}

void Player::move(Vector2f mapSize) {
	Vector2f pos = getPosition();
	Vector2f nPos = Vector2f(pos.x, pos.y);

	if (!upR)
		nPos.y -= curSpeed;
	if (!rightR)
		nPos.x += curSpeed;
	if (!downR)
		nPos.y += curSpeed;
	if (!leftR)
		nPos.x -= curSpeed;

	//ensure bounds
	int pSize = getRadius() * 2;
	if (nPos.x < 0)
		nPos.x = 0;
	else if (nPos.x > mapSize.x - pSize)
		nPos.x = mapSize.x - pSize;
	if (nPos.y < 0)
		nPos.y = 0;
	else if (nPos.y > mapSize.y - pSize)
		nPos.y = mapSize.y - pSize;

	setPosition(nPos);
}

void Player::keyPressed(Clock clock) {
	//if the player is a cpu, it doesn't react to key event
	if (!isCpu) {
		if (Keyboard::isKeyPressed(bindings[4])) {
			if (downR)
				upR = false;
		}
		if (Keyboard::isKeyPressed(bindings[5])) {
			if (leftR)
				rightR = false;
		}
		if (Keyboard::isKeyPressed(bindings[6])) {
			if (upR)
				downR = false;
		}
		if (Keyboard::isKeyPressed(bindings[7])) {
			if (rightR)
				leftR = false;
		}
	}
}

void Player::keyReleased(Event e, Clock clock) {
	if (!isCpu) {
		if (e.key.code == bindings[0]) {
			if (!arsenal.isVisible()) {
				Vector2f pos = getPosition();
				arsenal.setLocation(Vector2f(pos.x + getRadius(), pos.y - 200));
			}

			arsenal.setVisible(!arsenal.isVisible());
		}
		else if (e.key.code == bindings[1]) {
			//attack 1
		}
		else if (e.key.code == bindings[2]) {
			//attack 2
		}
		else if (e.key.code == bindings[3]) {
			//attack 3
		}
		else if (e.key.code == bindings[4]) {
			upR = true;
		}
		else if (e.key.code == bindings[5]) {
			rightR = true;
		}
		else if (e.key.code == bindings[6]) {
			downR = true;
		}
		else if (e.key.code == bindings[7]) {
			leftR = true;
		}
	}
}