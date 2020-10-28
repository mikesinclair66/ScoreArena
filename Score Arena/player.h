#pragma once
#include <SFML/Graphics.hpp>
#include "attackArsenal.h"

using namespace sf;

namespace Game {
	class Player : public CircleShape {
		bool isCpu = false;
		static const int BINDING_LENGTH = 8;
		Keyboard::Key bindings[BINDING_LENGTH];//attack menu, attack 1-3, up-left
		const int SCORE_DEFAULT = 30;
		AttackArsenal arsenal;

		//movement records
		bool upR = true, rightR = true, downR = true, leftR = true;
		float upTime, rightTime, downTime, leftTime;
		Vector2f startPos;
		int speed = 8;

	public:
		int score = SCORE_DEFAULT;

		Player();
		void draw(RenderWindow&);
		void move(Vector2f);
		void setCpu(bool isCpu) { this->isCpu = isCpu; }
		void setKeyBindings(Keyboard::Key bindings[BINDING_LENGTH]) {
			for (int i = 0; i < BINDING_LENGTH; i++)
				this->bindings[i] = bindings[i];
		}
		void keyPressed(Clock);
		void keyReleased(Event, Clock);
	};
}