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
		Color skinColor, skinOutlineColor;

		//movement records
		bool upR = true, rightR = true, downR = true, leftR = true;
		float upTime, rightTime, downTime, leftTime;
		Vector2f startPos;
		const int SPEED = 8;
		int curSpeed = SPEED;

		//power variables
		Sprite sprite;
		int powerQueue = 0;//queue can be used for powers 1-3; 0 means no power queued

	public:
		int score = SCORE_DEFAULT;
		AttackArsenal arsenal;

		Player();
		void draw(RenderWindow&, Text);
		void move(Vector2f);
		void restoreCurSpeed() { curSpeed = SPEED; }
		void setCpu(bool isCpu) { this->isCpu = isCpu; }
		void setFillColor(Color c) {
			CircleShape::setFillColor(c);
			skinColor = c;
		}
		void setCurFillColor(Color c) { CircleShape::setFillColor(c); }
		void setOutlineColor(Color c) {
			CircleShape::setOutlineColor(c);
			skinOutlineColor = c;
		}
		void setCurOutlineColor(Color c) { CircleShape::setOutlineColor(c); }
		void setKeyBindings(Keyboard::Key bindings[BINDING_LENGTH]) {
			for (int i = 0; i < BINDING_LENGTH; i++)
				this->bindings[i] = bindings[i];
		}
		void setCurSpeed(int curSpeed) { this->curSpeed = curSpeed; }
		void setPowerQueue(int powerQueue) { this->powerQueue = powerQueue; }
		int getCurSpeed() { return curSpeed; }
		int getPowerQueue() { return powerQueue; }
		bool getCpu() { return isCpu; }
		void keyPressed(Clock);
		void keyReleased(Event, Clock);
	};
}