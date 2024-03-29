#include "menu.h"
#include <iostream>

using namespace std;
using namespace MenuItems;

//int Menu::powerPrices[] = { 20, 30, 40, 40, 40, 40 };
//int Menu::powerDmg[] = { 30, 20, 40 };
//Texture Menu::powerTextures[] = { Texture(), Texture(), Texture(), Texture(), Texture(), Texture() };

Menu* Menu::instance = nullptr;

Menu* Menu::getInstance(int width, int height) {
	if (instance == nullptr)
		instance = new Menu(width, height);

	return instance;
}

Menu::Menu(int width, int height) {
	this->width = width;
	this->height = height;

	//load images
	if (!bg.loadFromFile("..\\res\\menuBg.jpg"))
		throw runtime_error("Background image couldn\'t be loaded.");

	if (!title.loadFromFile("..\\res\\menuTitle.png"))
		throw runtime_error("Title image couldn\'t be loaded.");

	//load cursor
	if (!cursorImg.loadFromFile("..\\res\\cursor.png"))
		throw runtime_error("Cursor image couldn\'t be loaded.");
	if (!cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), Vector2u(0, 0)))
		throw runtime_error("Cursor couldn\'t be loaded from image.");

	//load option format and then create options
	if (!font.loadFromFile("..\\res\\Sinclairscript-Regular.ttf")) {
		if (!font.loadFromFile("..\\res\\Sinclairscript-Regular.otf"))
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
	selector.sets[1].push_back("BACK", Vector2f(width / 12, height / 12));
	selector.sets[1].push_back("START!", Vector2f(width / 2, height * 6 / SEGMENTS));
	colorSelect[0].setSlotMax(7);
	colorSelect[1].setSlotMax(7);
	powerSelect.setSlotMax(6);
	bool powersLoaded = true;
	if (!powerTextures[0].loadFromFile("..\\res\\attack.png"))
		powersLoaded = false;
	if (!powerTextures[1].loadFromFile("..\\res\\absorb.png"))
		powersLoaded = false;
	if (!powerTextures[2].loadFromFile("..\\res\\fire.png"))
		powersLoaded = false;
	if (!powerTextures[3].loadFromFile("..\\res\\frozen.png"))
		powersLoaded = false;
	if (!powerTextures[4].loadFromFile("..\\res\\invincibility.png"))
		powersLoaded = false;
	if (!powerTextures[5].loadFromFile("..\\res\\lightning.png"))
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
	colorSelect[1].slot = 1;

	msg.setPosition(Vector2f(width / 2, height / 12));
	msg.setMsg("You must select a power for each power slot before beginning.");

	//page 2
	selector.sets[2].push_back("BACK", Vector2f(width / 12, height / 12));

	FloatRect bounds;
	maps[0].loadImage("..\\res\\map1Bg.jpg");
	maps[0].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[0].setPosition(Vector2f(width / 5, height * 1.5f / 5));
	bounds = maps[0].getLocalBounds();
	maps[0].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);

	maps[1].loadImage("..\\res\\lava.jpg");
	maps[1].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[1].setPosition(Vector2f(width * 2.5f / 5, height * 1.5f / 5));
	bounds = maps[1].getLocalBounds();
	maps[1].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);

	maps[2].loadImage("..\\res\\bg3.jpg");
	maps[2].loadImage("..\\res\\bg3.jpg");
	maps[2].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[2].setPosition(Vector2f(width * 4 / 5, height * 1.5f / 5));
	bounds = maps[2].getLocalBounds();
	maps[2].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);

	maps[3].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[3].setPosition(Vector2f(width / 5, height * 3.5f / 5));
	bounds = maps[3].getLocalBounds();
	maps[3].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	maps[3].setDisabled(true);

	maps[4].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[4].setPosition(Vector2f(width * 2.5f / 5, height * 3.5f / 5));
	bounds = maps[4].getLocalBounds();
	maps[4].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	maps[4].setDisabled(true);

	maps[5].setSize(Vector2f(width / 5, height * 1.5f / 5));
	maps[5].setPosition(Vector2f(width * 4 / 5, height * 3.5f / 5));
	bounds = maps[5].getLocalBounds();
	maps[5].setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	maps[5].setDisabled(true);

	//page 3
	selector.sets[3].push_back("CANCEL", Vector2f(width * 2 / 5, height * 5 / 6));
	selector.sets[3].push_back("APPLY", Vector2f(width * 3 / 5, height * 5 / 6));

	bindingSets[0].setBindings(bindings1);
	bindingSets[1].setBindings(bindings2);
	bindingSets[0].setLocation(Vector2f(width * 3 / 10, height * 1 / 4),
		Vector2f(width * 3 / 10, height * 5 / 6));
	bindingSets[1].setLocation(Vector2f(width * 7 / 10, height * 1 / 4),
		Vector2f(width * 7 / 10, height * 5 / 6));
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

				//draw key bindings by containers
				Vector2f containerPos = arsenals[0].containers[i].getPosition();
				text.setString(getBindingString(bindings1[i + 1]));
				text.setFillColor(Color::Yellow);
				text.setPosition(Vector2f(containerPos.x - 155 - text.getCharacterSize() / 2,
					containerPos.y - text.getCharacterSize() / 2));
				window.draw(text);
			}
			if (!singlePlayer) {
				arsenals[1].draw(window);
				for (int i = 0; i < 3; i++) {
					int slot = arsenals[1].containers[i].slot;
					if (slot > 0)
						drawStats(window, text, arsenals[1].containers[i].getPosition(), slot - 1);

					//draw key bindings by containers
					Vector2f containerPos = arsenals[1].containers[i].getPosition();
					text.setString(getBindingString(bindings2[i + 1]));
					text.setFillColor(Color::Yellow);
					text.setPosition(Vector2f(containerPos.x - 155 - text.getCharacterSize() / 2,
						containerPos.y - text.getCharacterSize() / 2));
					window.draw(text);
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
			sprite.setTexture(powerTextures[powerSelect.slot]);
			sprite.setPosition(Vector2f(powerSelect.getPosition().x - 85,
				powerSelect.getPosition().y - 85));
			window.draw(sprite);

			//draw player colors in absorb icon
			if (powerSelect.slot == 1) {
				RectangleShape pColor;
				pColor.setFillColor(getPlayerColor(0));
				pColor.setPosition(Vector2f(powerSelect.getPosition().x + 42,
					powerSelect.getPosition().y - 70));
				pColor.setSize(Vector2f(37, 37));
				window.draw(pColor);

				pColor.setFillColor(getPlayerColor(1));
				pColor.setPosition(Vector2f(powerSelect.getPosition().x - 72,
					powerSelect.getPosition().y + 5));
				pColor.setSize(Vector2f(67, 66));
				window.draw(pColor);
			}

			//powers in arsenal slots
			for (int i = 0; i < 3; i++) {
				int slot = arsenals[0].containers[i].slot;
				if (slot > 0) {
					Vector2f cPos = arsenals[0].containers[i].getPosition();
					sprite.setTexture(powerTextures[slot - 1]);
					sprite.setPosition(Vector2f(cPos.x - 85, cPos.y - 85));
					window.draw(sprite);

					//draw player colors in absorb icon
					if (slot == 2) {
						RectangleShape pColor;
						pColor.setFillColor(getPlayerColor(1));
						pColor.setPosition(Vector2f(cPos.x + 42, cPos.y - 70));
						pColor.setSize(Vector2f(37, 37));
						window.draw(pColor);

						pColor.setFillColor(getPlayerColor(0));
						pColor.setPosition(Vector2f(cPos.x - 72, cPos.y + 5));
						pColor.setSize(Vector2f(67, 66));
						window.draw(pColor);
					}
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

						//draw player colors in absorb icon
						if (slot == 2) {
							RectangleShape pColor;
							pColor.setFillColor(getPlayerColor(0));
							pColor.setPosition(Vector2f(cPos.x + 42, cPos.y - 70));
							pColor.setSize(Vector2f(37, 37));
							window.draw(pColor);

							pColor.setFillColor(getPlayerColor(1));
							pColor.setPosition(Vector2f(cPos.x - 72, cPos.y + 5));
							pColor.setSize(Vector2f(67, 66));
							window.draw(pColor);
						}
					}
				}
			}

			msg.draw(window, text);
			break;
		case 2:
			for (int i = 0; i < 6; i++)
				maps[i].draw(window, text);
			break;
		case 3:
			FloatRect rect;
			text.setPosition(Vector2f(width * 3 / 10, height / 6));
			text.setString("Player 1");
			rect = text.getLocalBounds();
			text.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
			window.draw(text);
			bindingSets[0].draw(window, text);

			text.setPosition(Vector2f(width * 7 / 10, height / 6));
			text.setString("Player 2");
			rect = text.getLocalBounds();
			text.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
			window.draw(text);
			bindingSets[1].draw(window, text);

			rect = text.getLocalBounds();
			text.setOrigin(rect.left, rect.top);
		}

		//draw options
		selector.sets[page].draw(window, text);
		selector.draw(window, page, text);
	}
}

/// <summary>
/// Draws the price and damage of a selected power
/// under the specified slot.
/// </summary>
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
	else if (page == 2) {
		switch (selector.sets[page].getSelected()) {
		case 1:
			clear(page);
			page = 1;
			break;
		}
	}
	else if (page == 3) {
		switch (selector.sets[page].getSelected()) {
		case 1:
			//cancel changes
			bindingSets[0].clear();
			bindingSets[0].setBindings(bindings1);
			bindingSets[1].clear();
			bindingSets[1].setBindings(bindings2);
			clear(page);
			page = 0;
			break;
		case 2:
			//apply changes
			for (int i = 0; i < 8; i++) {
				bindings1[i] = bindingSets[0].bindings[i];
				bindings2[i] = bindingSets[1].bindings[i];
			}
			bindingSets[0].clear();
			bindingSets[1].clear();
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
		colorSelect[1].slot = 1;
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
		else
			return;

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

		if (page == 3) {
			bindingSets[0].keyReleased(k.key.code);
			bindingSets[1].keyReleased(k.key.code);
		}
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
		//check if a map is selected
		if (page == 2) {
			for (int i = 0; i < 6; i++) {
				if (maps[i].requestSelect(pos)) {
					selectedMap = i + 1;
					break;
				}

				//if the loop goes through on move with no map selected, restore selectedMap
				if (i == 5)
					selectedMap = 0;
			}
		}
		if (page == 3) {
			bindingSets[0].mouseMoved(pos);
			bindingSets[1].mouseMoved(pos);
		}
	}
}

void Menu::mouseReleased() {
	if (isActive()) {
		activateSelected();

		if (page == 1) {
			colorSelect[0].activateSelected();
			//if first color selector matches the second, skip to next color
			if (colorSelect[0].slot == colorSelect[1].slot)
				colorSelect[0].activateSelected();
			colorSelect[1].activateSelected();
			if (colorSelect[1].slot == colorSelect[0].slot)
				colorSelect[1].activateSelected();
			powerSelect.activateSelected();
			arsenals[0].mouseReleased(powerSelect.slot);
			if (!singlePlayer)
				arsenals[1].mouseReleased(powerSelect.slot);
		}
		else if (page == 2) {
			if (selectedMap > 0) {
				//close menu and go to game
				setActive(false);
				setStartGameQueue(true);
			}
		}
		else if (page == 3) {
			if (bindingSets[1].getSelected() == 0)
				bindingSets[0].mouseReleased();
			if (bindingSets[0].getSelected() == 0)
				bindingSets[1].mouseReleased();
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

BindingSet::BindingSet() {
	for (int i = 0; i < BINDING_NO; i++)
		changed[i] = false;
}

void BindingSet::setBindings(Keyboard::Key bindings[8]) {
	for (int i = 0; i < 8; i++) {
		this->bindings[i] = bindings[i];
		labels[i] = Menu::getBindingString(bindings[i]);
	}
}

void BindingSet::setLocation(Vector2f start, Vector2f end) {
	int distanceX = end.x - start.x, distanceY = end.y - start.y;

	for (int i = 0; i < BINDING_NO; i++) {
		locations[i] = Vector2f(start.x + i * distanceX / BINDING_NO,
			start.y + i * distanceY / BINDING_NO);
	}
}

void BindingSet::draw(RenderWindow& window, Text t) {
	for (int i = 0; i < BINDING_NO; i++) {
		t.setPosition(locations[i]);
		t.setString((selected - 1 != i) ? labels[i] : "???");
		if (i == hovered - 1 || i == selected - 1)
			t.setFillColor(Color::Yellow);
		else if (changed[i])
			t.setFillColor(Color::Red);
		else
			t.setFillColor(Color::Green);
		FloatRect rect = t.getLocalBounds();
		t.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		window.draw(t);
	}
}

void BindingSet::mouseReleased() {
	selected = hovered;
}

void BindingSet::mouseMoved(Vector2i pos) {
	hovered = 0;
	for (int i = 0; i < BINDING_NO; i++) {
		int length = labels[i].length();
		if (pos.x >= locations[i].x - length * 50 && pos.x <= locations[i].x + length * 50
			&& pos.y >= locations[i].y - 25 && pos.y <= locations[i].y + 25)
			hovered = i + 1;
	}
}

void BindingSet::keyReleased(Keyboard::Key key) {
	bool valid = true;
	for (int i = 0; i < BINDING_NO; i++) {
		if (bindings[i] == key)
			valid = false;
	}

	if (selected > 0 && valid) {
		bindings[selected - 1] = key;
		labels[selected - 1] = Menu::getBindingString(key);
		changed[selected - 1] = true;
		selected = 0;
	}
}

void BindingSet::clear() {
	selected = 0;
	for (int i = 0; i < BINDING_NO; i++)
		changed[i] = false;
}