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

void Power::activate() {
	//method is overridden for certain powers
}

Attack::Attack() : Power() {
	powerNo = 0;
}

void Attack::landAttack() {
	Power::landAttack();
	queueDamage = true;
}

void Attack::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
	player.setCurFillColor(Color::Black);
}

void Attack::update(Player& player, Player& opponent) {
	Power::update(player, opponent);
	Vector2f pos = player.getPosition(), opos = opponent.getPosition();
	if (!attackLanded && pos.x >= opos.x - player.getRadius() && pos.x <= opos.x + player.getRadius()
		&& pos.y >= opos.y - player.getRadius() && pos.y <= opos.y + player.getRadius())
		landAttack();

	if (queueDamage) {
		opponent.score -= MenuItems::Menu::powerDmg[powerNo];
		queueDamage = false;
	}
}

void Attack::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.setCurFillColor(player.skinColor);
}

Absorb::Absorb() : Power() {
	setDrawable(true);
	powerNo = 1;

	ring.setOutlineColor(Color::Green);
	ring.setOutlineThickness(10);
	ring.setFillColor(Color::Transparent);
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
	if (toggled && attackLanded) {
		window.draw(ring);
	}
}

void Absorb::start(Player& player, Player& opponent) {
	Power::start(player, opponent);
}

void Absorb::update(Player& player, Player& opponent) {
	Power::update(player, opponent);
	Vector2f pos = player.getPosition(), opos = opponent.getPosition();
	if (!attackLanded && pos.x >= opos.x - player.getRadius() && pos.x <= opos.x + player.getRadius()
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

		int radius = player.getRadius();
		Vector2f pos = player.getPosition(), opos = opponent.getPosition();
		pos.x += radius;
		pos.y += radius;
		ring.setPosition(pos);
		ring.setSize(Vector2f(opos.x + radius - pos.x, opos.y + radius - pos.y));
	}
}

void Absorb::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
}

Fire::Fire() : Power() {
	powerNo = 2;
	setDrawable(true);
	for (int i = 0; i < BULLET_NO; i++) {
		fired[i] = false;
		rotation[i] = 0;
		exploded[i] = false;
		explosion[i].setFillColor(Color::Transparent);
		explosion[i].setOutlineColor(Color::Red);
		directHit[i] = false;
	}

	if (!bulletTexture.loadFromFile("res\\fireball.png"))
		throw runtime_error("Error loading fireball image");
	sprite.setTexture(bulletTexture);
}

void Fire::landAttack() {
	Power::landAttack();
	queueDamage = true;
}

void Fire::draw(RenderWindow& window, Player& player, Player& opponent) {
	if (toggled) {
		window.draw(lineHoriz);
		window.draw(lineVert);
		window.draw(innerRing);
		window.draw(outerRing);

		for (int i = 0; i < BULLET_NO; i++) {
			if (exploded[i])
				window.draw(explosion[i]);

			//if the bullet is done being shot, don't draw it
			if (!fired[i] && bulletNo > i)
				continue;
			sprite.setPosition(bullets[i]);
			sprite.setRotation(rotation[i]);
			window.draw(sprite);
		}
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

	//make player stop moving and set controls to crosshair
	aimPos = player.getPosition();
	aimPos.x += pRadius;
	aimPos.y += pRadius;
	player.setCurSpeed(0);

	//draw amount of bullets under player
	bulletNo = 0;
	Vector2f pos = player.getPosition();
	int radius = player.getRadius();
	pos.y += radius * 2;
	int bulletWidth = bulletTexture.getSize().x;
	for (int i = bulletNo; i < BULLET_NO; i++) {
		bullets[i] = Vector2f(pos.x + ((i + 1) * radius * 2 / BULLET_NO) - bulletWidth, pos.y);
		directHit[i] = false;
	}
}

void Fire::update(Player& player, Player& opponent) {
	if (queueDamage) {
		opponent.score -= MenuItems::Menu::powerDmg[powerNo] / BULLET_NO;
		queueDamage = false;
	}

	//redefines Power::update(), only pushing back the opponent. Also gets rid of time limit
	if (attackLanded) {
		curFrame++;

		Vector2f ppos = player.getPosition(), opos = opponent.getPosition();
		int speed = player.getSpeed() * 2;

		if (ppos.x <= opos.x) {
			opos.x += speed;
		}
		else {
			opos.x -= speed;
		}

		if (ppos.y <= opos.y) {
			opos.y += speed;
		}
		else {
			opos.y -= speed;
		}

		opponent.setPosition(opos);

		if (curFrame >= frameDuration)
			attackLanded = false;
	}
	//end of redefinition

	int speed = player.getSpeed() * 1.75f;
	if (player.getMovementQueue(0))
		aimPos.y -= speed;
	if (player.getMovementQueue(1))
		aimPos.x += speed;
	if (player.getMovementQueue(2))
		aimPos.y += speed;
	if (player.getMovementQueue(3))
		aimPos.x -= speed;

	//assign boundaries to crosshair
	Vector2f size = player.getMapSize();
	if (aimPos.x < 0)
		aimPos.x = 0;
	else if (aimPos.x > size.x)
		aimPos.x = size.x;
	if (aimPos.y < 0)
		aimPos.y = 0;
	else if (aimPos.y > size.y)
		aimPos.y = size.y;

	innerRing.setPosition(aimPos);
	outerRing.setPosition(aimPos);
	lineHoriz.setPosition(aimPos);
	lineVert.setPosition(aimPos);
	
	bool allFalse = true;
	for (int i = 0; i < BULLET_NO; i++) {
		if (fired[i]) {
			bool up = false, right = false, down = false, left = false;

			if (bullets[i].x <= destination[i].x - SPEED) {
				bullets[i].x += SPEED;
				right = true;
			}
			else if (bullets[i].x >= destination[i].x + SPEED) {
				bullets[i].x -= SPEED;
				left = true;
			}

			if (bullets[i].y <= destination[i].y - SPEED) {
				bullets[i].y += SPEED;
				down = true;
			}
			else if (bullets[i].y >= destination[i].y + SPEED) {
				bullets[i].y -= SPEED;
				up = true;
			}

			if (up) {
				if (!right && !left)
					rotation[i] = -90;
				else if (!right)
					rotation[i] = -135;
				else
					rotation[i] = -45;
			}
			if (down) {
				if (!right && !left)
					rotation[i] = 90;
				else if (!right)
					rotation[i] = 135;
				else
					rotation[i] = 45;
			}

			if (left && !up && !right)
				rotation[i] = -180;
			if (right && !up && !down)
				rotation[i] = 0;

			//check for opponent contact
			Vector2f opos = opponent.getPosition();
			int pRadius = opponent.getRadius();
			if (bullets[i].x >= opos.x - pRadius && bullets[i].x <= opos.x + pRadius * 3
				&& bullets[i].y >= opos.y - pRadius && bullets[i].y <= opos.y + pRadius * 3) {
				fired[i] = false;
				directHit[i] = true;
				initExplosion(i);
				landAttack();
			}

			else if (bullets[i].x >= destination[i].x - SPEED &&
				bullets[i].x <= destination[i].x + SPEED
				&& bullets[i].y >= destination[i].y - SPEED && bullets[i].y
				<= destination[i].y + SPEED) {
				fired[i] = false;
				directHit[i] = false;
				initExplosion(i);
			}
		}

		if (exploded[i]) {
			int radius = explosion[i].getRadius() + player.getSpeed();
			explosion[i].setRadius(radius);

			int thickness = explosion[i].getOutlineThickness();
			if (radius < RADIUS_MAX / 2)
				thickness += 3;
			else if (radius >= RADIUS_MAX / 2 && thickness > 4)
				thickness -= 3;
			explosion[i].setOutlineThickness(thickness);

			explosion[i].setPosition(Vector2f(bullets[i].x - explosion[i].getRadius(),
				bullets[i].y - explosion[i].getRadius()));

			//check for opponent contact
			Vector2f opos = opponent.getPosition(), epos = explosion[i].getPosition();
			int pRadius = opponent.getRadius(), eRadius = explosion[i].getRadius();
			if (epos.x >= opos.x - eRadius * 2 && epos.x <= opos.x + eRadius * 2
				&& epos.y >= opos.y - eRadius * 2 && epos.y <= opos.y + eRadius * 2) {
				if (!directHit[i]) {
					landAttack();
					directHit[i] = true;//stops from continuously damaging opponent
				}
			}

			if (radius >= RADIUS_MAX)
				exploded[i] = false;
		}

		if (fired[i] || exploded[i])
			allFalse = false;
	}

	if (bulletNo >= BULLET_NO && allFalse && !attackLanded)
		end(player, opponent);
}

void Fire::initExplosion(int i) {
	exploded[i] = true;
	explosion[i].setRadius(RADIUS_MIN);
	explosion[i].setOutlineThickness(THICKNESS_MIN);
	explosion[i].setPosition(Vector2f(bullets[i].x - explosion[i].getRadius(),
		bullets[i].y - explosion[i].getRadius()));
}

void Fire::end(Player& player, Player& opponent) {
	Power::end(player, opponent);
	player.restoreCurSpeed();
	for (int i = 0; i < BULLET_NO; i++)
		rotation[i] = 0;
}

void Fire::activate() {
	destination[bulletNo] = innerRing.getPosition();
	fired[bulletNo++] = true;
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