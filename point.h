#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Game {
	class Point : public RectangleShape {
		Color shadowColor;
		RectangleShape shadow;
		const int SHADOW_DISTANCE = 10;//distance from point to its shadow

	public:
		Point();
		void draw(RenderWindow&);
		void setPosition(Vector2f);
		void setSize(Vector2f);
	};
}