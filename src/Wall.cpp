#include "../include/Wall.h"

Wall::Wall()
{
	wall.setFillColor(sf::Color::Yellow);
}

void Wall::CreateWall(float lengthX, float lengthY, Vector2f position)
{
	// Loops creation of wall while x is less than length given.
	wall.setSize(Vector2f{lengthX, lengthY});
	wall.setOrigin(Vector2f{ lengthX / 2.f, lengthY / 2.f });
	wall.setPosition(position);
}

void Wall::DrawTo(RenderWindow& window)
{
	window.draw(wall);
}