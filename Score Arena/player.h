#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "attackArsenal.h"

using namespace sf;

namespace Game {
	class Player : public CircleShape {
		bool isCpu = false;
		static const int BINDING_LENGTH = 8;
		Keyboard::Key bindings[BINDING_LENGTH];//attack menu, attack 1-3, up-left
		std::string name;

		//movement records
		bool upR = true, rightR = true, downR = true, leftR = true;
		float upTime, rightTime, downTime, leftTime;
		Vector2f startPos;
		const int SPEED = 8;
		int curSpeed = SPEED;
		Vector2f mapSize;

		//power variables
		Sprite sprite;
		int powerQueue = 0;//queue can be used for powers 1-3; 0 means no power queued
		bool invincible = false;

	public:
		const int SCORE_DEFAULT = 30;
		int score = SCORE_DEFAULT;
		AttackArsenal arsenal;
		Color skinColor, skinOutlineColor;

		Player();
		void draw(RenderWindow&, Text);
		void damage(int);
		void heal(int);
		void move();
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
		void setMapSize(Vector2f mapSize) { this->mapSize = mapSize; }
		void setName(std::string name) { this->name = name; }
		void setInvincible(bool invincible) { this->invincible = invincible; }
		bool isInvincible() { return invincible; }
		Vector2f getMapSize() { return mapSize; }
		std::string getName() { return name; }
		int getCurSpeed() { return curSpeed; }
		int getSpeed() { return SPEED; }
		int getPowerQueue() { return powerQueue; }
		bool getMovementQueue(int dir) {
			//dir is clock wise (0-top, 3-left)
			if (dir == 0)
				return !upR;
			else if (dir == 1)
				return !rightR;
			else if (dir == 2)
				return !downR;
			else
				return !leftR;
		}
		bool getCpu() { return isCpu; }
		void keyPressed(Clock);
		void keyReleased(Event, Clock);
	};
}