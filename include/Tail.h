#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tail
{
public:
	Tail(sf::Vector2f position);
	void DrawPart(RenderWindow& window);

	sf::Vector2f GetPos() { return tailPos; };
	RectangleShape Box() { return box; };
	// Little commenting here; a lot of this is easy and self-explanatory.
private:
	sf::RectangleShape box;
	sf::Vector2f tailPos;
};