#include "attackArsenal.h"
#include "menu.h"

using namespace Game;

AttackArsenal::AttackArsenal() : Arsenal() {
	background.setSize(Vector2f(700, 300));
	background.setFillColor(Color(255, 255, 255, 127));
	background.setOutlineColor(Color::Black);
	background.setOutlineThickness(5);
}

void AttackArsenal::draw(RenderWindow& window, Sprite sprite, Text t) {
	window.draw(background);
	Arsenal::draw(window);
	for (int i = 0; i < 3; i++) {
		if (containers[i].slot > 0) {
			//powers in arsenal slots
			Vector2f cPos = containers[i].getPosition();
			sprite.setTexture(MenuItems::Menu::getInstance(0, 0)->getPowerTextures()[containers[i].slot - 1]);
			sprite.setPosition(Vector2f(cPos.x - 85, cPos.y - 85));
			window.draw(sprite);
			MenuItems::Menu::getInstance(0, 0)->drawStats(window, t,
				containers[i].getPosition(), containers[i].slot - 1);
		}
	}
}

void AttackArsenal::setLocation(Vector2f location) {
	background.setPosition(Vector2f(location.x, location.y - 50));
	FloatRect bounds = background.getLocalBounds();
	background.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);

	//since the attack arsenal is horizontal , it used ymod horizontally
	for (int i = 0; i < 3; i++) {
		int ymod = 0;
		if (i == 0)
			ymod = -CONTAINER_YMOD;
		else if (i == 1)
			ymod = 0;
		else
			ymod = CONTAINER_YMOD;
		containers[i].setPosition(Vector2f(location.x + ymod * 5, location.y - 80));
		bounds = containers[i].getLocalBounds();
		containers[i].setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
	}
}