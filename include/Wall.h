#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Wall
{
public:
	Wall();
	void CreateWall(float lengthX, float lengthY, Vector2f position);
	void DrawTo(RenderWindow &window);
	RectangleShape WallRect() { return wall; };
	// We just make walls this way to contain the snake.
private:
	RectangleShape wall;
};