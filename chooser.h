#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace MenuItems {
	class Chooser {
		const int ARROW_SIZE = 100;
		const int ARROW_OUTLINE = 10;
		Vector2f pos;
		int selected = 0;
		int slotMax = 5;
		void initArrow(CircleShape&, bool);

	public:
		/* A chooser has a specified amount of slots. For the power select, the number
		of available powers is the number of slots. */
		int slot = 0;
		CircleShape a1, a2;

		Chooser();
		void draw(RenderWindow&);
		void requestSelect(Vector2i);
		void activateSelected();
		void setPosition(Vector2f, int);
		void setSlotMax(int slotMax) { this->slotMax = slotMax; }
		void select(int);
		int getSelected() { return selected; }
		Vector2f getPosition() { return pos; }
		int getSlotMax() { return slotMax; }
	};
}