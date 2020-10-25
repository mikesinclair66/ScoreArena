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
	text.setCharacterSize(CHAR_SIZE);
	text.setStyle(Text::Bold);

	//page 0
	selector.sets[0].push_back("SINGLE PLAYER", Vector2f(width / 2, height * 3 / SEGMENTS));
	selector.sets[0].push_back("MULTI PLAYER", Vector2f(width / 2, height * 4 / SEGMENTS));
	selector.sets[0].push_back("OPTIONS", Vector2f(width / 2, height * 5 / SEGMENTS));
	selector.sets[0].push_back("EXIT", Vector2f(width / 2, height * 6 / SEGMENTS));

	//page 1
	selector.sets[1].push_back("BACK", Vector2f(width / 8, height / SEGMENTS));
	selector.sets[1].push_back("START!", Vector2f(width / 2, height * 6 / SEGMENTS));
	powerSelect.setSlotMax(6);
	bool powersLoaded = true;
	if (!powerTextures[0].loadFromFile("res\\attack.png"))
		powersLoaded = false;
	if (!powerTextures[1].loadFromFile("res\\absorb.png"))
		powersLoaded = false;
	if (!powerTextures[2].loadFromFile("res\\fire.png"))
		powersLoaded = false;
	if (!powerTextures[3].loadFromFile("res\\frozen.png"))
		powersLoaded = false;
	if (!powerTextures[4].loadFromFile("res\\invincibility.png"))
		powersLoaded = false;
	if (!powerTextures[5].loadFromFile("res\\lightning.png"))
		powersLoaded = false;

	if (!powersLoaded)
		throw runtime_error("Couldn\'t load power textures.");
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
		switch (page) {
		case 0:
			sprite.setTexture(title);
			sprite.setPosition(Vector2f(width / 2 - title.getSize().x / 2, height / SEGMENTS * 1));
			window.draw(sprite);
			break;
		case 1:
			colorSelect[0].draw(window);
			colorSelect[1].draw(window);
			powerSelect.draw(window);
			arsenals[0].draw(window);
			if(!singlePlayer)
				arsenals[1].draw(window);
			
			//draw selectable powers
			sprite.setTexture(powerTextures[powerSelect.slot]);
			Vector2f startPos = powerSelect.getPosition();
			sprite.setPosition(Vector2f(startPos.x - 85, startPos.y - 85));
			/*
			FloatRect spriteRect = sprite.getLocalBounds();
			sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
				spriteRect.top + spriteRect.height / 2.0f);
			*/
			window.draw(sprite);

			//powers in arsenal slots
			for (int i = 0; i < 3; i++) {
				int slot = arsenals[0].containers[i].slot;
				if (slot > 0) {
					Vector2f cPos = arsenals[0].containers[i].getPosition();
					sprite.setTexture(powerTextures[slot - 1]);
					sprite.setPosition(Vector2f(cPos.x - 85, cPos.y - 85));
					window.draw(sprite);
				}
			}
			if (!singlePlayer) {
				for (int i = 0; i < 3; i++) {
					int slot = arsenals[1].containers[i].slot;
					if (slot > 0) {
						Vector2f cPos = arsenals[1].containers[i].getPosition();
						sprite.setTexture(powerTextures[slot - 1]);
						sprite.setPosition(Vector2f(cPos.x - 85, cPos.y - 85));
						window.draw(sprite);
					}
				}
			}
			break;
		}

		//draw options
		selector.sets[page].draw(window, text);
		selector.draw(window, page, text);
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
			clear(page);
			page = 1;
			//add commands for single player page
			singlePlayer = true;
			colorSelect[0].setPosition(Vector2f(width / 6, height / 3), SPACE_CSELECT);
			colorSelect[1].setPosition(Vector2f(width / 6, height * 2 / 3), SPACE_CSELECT);
			powerSelect.setPosition(Vector2f(width / 2, height / 2), SPACE_PSELECT);
			arsenals[0].setLocation(Vector2f(width * 5 / 6, height));
			break;
		case 2:
			clear(page);
			page = 1;
			//add commands for multi player page
			singlePlayer = false;
			colorSelect[0].setPosition(Vector2f(width / 6, height / 3), SPACE_CSELECT);
			colorSelect[1].setPosition(Vector2f(width / 6, height * 2 / 3), SPACE_CSELECT);
			powerSelect.setPosition(Vector2f(width / 2, height / 2), SPACE_PSELECT);
			arsenals[0].setLocation(Vector2f(width * 3 / 4, height));
			arsenals[1].setLocation(Vector2f(width * 11 / 12, height));
			break;
		case 3:
			clear(page);
			page = 3;//page 3 as page 2 is for selecting the map
			break;
		case 4:
			setExitQueue(true);
			break;
		}
	}
	else if (page == 1) {
		switch (selector.sets[page].getSelected()) {
		case 1:
			clear(page);
			page = 0;
			break;
		}
	}
}

void Menu::clear(int page) {
	selector.sets[page].select(0);

	if (page == 1) {
		colorSelect[0].select(0);
		colorSelect[0].slot = 0;
		colorSelect[1].select(0);
		colorSelect[1].slot = 0;
		powerSelect.select(0);
		powerSelect.slot = 0;
	}
}

void Menu::keyPressed() {
	if (isActive()) {
		bool up = false, down = false;
		int nSelected = selector.sets[page].getSelected();

		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			nSelected--;
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			nSelected++;

		//if selected var goes out of bound, return to opposite end
		if (nSelected < 1)
			nSelected = selector.sets[page].getOptionsLength();
		else if (nSelected > selector.sets[page].getOptionsLength())
			nSelected = 1;

		select(nSelected);
	}
}

void Menu::keyReleased(Event k) {
	if (isActive()) {
		if (k.key.code == Keyboard::Enter)
			activateSelected();
	}
}

void Menu::mouseMoved() {
	if (isActive()) {
		Vector2i pos = Mouse::getPosition();
		int selected = 0;

		//check if an option is selected
		for (int i = 0; i < selector.sets[page].getOptionsLength(); i++) {
			String label = selector.sets[page].getLabel(i);
			Vector2f location = selector.sets[page].getLocation(i);

			if (pos.x >= location.x - (float)(label.getSize() * text.getCharacterSize()) / 2
				&& pos.x <= location.x + (float)(label.getSize() * text.getCharacterSize()) / 2
				&& pos.y >= location.y - text.getCharacterSize() / 2
				&& pos.y <= location.y + text.getCharacterSize() / 2) {
				selected = i + 1;
				break;
			}
		}

		select(selected);

		//check if a chooser is selected
		if (page == 1) {
			colorSelect[0].requestSelect(pos);
			colorSelect[1].requestSelect(pos);
			powerSelect.requestSelect(pos);
		}
	}
}

void Menu::mouseReleased() {
	if (isActive()) {
		activateSelected();
		
		if (page == 1) {
			colorSelect[0].activateSelected();
			colorSelect[1].activateSelected();
			powerSelect.activateSelected();
			arsenals[0].mouseReleased(powerSelect.slot);
			if (!singlePlayer)
				arsenals[1].mouseReleased(powerSelect.slot);
		}
	}
}

void Menu::select(int selected) {
	if (selected != selector.sets[page].getSelected()) {
		selector.sets[page].select(selected);
		selector.select(selected, page);
	}
}