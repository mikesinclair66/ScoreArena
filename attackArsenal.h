#pragma once
#include "arsenal.h"

namespace Game {
	class AttackArsenal : public MenuItems::Arsenal {
		RectangleShape background;
		bool visible = false;

	public:
		AttackArsenal();
		void draw(RenderWindow&, Sprite, Text);
		bool isVisible() { return visible; }
		int getPowerSlot(int container) { return containers[container].slot; }
		void setLocation(Vector2f) override;
		void setVisible(bool visible) { this->visible = visible; }
		void setPowerSlot(int container, int slot) { containers[container].slot = slot; }
	};
}