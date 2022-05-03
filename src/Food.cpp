#include "../include/Food.h"
#include "../include/Head.h"

Food::Food()
{
	food.setSize(Vector2f{ 26.f, 26.f });
	food.setOrigin(Vector2f{ 13.f, 13.f });
	food.setFillColor(sf::Color::Cyan);
}

void Food::DrawTo(RenderWindow& window)
{
	window.draw(food);
}

void Food::SetPos(Vector2f newPos)
{
	Head p;

	// Clamps position of food spawn to an 870x870 grid.
	if (newPos.x > 870 || newPos.y > 870 || newPos.x < 30 || newPos.y < 30)
	{
		cout << "\n Entered clamp expression";
		RandomisePos();
		// Store vector2f of position where food and tail overlapped.
		// This could be optimised if we could keep a track of each 'cell' in the game, and spawn in a cell that isn't occupied.
		// Unfortunately, I lack the knowledge to do this.
	}

	else 
	{
		cout << "\nEntered else statement.";
		p.TailList();
		for (auto& part : p.TailList()) {
			cout << "\n Checking tail... ";
			// Checks through each part of the snake.
			// We don't know /where/ the overlap is, so we have to check each part of the snake.
			// Computers don't have our inherent human vision, after all; this requires no testing.
			if (newPos == part.GetPos())
				// Checks that each part of the snake isn't at the same coordinates of where the food want to spawn.
			{
				RandomisePos();
				// Since food only spawns in one position, we only record where the position was.
				// The position, being where the food overlapped on the tail.
			}
		}
		food.setPosition(newPos);
	}
}

void Food::RandomisePos()
{
	// Number of segments is put into the random pos. We * 30 as 900 / 30 is 30.
	// Grid of 20, 900 / 20 would be 45.
	float randX = (int)(rand() % 30) * 30.f;
	float randY = (int)(rand() % 30) * 30.f;
	// Implicit conversions.
	SetPos(Vector2f{randX, randY});
}