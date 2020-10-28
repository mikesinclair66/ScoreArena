#pragma once
#include "arsenal.h"

namespace Game {
	class AttackArsenal : public MenuItems::Arsenal {
		RectangleShape background;
		bool visible = false;

	public:
		AttackArsenal();
		void draw(RenderWindow&) override;
		bool isVisible() { return visible; }
		void setLocation(Vector2f) override;
		void setVisible(bool visible) { this->visible = visible; }
	};
}