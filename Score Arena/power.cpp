#include "power.h"

using namespace Game;

Power::Power() {
	
}

bool Power::canAfford(int pScore) {
	return pScore >= MenuItems::Menu::powerPrices[powerNo];
}

void Power::start() {
	toggled = true;
	curFrame = 0;
}

void Power::update() {
	curFrame++;

	if (curFrame >= frameDuration)
		end();
}

void Power::end() {
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

Shield::Shield() : Power() {
	powerNo = 4;
}

Speed::Speed() : Power() {
	powerNo = 5;
}