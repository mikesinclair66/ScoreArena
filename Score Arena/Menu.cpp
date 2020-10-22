#include "menu.h"
#include <iostream>

using namespace std;

Menu::Menu(int width, int height) {
	this->width = width;
	this->height = height;

	//load images
	if (!bg.loadFromFile("res\\menuBg.jpg"))
		throw runtime_error("Background image couldn\'t be loaded.");

	if (!title.loadFromFile("res\\menuTitle.png"))
		throw runtime_error("Title image couldn\'t be loaded.");

	//load cursor
	if (!cursorImg.loadFromFile("res\\cursor.png"))
		throw runtime_error("Cursor image couldn\'t be loaded.");
	if (!cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), Vector2u(0, 0)))
		throw runtime_error("Cursor couldn\'t be loaded from image.");

	//load option format and then create options
	if (!font.loadFromFile("res\\Sinclairscript-Regular.ttf")) {
		if (!font.loadFromFile("res\\Sinclairscript-Regular.otf"))
			throw runtime_error("Could not load Sinclair_Script font.");
	}
	text.setFont(font);
	text.setCharacterSize(Selector::CHAR_SIZE);
	text.setStyle(Text::Bold);
	//page 0
	selector.sets[0].push_back("SINGLE PLAYER", Vector2f(width / 2, height / SEGMENTS * 3));
	selector.sets[0].push_back("MULTI PLAYER", Vector2f(width / 2, height / SEGMENTS * 4));
	selector.sets[0].push_back("OPTIONS", Vector2f(width / 2, height / SEGMENTS * 5));
	selector.sets[0].push_back("EXIT", Vector2f(width / 2, height / SEGMENTS * 6));
}

void Menu::draw(RenderWindow& window) {
	if (isActive()) {
		//draw bg
		sprite.setTexture(bg);
		Vector2u bgSize = bg.getSize();
		for (int i = 0; i < height; i += bgSize.y) {
			for (int j = 0; j < width; j += bgSize.x) {
				sprite.setPosition(Vector2f(j, i));
				window.draw(sprite);
			}
		}

		//draw title on first page
		if (page == 0) {
			sprite.setTexture(title);
			sprite.setPosition(Vector2f(width / 2 - title.getSize().x / 2, height / SEGMENTS * 1));
			window.draw(sprite);
		}

		//draw options
		selector.sets[page].draw(window, text);
	}
}

void Menu::setActive(bool active, RenderWindow& window) {
	if (active) {
		window.setMouseCursor(cursor);
	}
	else {
		//make cursor invisible
	}

	this->active = active;
}

/// <summary>
/// Activates the selected option. Since each option for
/// every page does different actions, each action should
/// be specified here.
/// </summary>
void Menu::activateSelected() {
	if (page == 0) {
		switch (selector.sets[page].getSelected()) {
		case 1:
			page = 1;
			//add commands for single player page
			break;
		case 2:
			page = 1;
			//add commands for multi player page
			break;
		case 3:
			page = 3;//page 3 as page 2 is for selecting the map
			break;
		case 4:
			setExitQueue(true);
			break;
		}
	}
}

void Menu::keyPressed() {
	if (isActive()) {
		bool up = false, down = false;

		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			selector.sets[page].select(selector.sets[page].getSelected() - 1);
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			selector.sets[page].select(selector.sets[page].getSelected() + 1);

		//if selected var goes out of bound, return to opposite end
		if (selector.sets[page].getSelected() < 1)
			selector.sets[page].select(selector.sets[page].getOptionsLength());
		else if (selector.sets[page].getSelected() > selector.sets[page].getOptionsLength())
			selector.sets[page].select(1);
	}
}

void Menu::keyReleased(Event k) {
	if (isActive()) {
		if (k.key.code == Keyboard::Enter)
			activateSelected();
	}
}

void Menu::mouseMoved() {
	Vector2i pos = Mouse::getPosition();

	for (int i = 0; i < selector.sets[page].getOptionsLength(); i++) {
		String label = selector.sets[page].getLabel(i);
		Vector2f location = selector.sets[page].getLocation(i);

		//TODO check if mouse is in bounds
	}
}