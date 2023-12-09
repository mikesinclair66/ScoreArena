#include "arsenal.h"

using namespace MenuItems;

Arsenal::Arsenal() {
	for (int i = 0; i < 3; i++) {
		containers[i].setSize(Vector2f(200, 200));
		containers[i].setFillColor(Color::Transparent);
		containers[i].setOutlineColor(Color::Black);
		containers[i].setOutlineThickness(CONTAINER_OUTLINE);
	}
}

void Arsenal::draw(RenderWindow& window) {
	for (int i = 0; i < 3; i++)
		window.draw(containers[i]);
}

/// <summary>
/// Sets up the location of the arsenal using a vector
/// containing the x position and height of the screen.
/// </summary>
/// <param name="location"></param>
void Arsenal::setLocation(Vector2f location) {
	for (int i = 0; i < 3; i++) {
		int ymod = 0;
		if (i == 0)
			ymod = -CONTAINER_YMOD;
		else if (i == 2)
			ymod = CONTAINER_YMOD;
		containers[i].setPosition(Vector2f(location.x, location.y * (i + 1) / 4 + ymod));
		FloatRect bounds = containers[i].getLocalBounds();
		containers[i].setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
	}
}

void Arsenal::clear() {
	for (int i = 0; i < 3; i++)
		containers[i].slot = 0;
}

void Arsenal::mouseReleased(int slot) {
	Vector2i pos = Mouse::getPosition();

	for (int i = 0; i < 3; i++) {
		Vector2f location = containers[i].getPosition();
		Vector2f size = containers[i].getSize();

		if (pos.x >= location.x - size.x / 2 && pos.x <= location.x + size.x / 2
			&& pos.y >= location.y - size.y / 2 && pos.y <= location.y + size.y / 2)
			containers[i].slot = slot + 1;
	}
}