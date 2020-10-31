#include "power.h"

using namespace Game;

Power::Power() {
	
}

void Power::landAttack() {
	attackLanded = true;
	curFrame = frameDuration - pushback;
}

void Power::draw(RenderWindow&, Player& player, Player& opponent) {
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

	if (attackLanded) {
		Vector2f ppos = player.getPosition(), opos = opponent.getPosition();
		int speed = player.getSpeed() * 2;

		if (ppos.x <= opos.x) {
			ppos.x -= speed;
			opos.x += speed;
		}
		else {
			opos.x -= speed;
			ppos.x += speed;
		}

		if (ppos.y <= opos.y) {
			ppos.y -= speed;
			opos.y += speed;
		}
		else {
			opos.y -= speed;
			ppos.y += speed;
		}

		player.setPosition(ppos);
		opponent.setPosition(opos);
	}

	if (curFrame >= frameDuration)
		end(player, opponent);
}

void Power::end(Player& player, Player& opponent) {
	attackLanded = false;
	toggled = false;
}

Attack::Attack() : Power() {
	powerNo = 0;
}

void Attack::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
	player.setCurFillColor(Color::Black);
}

void Attack::update(Player& player, Player& opponent) {
	Power::update(player, opponent);
	Vector2f pos = player.getPosition(), opos = opponent.getPosition();
	if (pos.x >= opos.x - player.getRadius() && pos.x <= opos.x + player.getRadius()
		&& pos.y >= opos.y - player.getRadius() && pos.y <= opos.y + player.getRadius())
		landAttack();
}

void Attack::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.setCurFillColor(player.skinColor);
}

Absorb::Absorb() : Power() {
	setDrawable(true);
	powerNo = 1;
}

void Absorb::landAttack() {
	Power::landAttack();
	ppf = (float) MenuItems::Menu::powerDmg[powerNo] / (float) pushback;
	if (ppf <= 0)
		ppf = 1;
	
	//if ppf won't cover the powerDmg amount, take away the remaining points at first
	if (ppf * pushback < MenuItems::Menu::powerDmg[powerNo]) {
		remaining = MenuItems::Menu::powerDmg[powerNo] - ppf * pushback;
		ppfTooSmall = true;
	}
}

void Absorb::draw(RenderWindow& window, Player& player, Player& opponent) {
	if (toggled) {

	}
}

void Absorb::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
}

void Absorb::update(Player& player, Player& opponent) {
	Power::update(player, opponent);
	Vector2f pos = player.getPosition(), opos = opponent.getPosition();
	if (pos.x >= opos.x - player.getRadius() && pos.x <= opos.x + player.getRadius()
		&& pos.y >= opos.y - player.getRadius() && pos.y <= opos.y + player.getRadius())
		landAttack();

	if (attackLanded) {
		player.score += ppf;
		opponent.score -= ppf;

		if (ppfTooSmall) {
			player.score += remaining;
			opponent.score -= remaining;
			ppfTooSmall = false;
		}
	}
}

void Absorb::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
}

Fire::Fire() : Power() {
	powerNo = 2;
	setDrawable(true);
}

void Fire::draw(RenderWindow& window, Player& player, Player& opponent) {
	if (toggled) {
		Vector2f pos = player.getPosition();
		int radius = player.getRadius();
		pos.x += radius;
		pos.y += radius;

		innerRing.setPosition(pos);
		outerRing.setPosition(pos);
		lineHoriz.setPosition(pos);
		lineVert.setPosition(pos);

		window.draw(lineHoriz);
		window.draw(lineVert);
		window.draw(innerRing);
		window.draw(outerRing);
	}
}

void Fire::start(Player& player, Player& opponent) {
	Power::start(player, opponent);

	int pRadius = player.getRadius();

	innerRing.setRadius(pRadius / 10);
	outerRing.setRadius(pRadius / 5);
	outerRing.setFillColor(Color::Transparent);
	outerRing.setOutlineThickness(5);
	lineHoriz.setSize(Vector2f(pRadius, 10));
	lineVert.setSize(Vector2f(10, pRadius));

	innerRing.setFillColor(Color::Black);
	outerRing.setFillColor(Color::Black);
	lineHoriz.setFillColor(Color::Black);
	lineVert.setFillColor(Color::Black);

	FloatRect inRingRect = innerRing.getLocalBounds();
	innerRing.setOrigin(inRingRect.left + inRingRect.width / 2.0f,
		inRingRect.top + inRingRect.height / 2.0f);

	FloatRect outRingRect = outerRing.getLocalBounds();
	outerRing.setOrigin(outRingRect.left + outRingRect.width / 2.0f,
		outRingRect.top + outRingRect.height / 2.0f);

	FloatRect lineHorRect = lineHoriz.getLocalBounds();
	lineHoriz.setOrigin(lineHorRect.left + lineHorRect.width / 2.0f,
		lineHorRect.top + lineHorRect.height / 2.0f);

	FloatRect lineVerRect = lineVert.getLocalBounds();
	lineVert.setOrigin(lineVerRect.left + lineVerRect.width / 2.0f,
		lineVerRect.top + lineVerRect.height / 2.0f);
}

void Fire::update(Player& player, Player& opponent) {
	Power::update(player, opponent);
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

void Speed::draw(RenderWindow& window, Player& player, Player& opponent) {
	if (toggled) {
		for (Bolt& b : bolts) {
			Vector2f pos = player.getPosition();
			pos.x += b.playerPos.x;
			pos.y += b.playerPos.y;
			b.setLocation(pos);
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
			b.lines[i].setSize(Vector2f(length, 4));

			int rotate = rand() % 180 + 1;
			b.lines[i].rotate(rotate);
		}
	}
}

void Speed::update(Player& player, Player& opponent) {
	Power::update(player, opponent);

	if (curFrame % 5 == 0) {
		int size = player.getRadius() * 2;
		bolts[curBolt++].playerPos = Vector2f(rand() % size, rand() % size);

		if (curBolt >= BOLT_NO)
			curBolt = 0;
	}
}

void Speed::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.restoreCurSpeed();
}