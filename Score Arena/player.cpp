#include "player.h"

using namespace Game;

Player::Player() {
	setOutlineThickness(5);
}

void Player::draw(RenderWindow& window, Text t) {
	window.draw(*this);
	if (arsenal.isVisible())
		arsenal.draw(window, sprite, t);
}

void Player::move(Vector2f mapSize) {
	Vector2f pos = getPosition();
	Vector2f nPos = Vector2f(pos.x, pos.y);

	if (!upR)
		nPos.y -= speed;
	if (!rightR)
		nPos.x += speed;
	if (!downR)
		nPos.y += speed;
	if (!leftR)
		nPos.x -= speed;

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