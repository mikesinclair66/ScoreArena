#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace MenuItems {
	class Message {
		Clock clock;
		string msg;
		bool activated = false;
		Vector2f position;

	public:
		void draw(RenderWindow&, Text);
		void setMsg(string msg) { this->msg = msg; }
		void setPosition(Vector2f position) { this->position = position; }
		void activate();
		void deactivate();
		bool checkActive();
		Vector2f getPosition() { return position; }
	};
}