#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Menu::Menu(int width, int height) {
	this->width = width;
	this->height = height;

	//load background image
	if (!bg.loadFromFile("images\\menuBg.jpg"))
		throw runtime_error("Failed to load background image.");

	//load title image
	if (!title.loadFromFile("images\\menuTitle.png"))
		throw runtime_error("Failed to load title image.");

	//load cursor
	if (!cursorImg.loadFromFile("images\\cursor.png"))
		throw runtime_error("Failed to load cursor image.");
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
			int segments = sizeof(labels) / sizeof(labels[0]) + 4;

			sprite.setTexture(title);
			sprite.setPosition(Vector2f(width / 2 - title.getSize().x / 2,
				(1 / segments) * height));
			window.draw(sprite);


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