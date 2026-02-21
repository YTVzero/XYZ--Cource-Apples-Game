#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include <sstream>

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
			std::ostringstream menuStr;
			menuStr << "=== MODE SELECTION ===\n\n"
				<< "1  The normal number of apples      " << ((game.gameMode & MODE_NORMAL_APPLES) ? "ON" : "OFF") << "\n"
				<< "2  Random number of apples       " << ((game.gameMode & MODE_RANDOM_APPLES) ? "ON" : "OFF") << "\n"
				<< "3  Lots of apples (~45)            " << ((game.gameMode & MODE_MANY_APPLES) ? "ON" : "OFF") << "\n"
				<< "4  Acceleration after the apple       " << ((game.gameMode & MODE_ACCELERATION) ? "ON" : "OFF") << "\n"
				<< "5  WITHOUT ACCELERATION               " << ((game.gameMode & MODE_WITHOUT_ACCELERATION) ? "ON" : "OFF") << "\n\n"
		
				<< "Press ENTER to start";

			game.text.menuText.setString(menuStr.str());
			window.draw(game.text.menuText);
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
