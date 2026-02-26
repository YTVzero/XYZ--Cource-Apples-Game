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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (game.state == GameState::Playing && !game.isGameFinished)
					{
						game.previousState = game.state;
						game.pauseSelection = 1;  
						game.state = GameState::PauseExit;
						PauseExitText(game.text, game);  
					}
					else if (game.state == GameState::ModeSelection)
					{
						window.close();
					}
					else if (game.state == GameState::PauseExit)
					{
						game.state = game.previousState;
					}
				}

				
				if (game.state == GameState::PauseExit)
				{
					if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
					{
						game.pauseSelection = (game.pauseSelection == 0) ? 1 : 0;
						PauseExitText(game.text, game); 
					}
					else if (event.key.code == sf::Keyboard::Enter)
					{
						if (game.pauseSelection == 0)  
						{
							window.close();
						}
						else                           
						{
							game.state = game.previousState;
						}
					}
				}
			}

			ProcessSelectionMenu(game, event);
		
		}
		window.clear(sf::Color::Black);

		if (game.state == GameState::ModeSelection)
		{
			ModeSelection(game, window);
		}
		else if (game.state == GameState::PauseExit)
		{
			
			DrawGame(game, window);

			
			sf::RectangleShape overlay(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
			overlay.setFillColor(sf::Color(0, 0, 0, 160));
			window.draw(overlay);

			DrawPauseExitText(game.text, window);
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
