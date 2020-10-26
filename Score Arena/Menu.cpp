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
	colorSelect[0].setSlotMax(7);
	colorSelect[1].setSlotMax(7);
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

	pSkins[0].setRadius(SPACE_CSELECT / 2 - 20);
	pSkins[1].setRadius(SPACE_CSELECT / 2 - 20);
	pSkins[0].setOutlineThickness(5);
	pSkins[1].setOutlineThickness(5);
	FloatRect o1 = pSkins[0].getLocalBounds(), o2 = pSkins[1].getLocalBounds();
	pSkins[0].setOrigin(o1.left + o1.width / 2.0f, o1.top + o1.height / 2.0f);
	pSkins[1].setOrigin(o2.left + o2.width / 2.0f, o2.top + o2.height / 2.0f);

	msg.setPosition(Vector2f(width / 2, height / 12));
	msg.setMsg("You must select a power for each power slot before beginning.");
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
			
			drawStats(window, text, powerSelect.getPosition(), powerSelect.slot);

			//draw arsenals along with power prices
			arsenals[0].draw(window);
			for (int i = 0; i < 3; i++) {
				int slot = arsenals[0].containers[i].slot;
				if (slot > 0)
					drawStats(window, text, arsenals[0].containers[i].getPosition(), slot - 1);
			}
			if(!singlePlayer){
				arsenals[1].draw(window);
				for (int i = 0; i < 3; i++) {
					int slot = arsenals[1].containers[i].slot;
					if (slot > 0)
						drawStats(window, text, arsenals[1].containers[i].getPosition(), slot - 1);
				}
			}

			//draw player skins
			pSkins[0].setFillColor(getSkinColor(colorSelect[0].slot));
			pSkins[0].setOutlineColor(getSkinOutlineColor(colorSelect[0].slot));
			pSkins[1].setFillColor(getSkinColor(colorSelect[1].slot));
			pSkins[1].setOutlineColor(getSkinOutlineColor(colorSelect[1].slot));
			window.draw(pSkins[0]);
			window.draw(pSkins[1]);
			
			//draw selectable powers
			Vector2f startPos = powerSelect.getPosition();
			sprite.setTexture(powerTextures[powerSelect.slot]);
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

			msg.draw(window, text);
			break;
		}

		//draw options
		selector.sets[page].draw(window, text);
		selector.draw(window, page, text);
	}
}

void Menu::drawStats(RenderWindow& window, Text text, Vector2f startPos, int slot) {
	//draw price and damage of powers
	text.setFillColor(Color::Green);
	text.setString("$" + to_string(powerPrices[slot]));
	FloatRect rect = text.getLocalBounds();
	text.setOrigin(Vector2f(rect.left + rect.width / 2.0f, text.getOrigin().y));
	if (slot < 3) {
		text.setPosition(Vector2f(startPos.x - 60, startPos.y + 120));
		window.draw(text);

		//draw power damage
		text.setFillColor(Color::Red);
		text.setString(to_string(powerDmg[slot]) + "X");
		text.setPosition(Vector2f(startPos.x + 60, startPos.y + 120));
		window.draw(text);
	}
	else {
		text.setPosition(Vector2f(startPos.x, startPos.y + 120));
		window.draw(text);
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
			pSkins[0].setPosition(colorSelect[0].getPosition());
			colorSelect[1].setPosition(Vector2f(width / 6, height * 2 / 3), SPACE_CSELECT);
			pSkins[1].setPosition(colorSelect[1].getPosition());
			powerSelect.setPosition(Vector2f(width / 2, height / 2), SPACE_PSELECT);
			arsenals[0].setLocation(Vector2f(width * 5 / 6, height));
			break;
		case 2:
			clear(page);
			page = 1;
			//add commands for multi player page
			singlePlayer = false;
			colorSelect[0].setPosition(Vector2f(width / 6, height / 3), SPACE_CSELECT);
			pSkins[0].setPosition(colorSelect[0].getPosition());
			colorSelect[1].setPosition(Vector2f(width / 6, height * 2 / 3), SPACE_CSELECT);
			pSkins[1].setPosition(colorSelect[1].getPosition());
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
		case 2:
			if (checkPowersFilled()) {
				msg.deactivate();
				page = 2;
			}
			else
				msg.activate();
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
		arsenals[0].clear();
		arsenals[1].clear();
		msg.deactivate();
	}
}

bool Menu::checkPowersFilled() {
	if (singlePlayer) {
		for (int i = 0; i < 3; i++) {
			if (arsenals[0].containers[i].slot == 0)
				return false;
		}
		return true;
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (arsenals[0].containers[i].slot == 0 || arsenals[1].containers[i].slot == 0)
				return false;
		}
		return true;
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

Color Menu::getSkinColor(int slot) {
	Color c;

	switch (slot) {
	case 0:
		c = Color(0, 255, 68);//green
		break;
	case 1:
		c = Color(255, 251, 0);//yellow
		break;
	case 2:
		c = Color::Red;//red
		break;
	case 3:
		c = Color(0, 255, 255);//cyan
		break;
	case 4:
		c = Color::Blue;//blue
		break;
	case 5:
		c = Color(208, 0, 255);//magenta
		break;
	case 6:
		c = Color(255, 0, 166);//pink
		break;
	}

	return c;
}

Color Menu::getSkinOutlineColor(int slot) {
	Color c;

	switch (slot) {
	case 0:
		c = Color(0, 140, 37);
		break;
	case 1:
		c = Color(138, 135, 0);
		break;
	case 2:
		c = Color(138, 0, 0);
		break;
	case 3:
		c = Color(0, 128, 128);
		break;
	case 4:
		c = Color(0, 22, 145);
		break;
	case 5:
		c = Color(115, 0, 140);
		break;
	case 6:
		c = Color(135, 0, 88);
		break;
	}

	return c;
}