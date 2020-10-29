#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "menu.h"
#include "player.h"

using namespace sf;

namespace Game {
	class Power {
	protected:
		int powerNo;//power number to powerPrice[] and powerDmg[]
		bool priceRequired = true;//if affordability is needed to use; lose if can't afford
		bool toggled = false;
		int curFrame, frameDuration = 100;

	public:
		Power();
		bool canAfford(int pScore);
		bool requiresPrice() { return priceRequired; }
		virtual void start(Player& player, Player& opponent);
		void update(Player& player, Player& opponent);
		virtual void end(Player& player, Player& opponent);
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
		const static int LINES_MIN = 4, LINES_MAX = 10;
		const static int LENGTH_MIN = 100, LENGTH_MAX = 200;

		class Bolt {
		public:
			RectangleShape lines[LINES_MAX];
			RectangleShape innerLines[LINES_MAX];
			int lineNo;

			void setLineNo(int lineNo) { this->lineNo = lineNo; }
			void setColor(Color outer, Color inner) {
				for (int i = 0; i < lineNo; i++) {
					lines[i].setFillColor(outer);
					innerLines[i].setFillColor(inner);
				}
			}
		};
		const static int BOLT_NO = 4;
		Bolt bolts[BOLT_NO];

		void initEffect();

	public:
		Speed();
		void start(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};
}