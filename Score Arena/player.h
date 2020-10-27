#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Game {
	class Player : public CircleShape {
		bool isCpu = false;
		static const int BINDING_LENGTH = 8;
		Keyboard::Key bindings[BINDING_LENGTH];//attack menu, attack 1-3, up-left
		const int SCORE_DEFAULT = 30;
		int score = SCORE_DEFAULT;

		//movement records
		

	public:
		const float SPEED_MOD = 2;

		Player();
		void draw(RenderWindow&);
		void setCpu(bool isCpu) { this->isCpu = isCpu; }
		void setKeyBindings(Keyboard::Key bindings[BINDING_LENGTH]) {
			for (int i = 0; i < BINDING_LENGTH; i++)
				this->bindings[i] = bindings[i];
		}
		void keyPressed(Clock);
		void keyReleased(Event, Clock);
	};
}