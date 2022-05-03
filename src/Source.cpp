#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono> // Elegant, beautiful chrono.
#include "../include/Head.h"
#include "../include/Food.h"
#include "../include/Wall.h"
#include "../include/UI.h"

using namespace std;
unsigned int score = 0;

void CheckCollisions(Head* p, Food* f, Wall* wT, Wall* wB, Wall* wL, Wall* wR, UI* ui) {
	// Set up pointers so I can point (->) to functions.
	sf::Rect<float> playerGrid{ p->PlayerRect().getGlobalBounds() };
	sf::Rect<float> foodGrid{ f->FoodRect().getGlobalBounds() };
	sf::Rect<float> wallTopGrid{ wT->WallRect().getGlobalBounds() };
	sf::Rect<float> wallBotGrid{ wB->WallRect().getGlobalBounds() };
	sf::Rect<float> wallLeftGrid{ wL->WallRect().getGlobalBounds() };
	sf::Rect<float> wallRightGrid{ wR->WallRect().getGlobalBounds() };
	// Get global bounds of all objects in-game.
	// Not very efficient; should have colliders personalised to each class.
	// I'll do it when it can / feel like doing it. This project was a nightmare enough, sifting through docs.

	if (playerGrid.intersects(foodGrid)) { // Simple intersection check.
		ostringstream sScore;	score++; // New var from iostream
		sScore.str(""); // Sets empty string.
		sScore << "Score: " << score; 
		// Under the hood, Score is treated as character; pointer for additional value (score) is pointed and used.
		p->LengthUp(); // Nom food, grow tail.
		f->RandomisePos(); // Recycle food and place somewhere else.
		ui->setScore(sScore.str()); // Writes output string stream as a string into setScore.
	}

	if (playerGrid.intersects(wallTopGrid) || playerGrid.intersects(wallBotGrid) || playerGrid.intersects(wallLeftGrid) || playerGrid.intersects(wallRightGrid))
	{
		exit(0);
	}

	// Now to check if player collides w/ tail. We have to go through the vector to do it tho.
	for (auto& part : p->TailList()) {
		sf::Rect<float> tailPos{ part.Box().getGlobalBounds() };
		// same global bounds get.
		if (playerGrid.intersects(tailPos)) {
			exit(0);
		}
	}
}

// Honestly easier to write the collider function here.
// If I get around to cleaning it up, maybe. For now, cba.


int main()
{
	// Create a window with the constructor
	sf::RenderWindow window(sf::VideoMode(900, 900), "Snake Game");
	window.setPosition(sf::Vector2i(400, 50)); // Set the position of the window to 100,100
	window.setFramerateLimit(60); // Set the limit of the the number of frames per second
	window.setKeyRepeatEnabled(true);


	//https://en.cppreference.com/w/cpp/chrono
	// Chrono API: 19/04/2022
	// Store time of when app instance was launched through system clock.
	auto instanceClock = chrono::system_clock::now();
	// Chrono Library is time-keeping with varying levels of precision.
	// We call system_clock, which calls to the very thing in your taskbar window showing time.
	// Auto is an inferred var type - compiler sets it to relevant var to store the variable. 
	// E.G: Hover over 'clock' to see what it is in VS-19

	Head playerHead{}; // Same as Head playerHead = Head();
	Food food{};
	Wall wallTop{};			wallTop.CreateWall(900, 26, { 450.f, 0.f });
	Wall wallBot{};			wallBot.CreateWall(900, 26, { 450.f, 900.f });
	Wall wallLeft{};		wallLeft.CreateWall(26, 900, { 0.f, 450.f });
	Wall wallRight{};		wallRight.CreateWall(26, 900, { 900.f, 450.f });
	UI ui{};
	// Creates walls.

	playerHead.SpawnPos(Vector2f{ 270.f, 270.f });
	food.SetPos({ 600.f, 600.f });

					  // Run until the user closes the window
	while (window.isOpen())
	{
		// check all user events
		sf::Event event;

		// Lines 60 to 84, you can guess, is character movement.
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (playerHead.LastPressed() != Down) {
				playerHead.LastPressed(Up);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (playerHead.LastPressed() != Up) {
				playerHead.LastPressed(Down);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (playerHead.LastPressed() != Right) {
				playerHead.LastPressed(Left);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (playerHead.LastPressed() != Left) {
				playerHead.LastPressed(Right);
			}
		}

		while (window.pollEvent(event))
		{
			// User has pressed the close button
			switch (event.type)
			{
			case (Event::Closed):
				window.close();
				break; // Perhaps unreachable code, but not chancing it.
			}
			/*
			// ew stinky sf::Time, use std::chrono instead, more precise.
			// It's even in the wrong position for it to clock correctly in code.

			sf::Time elapsedTime = timer.getElapsedTime();
			if (elapsedTime.asSeconds() > 1.0f)
			{
				cout << iCounter << endl;
				iCounter++; // Increment the counter
				if (iCounter == 60) iCounter = 0;
				timer.restart();
			}*/
		}

		auto instanceTime = chrono::system_clock::now(); // This updates while the window is open, so we get precise time.
		chrono::duration<float, milli> diff = instanceTime - instanceClock;
		// Get duration (in float & milliseconds) difference between instanceTime and instanceClock.
		float timer = 300.f - ((playerHead.Length() - 2) * 8.f); 
		// 300 milliseconds base; snake gets faster based on number of tails (excludes starting tails).
		timer = (timer > 130.f) ? timer : 130.f; // Clamps speed of snake.
		// Expression is evaluated (? operator); if true, it equals timer. If false, it equals 150.f.

		if (diff.count() > timer) // If difference is now greater than timer...
			//... We know 500 milliseconds passed.
		{
			instanceClock = chrono::system_clock::now(); // Set new clock to current time.
			instanceClock = instanceTime; // Reset clock to current instance.
			// Store address of playerHead and food colliding.
			playerHead.TimeTick();
			CheckCollisions(&playerHead, &food, &wallTop, &wallBot, &wallLeft, &wallRight, &ui);
		}

		food.DrawTo(window);
		playerHead.DrawTo(window);
		wallTop.DrawTo(window); wallBot.DrawTo(window); 
		wallLeft.DrawTo(window); wallRight.DrawTo(window);
		ui.DrawTo(window);
		window.display();
		window.clear();
	}
}