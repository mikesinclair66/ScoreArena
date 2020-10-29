#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "player.h"

using namespace sf;

namespace Game {
	class Power {
	protected:
		int powerNo;//power number to powerPrice[] and powerDmg[]
		bool priceRequired = true;//if affordability is needed to use; lose if can't afford
		bool drawable = false;//if the power has effects that constantly need to be drawn
		bool toggled = false;
		int curFrame, frameDuration = 100;

	public:
		Power();
		bool canAfford(int pScore);
		bool requiresPrice() { return priceRequired; }
		virtual void start(Player& player, Player& opponent);
		virtual void update(Player& player, Player& opponent);
		virtual void end(Player& player, Player& opponent);
		virtual void draw(RenderWindow&);
		void setDrawable(bool drawable) { this->drawable = drawable; }
		bool getDrawable() { return drawable; }
		int getPrice() { return MenuItems::Menu::powerPrices[powerNo]; }
		bool isActive() { return toggled; }
		int getPowerNo() { return powerNo; }
	};

	class Attack : public Power {
	public:
		Attack();
	};

	class Absorb : public Power {
	public:
		Absorb();
	};

	class Fire : public Power {
	public:
		Fire();
	};

	class Freeze : public Power {
	public:
		Freeze();
		void start(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};

	class Shield : public Power {
	public:
		Shield();
	};

	class Speed : public Power {
		Color innerYellow = Color(255, 255, 175), outerYellow = Color(255, 255, 0);
		Color innerBlue = Color(175, 255, 255), outerBlue = Color(0, 255, 255);
		const static int LINES_MIN = 1, LINES_MAX = 4;
		const static int LENGTH_MIN = 25, LENGTH_MAX = 50;

		class Bolt {
		public:
			RectangleShape lines[LINES_MAX];
			RectangleShape innerLines[LINES_MAX];
			int lineNo;

			void setColor(Color outer, Color inner) {
				for (int i = 0; i < lineNo; i++) {
					lines[i].setFillColor(outer);
					innerLines[i].setFillColor(inner);
				}
			}
			void setLocation(Vector2f pos) {
				for (int i = 0; i < lineNo; i++) {
					lines[i].setPosition(pos);
					innerLines[i].setPosition(pos);

					FloatRect boundingBox = lines[i].getGlobalBounds();
					if (lines[i].getRotation() <= 90)
						pos.x += (boundingBox.width - 5);
					else
						pos.x -= (boundingBox.width - 5);
					pos.y += (boundingBox.height - 5);
				}
			}
			void draw(RenderWindow& window) {
				for (int i = 0; i < lineNo; i++) {
					window.draw(lines[i]);
					window.draw(innerLines[i]);
				}
			}
		};
		int curBolt = 0;
		const static int BOLT_NO = 4;
		Bolt bolts[BOLT_NO];

		void initEffect();

	public:
		Speed();
		void draw(RenderWindow&) override;
		void start(Player& player, Player& opponent) override;
		void update(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};
}