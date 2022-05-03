#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


using namespace sf;

class UI
{
public:
	UI();
	void DrawTo(RenderWindow &window);
	void setScore(const std::string& text);


private:
	sf::Font fontType;
	sf::Text scoreText;
};