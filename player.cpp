#include "player.h"
#include <string>
#include <iostream>

using namespace Game;

Player::Player() {
	setOutlineThickness(5);
}

void Player::draw(RenderWindow& window, Text t) {
	if (invisible)
		return;

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

void Player::damage(int score) {
	if (!invincible)
		this->score -= score;
}

void Player::heal(int score) {
	if (!invincible)
		this->score += score;
}

void Player::move() {
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
			powerQueue = 1;
		}
		else if (e.key.code == bindings[2]) {
			powerQueue = 2;
		}
		else if (e.key.code == bindings[3]) {
			powerQueue = 3;
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