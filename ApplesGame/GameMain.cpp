#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"

int main()
{
	using namespace CatAndApples;

	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Cat and Apples");

	// Game initialization
	Game game;
	InitGame(game);
	
	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen())
	{
		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Read events
		sf::Event event;

		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
			{
				window.close();
				
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				
			}

			ProcessSelectionMenu(game, event);
		
		}
		window.clear(sf::Color::Black);


		if (game.state == GameState::ModeSelection)
		{
			ModeSelection(game, window);
		}
		else
		{
			UpdateGame(game, deltaTime);
			DrawGame(game, window);
		}
		

		window.display();
	}

	// Deinitialization
	DeinializeGame(game);
	return 0;
}
