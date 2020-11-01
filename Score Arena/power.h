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
		bool attackLanded = false;//if true, push players away from each other
		int pushback = 15;//frames to push player back after landed attack
		int powerNo;//power number to powerPrice[] and powerDmg[]
		bool priceRequired = true;//if affordability is needed to use; lose if can't afford
		bool drawable = false;//if the power has effects that constantly need to be drawn
		bool toggled = false;
		int curFrame, frameDuration = 100;

	public:
		Power();
		virtual void landAttack();
		bool canAfford(int pScore);
		bool requiresPrice() { return priceRequired; }
		virtual void draw(RenderWindow&, Player&, Player&);
		virtual void start(Player& player, Player& opponent);
		virtual void update(Player& player, Player& opponent);
		virtual void end(Player& player, Player& opponent);
		virtual void activate();
		void setDrawable(bool drawable) { this->drawable = drawable; }
		bool getDrawable() { return drawable; }
		int getPrice() { return MenuItems::Menu::powerPrices[powerNo]; }
		bool isActive() { return toggled; }
		int getPowerNo() { return powerNo; }
	};

	class Attack : public Power {
		bool queueDamage = false;

	public:
		Attack();
		void landAttack() override;
		void start(Player& player, Player& opponent) override;
		void update(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};

	class Absorb : public Power {
		int ppf;
		bool ppfTooSmall = false;
		int remaining;

		RectangleShape ring;

	public:
		Absorb();
		void landAttack() override;
		void draw(RenderWindow&, Player&, Player&) override;
		void start(Player& player, Player& opponent) override;
		void update(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};

	class Fire : public Power {
		Texture bulletTexture;
		Sprite sprite;
		CircleShape innerRing, outerRing;
		RectangleShape lineHoriz, lineVert;
		Vector2f aimPos;
		const static int BULLET_NO = 3, SPEED = 25;
		int bulletNo;
		Vector2f bullets[BULLET_NO];
		Vector2f destination[BULLET_NO];
		bool fired[BULLET_NO];
		int rotation[BULLET_NO];
		bool exploded[BULLET_NO];
		CircleShape explosion[BULLET_NO];
		const static int RADIUS_MIN = 5, RADIUS_MAX = 175;
		const static int THICKNESS_MIN = 3;
		bool directHit[BULLET_NO];//if directly hit by the missile, blast radius doesn't damage
		bool up = false, right = false, down = false, left = false;
		bool queueDamage = false;

		void initExplosion(int);

	public:
		Fire();
		void landAttack() override;
		void start(Player& player, Player& opponent) override;
		void update(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
		void draw(RenderWindow&, Player& player, Player& opponent) override;
		void activate() override;
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
		const static int LINES_MIN = 1, LINES_MAX = 5;
		const static int LENGTH_MIN = 10, LENGTH_MAX = 25;

		class Bolt {
		public:
			RectangleShape lines[LINES_MAX];
			int lineNo;
			Vector2f playerPos = Vector2f(0, 0);//position within player diameter

			void setColor(Color outer, Color inner) {
				for (int i = 0; i < lineNo; i++) {
					lines[i].setFillColor(outer);
				}
			}
			void setLocation(Vector2f pos) {
				for (int i = 0; i < lineNo; i++) {
					lines[i].setPosition(pos);

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
				}
			}
		};
		int curBolt = 0;
		const static int BOLT_NO = 5;
		Bolt bolts[BOLT_NO];

		void initEffect();

	public:
		Speed();
		void draw(RenderWindow&, Player& player, Player& opponent) override;
		void start(Player& player, Player& opponent) override;
		void update(Player& player, Player& opponent) override;
		void end(Player& player, Player& opponent) override;
	};
}