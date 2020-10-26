#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class MapIcon : public RectangleShape {
	Texture t;
	bool disabled = false;

public:
	MapIcon();
	void draw(RenderWindow&, Text);
	bool loadImage(string path);
	bool requestSelect(Vector2i);
	void setDisabled(bool disabled);
	bool getDisabled() { return disabled; }
};