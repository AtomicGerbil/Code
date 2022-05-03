#pragma once

// Imported custom-made script that was built outside of the Snake assignment.
// This is why you'll be seeing `sf::` and `std::` more often here.

#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;

class SpriteManagerV2
{
private:
	sf::Texture texture; sf::Sprite sprite; sf::Vector2i sheetDims;
	std::vector<sf::IntRect> spriteRects;
	bool isAnimated = true;
	// Creates dynamic vector for an sfml integer rect.
	// Rect describes a rectangular frame, defined from top-left and by size (width x height).
	int imageX, imageY;
public:
	void spriteCreate(std::string filename, sf::Vector2f vector2f, sf::Vector2i sheetDims, int x, int y, bool isAnimated);

	void animateSprite(int iNumOfFrames);

	std::vector<sf::IntRect> SpriteRect()
	{
		return spriteRects;
	}
	// Getter method for spriteRects; lets us animate outside the scope.
};