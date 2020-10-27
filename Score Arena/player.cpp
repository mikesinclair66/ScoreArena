#include "player.h"

using namespace Game;

Player::Player() {

}

void Player::draw(RenderWindow& window) {
	window.draw(*this);
}