#include "power.h"
#include <iostream>

using namespace Game;

Power::Power() {
	
}

bool Power::canAfford(int pScore) {
	return pScore >= MenuItems::Menu::powerPrices[powerNo];
}

void Power::start(Player& user, Player& opponent) {
	toggled = true;
	curFrame = 0;
}

void Power::update(Player& player, Player& opponent) {
	curFrame++;

	if (curFrame >= frameDuration)
		end(player, opponent);
}

void Power::end(Player& player, Player& opponent) {
	toggled = false;
}

Attack::Attack() : Power() {
	powerNo = 0;
}

Absorb::Absorb() : Power() {
	powerNo = 1;
}

Fire::Fire() : Power() {
	powerNo = 2;
}

Freeze::Freeze() : Power() {
	powerNo = 3;
}

void Freeze::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
	opponent.setCurSpeed(0);
	opponent.setCurFillColor(Color::White);
	opponent.setCurOutlineColor(Color(127, 127, 127));
}

void Freeze::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	opponent.restoreCurSpeed();
	opponent.setCurFillColor(opponent.skinColor);
	opponent.setCurOutlineColor(opponent.skinOutlineColor);
}

Shield::Shield() : Power() {
	powerNo = 4;
}

Speed::Speed() : Power() {
	powerNo = 5;
	srand(time(NULL));
}

void Speed::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
	player.setCurSpeed(player.getCurSpeed() * 2);
	//initEffect();
}

void Speed::initEffect() {
	for (Bolt b : bolts) {
		b.setLineNo(rand() % (LINES_MAX - LINES_MIN) + LINES_MIN);

		//randomizes color between yellow and blue
		if (rand() % 2 == 0)
			b.setColor(outerYellow, innerYellow);
		else
			b.setColor(outerBlue, innerBlue);

		//randomize the length and rotation of each line
		for (int i = 0; i < b.lineNo; i++) {
			int length = rand() % (LENGTH_MAX - LENGTH_MIN) + LENGTH_MIN;
			b.lines[i].setSize(Vector2f(length, 8));
			b.innerLines[i].setSize(Vector2f(length, 8));

			int rotate = rand() % 180 + 1;
			b.lines[i].rotate(rotate);
			b.innerLines[i].rotate(rotate);
		}
	}
}

void Speed::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.restoreCurSpeed();
}