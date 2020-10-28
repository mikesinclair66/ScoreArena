#include "attackArsenal.h"

using namespace Game;

AttackArsenal::AttackArsenal() : Arsenal() {
	background.setSize(Vector2f(700, 300));
	background.setFillColor(Color::White);
	background.setOutlineColor(Color::Black);
	background.setOutlineThickness(5);
}

void AttackArsenal::draw(RenderWindow& window) {
	window.draw(background);
	Arsenal::draw(window);
}

void AttackArsenal::setLocation(Vector2f location) {
	FloatRect bounds = background.getLocalBounds();
	background.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);

	//since the attack arsenal is horizontal , it used ymod horizontally
	for (int i = 0; i < 3; i++) {
		int ymod = 0;
		if (i == 0)
			ymod = -CONTAINER_YMOD;
		else if (i == 2)
			ymod = CONTAINER_YMOD;
		containers[i].setPosition(Vector2f(location.x * (i + 1) / 4 + ymod, location.y));
		bounds = containers[i].getLocalBounds();
		containers[i].setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
	}
}