#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using std::cout;

class Food
{
public:
	Food();
	/*		###########
			# Getters #
			###########			*/
	FloatRect GlobalBounds(){ return food.getGlobalBounds();}
	RectangleShape GetFood() { return food; };

	/*		###########
			# Setters #
			###########			*/
	void DrawTo(RenderWindow& window);
	void RandomisePos(); // Why destroy and make a new food pellet? Just recycle.
	void SetPos(Vector2f newPos); // Self explanatory; create position for food to spawn.
	RectangleShape FoodRect() { return food; };

	// If I get time, I should consider making an 'Entity.h' some of the methods as virtuals.
// maybe later.

private:
	RectangleShape food;
};