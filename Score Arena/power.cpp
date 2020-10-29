#include "power.h"

using namespace Game;

Power::Power() {
	
}

void Power::draw(RenderWindow&) {
	//method is overridden for certain powers
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
	setDrawable(true);
	srand(time(NULL));
}

void Speed::draw(RenderWindow& window) {
	if (toggled) {
		for (Bolt b : bolts) {
			b.draw(window);
		}
	}
}

void Speed::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
	player.setCurSpeed(player.getCurSpeed() * 2.5f);
	initEffect();

	//locate bolts
	Vector2f pos = player.getPosition();
	int radius = player.getRadius();
	bolts[0].setLocation(Vector2f(pos.x - 50, pos.y));
	bolts[1].setLocation(Vector2f(pos.x - 50, pos.y + radius * 2));
	bolts[2].setLocation(Vector2f(pos.x + radius * 2 + 50, pos.y));
	bolts[3].setLocation(Vector2f(pos.x + radius * 2 + 50, pos.y + radius * 2 + 50));
}

void Speed::initEffect() {
	bool yellow = rand() % 2 == 0;

	for (Bolt& b : bolts) {
		b.lineNo = rand() % (LINES_MAX - LINES_MIN) + LINES_MIN;

		//randomizes color between yellow and blue
		if (yellow)
			b.setColor(outerYellow, innerYellow);
		else
			b.setColor(outerBlue, innerBlue);

		//randomize the length and rotation of each line
		for (int i = 0; i < b.lineNo; i++) {
			int length = rand() % (LENGTH_MAX - LENGTH_MIN) + LENGTH_MIN;
			b.lines[i].setSize(Vector2f(length, 8));
			b.innerLines[i].setSize(Vector2f(length, 3));

			int rotate = rand() % 180 + 1;
			b.lines[i].rotate(rotate);
			b.innerLines[i].rotate(rotate);
		}
	}
}

void Speed::update(Player& player, Player& opponent) {
	Power::update(player, opponent);

	if (curFrame % 10 == 0) {
		Vector2f pos = player.getPosition();
		bolts[curBolt++].setLocation(pos);

		if (curBolt >= BOLT_NO)
			curBolt = 0;
	}
}

void Speed::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.restoreCurSpeed();
}