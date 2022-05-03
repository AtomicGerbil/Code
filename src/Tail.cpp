#include "../include/Tail.h"
// Properties for this broke. Consider using CMake?

Tail::Tail(sf::Vector2f position)
{
	// Basic set pos, size and fill colour.
	// I am not doing fancy textures; no way.
	// okay mayber later, if I feel like it.
	box.setPosition(position);
	box.setSize(Vector2f{ 26.f, 26.f });
	box.setOrigin(Vector2f{ 13.f, 13.f });
	box.setFillColor(Color::Green);

	tailPos = position;
}

void Tail::DrawPart(RenderWindow &window)
{
	window.draw(box);
}