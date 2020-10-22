#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Selector : public RectangleShape {
	/// <summary>
	/// A set object is a set of labels that can be selected
	/// within the menu. Each page of the menu has a set.
	/// </summary>
	class Set {
		vector<string> labels;
		vector<Vector2f> locations;
		int selected = 0;

	public:
		void push_back(string, Vector2f);
		void draw(RenderWindow&, Text);
		string getLabel(int i) { return labels.at(i); }
		Vector2f getLocation(int i) { return locations.at(i); }
		int getSelected() { return selected; }
		void select(int);
		int getOptionsLength() { return labels.size(); }
	};

	static const int NUM_PAGES = 4;

public:
	static const int CHAR_SIZE = 45;//the size of a character in a label
	Set sets[NUM_PAGES];
};