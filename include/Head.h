#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "Tail.h"

using namespace sf; using std::vector;
enum directions{Up = 73, Left = 71, Right = 74, Down = 72};
// Set up enumerator; word-to-int as a reference point.
// These values are the same as the ones from SFML's existing enumator.

class Head
{

public:
	Head();

	void InputKey(unsigned int dir);
	void TimeTick();
	// Time tick is needed as we keep a constant direction from lastPressed.
	// This activates via a clock timer in the window.
	void DrawTo(RenderWindow& window);

	/*		###########
			# Getters #
			###########			*/
	int Length() { return length; };
	int LastPressed() { return lastPressed; };
	const std::vector<Tail>& TailList() const { return tailList; }
	RectangleShape PlayerRect() { return player; };

	/*		###########
			# Setters #
			###########			*/
	void LastPressed(unsigned int lastPressed) { this->lastPressed = lastPressed; }; 
	// Set last pressed button based on user input.
	void LengthUp() { length++; };
	void SpawnPos(Vector2f spawnPos);

private:
	// Needed, as the snake will continue moving from when it was last pressed.
	// Default is down, since player starts with snake moving upwards.
	unsigned int lastPressed = Down;
	RectangleShape player;
	vector<Tail> tailList;
	unsigned int length;
	/*
	Logic behind this: A snake is just a vector of tails, right?
	Tail[0] simply follows the head of the snake.
	We just increase the length (length++) to make room for a new tail in the vector when eating food.
	*/

};