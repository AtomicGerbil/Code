#include "../include/UI.h"

using namespace sf;

UI::UI()
{
	if (fontType.loadFromFile("./Assets/Fonts/norwester.otf"))
	{
		scoreText.setFont(fontType);
		scoreText.setCharacterSize(32);
		scoreText.setFillColor(sf::Color::Red);
		scoreText.setPosition({ 20.f, 20.f });
		// Basic constructor for the text.
	}
	else
	{
		printf("Unable to load file @ \'./Assets/Fonts/norwester.otf\'.");
		exit(1);
		// If it doesn't work, pretty much exit.
	}
}

void UI::DrawTo(RenderWindow &window)
{
	window.draw(scoreText);
}

void UI::setScore(const std::string& text)
{
	scoreText.setString(text);
	// This is used to alter the text.
}