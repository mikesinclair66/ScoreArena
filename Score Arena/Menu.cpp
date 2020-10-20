#include "menu.h"
#include <iostream>

using namespace std;

Menu::Menu(int width, int height) {
	this->width = width;
	this->height = height;

	//load background image
	if (!bg.loadFromFile("res\\menuBg.jpg"))
		throw runtime_error("Failed to load background image.");

	//load title image
	if (!title.loadFromFile("res\\menuTitle.png"))
		throw runtime_error("Failed to load title image.");

	//load cursor
	if (!cursorImg.loadFromFile("res\\cursor.png"))
		throw runtime_error("Failed to load cursor image.");

	//load font
	if (!font.loadFromFile("res\\Sinclairscript-Regular.ttf")) {
		//load other font it ttf isn't supported
		if (!font.loadFromFile("res\\Sinclairscript-Regular.otf"))
			throw runtime_error("Failed to load font.");
	}
	text.setFont(font);
	text.setCharacterSize(45);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	selector.setFillColor(Color::Magenta);
}

void Menu::draw(RenderWindow &window) {
	if (!isActive())
		return;

	//fill background with bg image
	sprite.setTexture(bg);
	Vector2u dims = bg.getSize();
	for (int i = 0; i < height; i += dims.y) {
		for (int j = 0; j < width; j += dims.x) {
			sprite.setPosition(Vector2f(j, i));
			window.draw(sprite);
		}
	}

	//draw the specified page
	switch (page) {
		case 0:
			sprite.setTexture(title);
			sprite.setPosition(Vector2f(width / 2 - title.getSize().x / 2,
				(float)(1 / SEGMENTS * height)));
			window.draw(sprite);

			//display the options
			for (int i = 0; i < sizeof(labels) / sizeof(labels[0]); i++) {
				if (selected == i + 1)
					text.setFillColor(Color::Yellow);
				else
					text.setFillColor(Color::White);
				text.setString(labels[i]);
				text.setPosition(Vector2f(width / 2 - text.getCharacterSize() * labels[i].length()
					/ 4, (float)((i + 3) / SEGMENTS * height)));
				window.draw(text);
			}

			if (selected > 0) {
				float mod = clock.getElapsedTime().asMilliseconds() * SELECT_MOD;
				float labelSize = (float)(labels[selected - 1].length() * text.getCharacterSize())
					* 0.6f;
				if (mod > labelSize)
					mod = labelSize;

				selector.setSize(Vector2f(mod, SELECT_MOD * 8));
				selector.setPosition(Vector2f(width / 2 - (float) mod * 0.475f,
					selector.getPosition().y));
				window.draw(selector);
			}

			break;
	}
}

void Menu::setActive(bool val, RenderWindow &window) {
	active = val;

	//change cursor
	if (val) {
		Vector2u cSize = cursorImg.getSize();
		Cursor cursor;
		if(cursor.loadFromPixels(cursorImg.getPixelsPtr(), cSize, Vector2u(0, 0)))
			window.setMouseCursor(cursor);
	}
	else {
		//TODO make cursor invisible
	}
}

void Menu::mouseMoved() {
	if (!isActive())
		return;

	Vector2i coords = Mouse::getPosition();
	int selected = 0;
	for (int i = 0; i < sizeof(labels) / sizeof(labels[0]); i++) {
		//if the cursor is in between the width and height of the option
		if (coords.x >= width / 2 - text.getCharacterSize() * labels[i].length() / 4 && coords.x <=
			width / 2 + text.getCharacterSize() * labels[i].length() / 4 &&
			coords.y >= (float)((i + 3) / SEGMENTS * height) + 10 && coords.y <=
			(float)((i + 3) / SEGMENTS * height) + text.getCharacterSize() + 10)
			selected = i + 1;
	}

	if (selected > 0) {
		if (this->selected != selected) {
			//TODO PUT IN SELECTOR FUNCTION
			clock.restart();
			selector.setSize(Vector2f(SELECT_MOD, SELECT_MOD * 8));
			selector.setPosition(Vector2f(width / 2 - SELECT_MOD / 2,
				(float)((selected + 2) / SEGMENTS * height) + text.getCharacterSize()
				+ SELECT_MOD * 7));
		}

		this->selected = selected;
	}
	else if (selected == 0 && this->selected != 0)
		this->selected = 0;
}

void Menu::mousePressed() {
	if (!isActive())
		return;
}

void Menu::mouseReleased() {
	if (!isActive())
		return;

	activateSelected();
}

void Menu::keyPressed() {
	if (!isActive())
		return;

	bool up = false, down = false, w = false, d = false;
	if (Keyboard::isKeyPressed(Keyboard::Up))
		up = true;
	if (Keyboard::isKeyPressed(Keyboard::Down))
		down = true;
	if (Keyboard::isKeyPressed(Keyboard::W))
		up = true;
	if (Keyboard::isKeyPressed(Keyboard::D))
		down = true;

	bool enter = false;
	if (Keyboard::isKeyPressed(Keyboard::Enter))
		enter = true;

	if (up || down || w || d) {
		switch (selected) {
		case 0:
			selected = 1;
			break;
		case 1:

			break;
		}
	}
}

void Menu::activateSelected() {
	if (selected == 1 || selected == 2)
		page = 1;
	else if (selected == 3)
		page = 2;
	else if (selected == 4)
		queueExit = true;

	selected = 0;
}