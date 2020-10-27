#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Game {
	class Player : public CircleShape {
		bool isCpu;
		static const int BINDING_LENGTH = 7;
		Keyboard bindings[BINDING_LENGTH];//attack 1-3, up-left

	public:
		Player();
		void draw(RenderWindow&);
		void setCpu(bool isCpu) { this->isCpu = isCpu; }
		void setKeyBindings(Keyboard bindings[BINDING_LENGTH]) {
			for (int i = 0; i < BINDING_LENGTH; i++)
				this->bindings[i] = bindings[i];
		}
	};
}