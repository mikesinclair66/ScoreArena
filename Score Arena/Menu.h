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
	class BindingSet {
		const static int BINDING_NO = 8;
		string labels[BINDING_NO];
		Vector2f locations[BINDING_NO];
		bool changed[BINDING_NO];
		int hovered = 0;
		int selected = 0;

	public:
		Keyboard::Key bindings[BINDING_NO];

		BindingSet();
		void setBindings(Keyboard::Key bindings[8]);
		Keyboard::Key* getBindings() { return bindings; }
		void setLocation(Vector2f, Vector2f);
		void draw(RenderWindow&, Text);
		void mouseReleased();
		void mouseMoved(Vector2i);
		void keyReleased(Keyboard::Key);
		void clear();
		int getSelected() { return selected; }
	};

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

		BindingSet bindingSets[2];

	public:
		static const int CHAR_SIZE = 45;//the size of a character in a label
		static Texture powerTextures[6];
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
		int getPowerSlot(int player, int slot) {
			return arsenals[player].containers[slot].slot;
		}
		/// <summary>
		/// Returns string based on key since key does not have
		/// toString() function.
		/// </summary>
		static string getBindingString(Keyboard::Key key) {
			string binding;

			switch (key) {
			case Keyboard::Up:
				binding = "UP";
				break;
			case Keyboard::Right:
				binding = "RIGHT";
				break;
			case Keyboard::Down:
				binding = "DOWN";
				break;
			case Keyboard::Left:
				binding = "LEFT";
				break;
			case Keyboard::Num0:
				binding = "0";
				break;
			case Keyboard::Num1:
				binding = "1";
				break;
			case Keyboard::Num2:
				binding = "2";
				break;
			case Keyboard::Num3:
				binding = "3";
				break;
			case Keyboard::Num4:
				binding = "4";
				break;
			case Keyboard::Num5:
				binding = "5";
				break;
			case Keyboard::Num6:
				binding = "6";
				break;
			case Keyboard::Num7:
				binding = "7";
				break;
			case Keyboard::Num8:
				binding = "8";
				break;
			case Keyboard::Num9:
				binding = "9";
				break;
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