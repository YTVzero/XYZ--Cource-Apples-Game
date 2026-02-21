#include "Game.h"
#include "Text.h"
#include <cstdlib>

namespace CatAndApples
{
	void InitGame(Game& game)
	{
		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		ScoreTextGame(game.text, game);
		ManualTextGame(game.text, game);
		ExitOrContTextGame(game.text, game);
		MenuText(game.text, game);      
		GameOverTextGame(game.text, game);
		LeaderboardTextGame(game.text, game);

		game.state = GameState::ModeSelection;
		game.gameMode = 0;

		game.leaderboard.GenerateFakeData();
	}

	void RestartGame(Game& game)
	{
		InitPlayer(game.player);

		ApplyGameMode(game);


		// Init rocks
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			InitRock(game.rock[i]);
		}

		//game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
		game.state = GameState::Playing;


		GameOverTextGame(game.text, game);
		ManualTextGame(game.text, game);
		ExitOrContTextGame(game.text, game);

	}

	void ApplyGameMode(Game& game)
	{
		if (game.apples != nullptr)
		{
			delete[] game.apples;
			game.apples = nullptr;
		}

		int howMany = game.fixedAppleCount;

		if (game.gameMode & MODE_RANDOM_APPLES)
		{
			howMany = 5 + (rand() % 50);
			if (game.gameMode & MODE_MANY_APPLES)
				howMany = 30 + (rand()% 31);
		}
		else if (game.gameMode & MODE_MANY_APPLES)
		{
			howMany = 40 + (rand() % 11);
		}
		else if (game.gameMode & MODE_NORMAL_APPLES)
		{
			howMany = 12 + (rand() % 6);
		}
		game.numApples = howMany;
		game.apples = new Apple[game.numApples];

		for (int i = 0; i < game.numApples; ++i)
		{
			InitApple(game.apples[i]);
		}

		game.player.speed = INITIAL_SPEED;
	}

	void ProcessSelectionMenu(Game& game, sf::Event event)
	{
		if (game.state != GameState::ModeSelection || event.type != sf::Event::KeyPressed)
			return;

		switch (event.key.code)
		{
		case sf::Keyboard::Num1: case sf::Keyboard::Numpad1: game.gameMode ^= MODE_NORMAL_APPLES; break;
		case sf::Keyboard::Num2: case sf::Keyboard::Numpad2: game.gameMode ^= MODE_RANDOM_APPLES; break;
		case sf::Keyboard::Num3: case sf::Keyboard::Numpad3: game.gameMode ^= MODE_MANY_APPLES; break;
		case sf::Keyboard::Num4: case sf::Keyboard::Numpad4: game.gameMode ^= MODE_ACCELERATION; break;
		case sf::Keyboard::Num5: case sf::Keyboard::Numpad5: game.gameMode ^= MODE_WITHOUT_ACCELERATION; break;
		case sf::Keyboard::Enter:
			game.state = GameState::Playing;
			RestartGame(game);
			break;
		}
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		if (game.state != GameState::Playing)
			return;

		// Update game state
		if (!game.isGameFinished)
		{
			ScoreTextGame(game.text, game);
			PlayerControl(game.player, deltaTime);
			CollisionWithApple(game.apples, game.numApples, game.player, game.numEatenApples, game.gameMode);
			CollisionWithRock(game.rock, game.player, game.isGameFinished, game.timeSinceGameFinish);
			CollisionPlayerWithBounds(game.player, game.isGameFinished, game.timeSinceGameFinish);
		
		}
		else
		{
			game.timeSinceGameFinish += deltaTime;

			if (game.timeSinceGameFinish <= PAUSE_LENGTH)
			{
				game.background.setFillColor(sf::Color::Red);
			}
			else
			{
				game.background.setFillColor(sf::Color::Black);

				game.leaderboard.UpdatePlayerScore(game.playerName, game.numEatenApples, false);
				LeaderboardTextGame(game.text, game);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					RestartGame(game);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					game.isGameFinished = false;
					game.state = GameState::ModeSelection;
				}
			}
			
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.state != GameState::Playing)
			return;

		window.draw(game.background);
		DrawPlayer(game.player,window);
		DrawApple(game.apples, game.numApples, window);
		DrawRock(game.rock, window);
		DrawStaticText(game.text, window);
		
		if (game.isGameFinished)
		{
			DrawDinamicText(game.text, window);
			DrawLeaderboardText(game.text, window);
		}
	}

	void DeinializeGame(Game& game)
	{
		if (game.apples != nullptr)
		{
			delete[] game.apples;
			game.apples = nullptr;
		}
	}
}
