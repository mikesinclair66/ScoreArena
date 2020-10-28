#pragma once
#include <SFML/Graphics.hpp>

namespace Game {
	class Power {
	public:
		Power();
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