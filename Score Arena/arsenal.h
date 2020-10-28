#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace MenuItems {
	class Arsenal {
		class Container : public RectangleShape {
			int slotMax = 6;

		public:
			int slot = 0;//unlike the chooser class, a slot of 0 displays nothing
		};

		const int CONTAINER_OUTLINE = 8;

	protected:
		const int CONTAINER_YMOD = 45;

	public:
		Container containers[3];

		Arsenal();
		virtual void draw(RenderWindow&);
		virtual void setLocation(Vector2f);
		void clear();
		void mouseReleased(int slot);
	};
}