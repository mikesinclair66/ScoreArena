#pragma once
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "player.h"

using namespace sf;

namespace Game {
	class Power {
	protected:
		int powerNo;//power number to powerPrice[] and powerDmg[]
		bool priceRequired = true;//if affordability is needed to use; lose if can't afford
		bool toggled = false;
		int curFrame, frameDuration = 20;

	public:
		Power();
		bool canAfford(int pScore);
		bool requiresPrice() { return priceRequired; }
		void start();
		void update();
		void end();
		int getPrice() { return MenuItems::Menu::powerPrices[powerNo]; }
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
	};

	class Shield : public Power {
	public:
		Shield();
	};

	class Speed : public Power {
	public:
		Speed();
	};
}