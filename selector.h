#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace MenuItems {
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
		const int SELECTOR_SPACE = 30;//space below the text
		const int SELECTOR_HEIGHT = 15;
		Clock clock;

	public:
		Set sets[NUM_PAGES];

		Selector();
		void select(int s, int p);
		void draw(RenderWindow& window, int page, Text t);
	};
}