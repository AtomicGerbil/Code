#include "../include/Head.h"
// Properties for this broke. Consider using CMake?

Head::Head()
{
	player.setSize(Vector2f{ 26.f, 26.f });
	player.setOrigin(Vector2f{ 13.f, 13.f });
	player.setFillColor(sf::Color::Blue);
	length = 30;
	lastPressed = Up;
}


void Head::InputKey(unsigned int dir)
{
	// Switch for directional input.
	// Won't comment here; it's really self-explanatory.

	tailList.push_back(Tail{player.getPosition()});
	// Pushback tail with Tail @ player.getPosition.
	// By the time this happens, player has moved forward one block.
	// In short, this follows a /shadow/ of the player's last pos.

	switch (dir)
	{
	case Up: {
		player.move(Vector2f{ 0.f, -30.f });
		break;
	}

	case Down: {
		player.move(Vector2f{ 0.f, 30.f });
		break;
	}

	case Left: {
		player.move(Vector2f{ -30.f, 0.f });
		break;
	}

	case Right: {
		player.move(Vector2f{ 30.f, 0.f });
		break;
	}

	default:
		printf("\n Error: Input not recognised in Head.cpp.");
		// No need to use cout ALL the time; this does the same.
		// This should never enter default anyways, so this is (in hope) unreachable code.
		break;
	}
}

void Head::TimeTick()
{
	InputKey(lastPressed);
	while (tailList.size() > length)
	// While vector size tailList is greater than length, do:
	{
		tailList.erase(tailList.begin()); // Destruct tail at [0].
		tailList.shrink_to_fit(); // Shrink vector size to fit.
		// We could alternatively do some vector element moving.
		// The above comment would be a more optimised solution.
	}
}

void Head::DrawTo(RenderWindow& window)
{
	window.draw(player);
	for (auto& part : tailList)
	// Couldn't figure out the var type, so let auto handle it lol.
	{
		part.DrawPart(window);
	}
	//for (auto& part : tailList)
	//{
	//	part.DrawPart(window);
	//}
}

void Head::SpawnPos(Vector2f spawnPos)
{
	player.setPosition(spawnPos);
}