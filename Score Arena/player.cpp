#include "player.h"

using namespace Game;

Player::Player() {
	setOutlineThickness(5);
}

void Player::draw(RenderWindow& window) {
	window.draw(*this);
}

void Player::keyPressed(Clock clock) {
	//if the player is a cpu, it doesn't react to key event
	if (!isCpu) {
		if (Keyboard::isKeyPressed(bindings[4])) {
			//up
		}
		else if (Keyboard::isKeyPressed(bindings[5])) {
			//right
		}
		else if (Keyboard::isKeyPressed(bindings[6])) {
			//down
		}
		else if (Keyboard::isKeyPressed(bindings[7])) {
			//left
		}
	}
}

void Player::keyReleased(Event e, Clock clock) {
	if (!isCpu) {
		if (e.key.code == bindings[0]) {
			//toggle attack menu
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
			//stop up
		}
		else if (e.key.code == bindings[5]) {
			//stop right
		}
		else if (e.key.code == bindings[6]) {
			//stop down
		}
		else if (e.key.code == bindings[7]) {
			//stop left
		}
	}
}