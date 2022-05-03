#include "../include/SpriteManagerV2.h"

void SpriteManagerV2::spriteCreate(std::string filename, sf::Vector2f vector2f, sf::Vector2i sheetDims, int x, int y, bool isAnimated)
{
	bool bSuccess = false;

	if (texture.loadFromFile(".\\assets\\textures\\" + filename))
	{
		this->sheetDims = sheetDims;
		// You can reference by class (using this) and var name in private.
		// With that, it becomes equal to variable in parameters here.
		imageX = vector2f.x / texture.getSize().x;
		imageY = vector2f.y / texture.getSize().y;

		if (isAnimated)
		{
			// Set up for sheet dimensions if the item is animated.
			this->isAnimated = isAnimated;
			imageX *= sheetDims.x;
			imageY *= sheetDims.y;
		}

		sprite.setScale(imageX, imageY);
		sprite.setOrigin(imageX / 2.f / sprite.getScale().x, imageY / 2.f / sprite.getScale().y);
		sprite.setPosition(x, y);
		sprite.setTexture(texture);
	} else 
	{
		cout << "\n Filename\" " << filename  << "\" could not be found!";
	}
}

void SpriteManagerV2::animateSprite(int iNumOfFrames)
{
	int iCurrentFrame = 0;
	spriteRects.reserve(iNumOfFrames);
	// Memory management to reserve exactly what is needed.
	if(isAnimated)
	{
		for (unsigned short i = 0; i < (sheetDims.x * sheetDims.y); i++)
			// Short is just 16 bits; saves memory, since spriteshorts are not long.
			// No animation should even use more than a 500 frames. If it does, I fear what you are doing.
		{
			sf::Vector2i temp;

			temp.x = (imageX / sheetDims.x * i) % sheetDims.x; // * i as we are moving across the sheet.
			temp.y = imageY / sheetDims.y * (i / sheetDims.x);
			// Gives the size of 1 frame in a spritesheet.
			spriteRects.push_back(sf::IntRect(temp, sheetDims));
		}

		for (auto& entry : spriteRects)
			// Runs for every entry into the spriteRects; error checking.
		{
			cout << "\nEntry @ Width: " << entry.width;
			cout << "\nEntry @ Height: " << entry.height;
			cout << "\nEntry @ Top: " << entry.top;
			cout << "\nEntry @ Left: " << entry.left;
			// We check each thing is set correctly.
		}
	} 
}