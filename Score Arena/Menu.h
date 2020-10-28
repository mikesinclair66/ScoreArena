#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "arsenal.h"
#include "chooser.h"
#include "mapIcon.h"
#include "message.h"
#include "selector.h"

using namespace std;
using namespace sf;

namespace MenuItems {
	class Menu {
		bool active = false;
		int width, height;
		const int SEGMENTS = 7;//segments to divide height by when coordinating options
		int page = 0;
		Image cursorImg;
		Cursor cursor;
		Texture bg, title;
		Sprite sprite;
		Font font;
		Text text;
		Selector selector;
		bool queueExit = false, queueStartGame = false;

		//power select page
		bool singlePlayer;
		Chooser colorSelect[2];
		CircleShape pSkins[2];
		int pSkinColors[2];
		Chooser powerSelect;
		const int SPACE_CSELECT = 200, SPACE_PSELECT = 175;
		Texture powerTextures[6];
		Arsenal arsenals[2];
		Message msg;

		//map select page
		MapIcon maps[6];
		int selectedMap;

		//key bindings page
		Keyboard::Key bindings1[8] = {
			Keyboard::X,
			Keyboard::E,
			Keyboard::R,
			Keyboard::T,
			Keyboard::W,
			Keyboard::D,
			Keyboard::S,
			Keyboard::A
		};
		Keyboard::Key bindings2[8] = {
			Keyboard::L,
			Keyboard::I,
			Keyboard::O,
			Keyboard::P,
			Keyboard::Up,
			Keyboard::Right,
			Keyboard::Down,
			Keyboard::Left
		};

	public:
		static const int CHAR_SIZE = 45;//the size of a character in a label
		static int powerPrices[6];
		static int powerDmg[3];

		Menu(int, int);
		void draw(RenderWindow&);
		static void drawStats(RenderWindow&, Text, Vector2f, int);
		void select(int);
		bool isActive() { return active; }
		void setActive(bool active, RenderWindow&);
		void setActive(bool active) { this->active = false; }
		void activateSelected();
		void clear(int);
		bool checkPowersFilled();
		void keyPressed();
		void keyReleased(Event);
		void mouseMoved();
		void mouseReleased();
		void setExitQueue(bool val) { queueExit = val; }
		void setStartGameQueue(bool val) { queueStartGame = val; }
		bool isCpu() { return singlePlayer; }
		bool getExitQueue() { return queueExit; }
		bool getStartGameQueue() { return queueStartGame; }
		Color getSkinColor(int slot);
		Color getSkinOutlineColor(int slot);
		Color getPlayerColor(int player) { return getSkinColor(colorSelect[player].slot); }
		Color getPlayerOutlineColor(int player) { return
			getSkinOutlineColor(colorSelect[player].slot); }
		int getSelectedMap() { return selectedMap; }
		Texture getMapTexture() { return *maps[selectedMap - 1].getTexture(); }
		Keyboard::Key* getBindings(int playerNo) {
			if (playerNo == 0)
				return bindings1;
			else
				return bindings2;
		}
		/// <summary>
		/// Returns string based on key since key does not have
		/// toString() function.
		/// </summary>
		static string getBindingString(Keyboard::Key key) {
			string binding;

			switch (key) {
			case Keyboard::Q:
				binding = "Q";
				break;
			case Keyboard::W:
				binding = "W";
				break;
			case Keyboard::E:
				binding = "E";
				break;
			case Keyboard::R:
				binding = "R";
				break;
			case Keyboard::T:
				binding = "T";
				break;
			case Keyboard::Y:
				binding = "Y";
				break;
			case Keyboard::U:
				binding = "U";
				break;
			case Keyboard::I:
				binding = "I";
				break;
			case Keyboard::O:
				binding = "O";
				break;
			case Keyboard::P:
				binding = "P";
				break;
			case Keyboard::A:
				binding = "A";
				break;
			case Keyboard::S:
				binding = "S";
				break;
			case Keyboard::D:
				binding = "D";
				break;
			case Keyboard::F:
				binding = "F";
				break;
			case Keyboard::G:
				binding = "G";
				break;
			case Keyboard::H:
				binding = "H";
				break;
			case Keyboard::J:
				binding = "J";
				break;
			case Keyboard::K:
				binding = "K";
				break;
			case Keyboard::L:
				binding = "L";
				break;
			case Keyboard::Z:
				binding = "Z";
				break;
			case Keyboard::X:
				binding = "X";
				break;
			case Keyboard::C:
				binding = "C";
				break;
			case Keyboard::V:
				binding = "V";
				break;
			case Keyboard::B:
				binding = "B";
				break;
			case Keyboard::N:
				binding = "N";
				break;
			case Keyboard::M:
				binding = "M";
				break;
			}

			return binding;
		}
	};
}