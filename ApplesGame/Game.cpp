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
	}

	void RestartGame(Game& game)
	{
		InitPlayer(game.player);

		ApplyGameMode(game);


		// Init rocks
		game.rocks.clear();
		game.rocks.reserve(NUM_ROCKS);
		for (int i = 0; i < NUM_ROCKS; ++i)
		{
			game.rocks.emplace_back();
			InitRock(game.rocks.back());
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
		game.apples.clear();

		int howMany = 10;

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

		game.apples.reserve(howMany);

		for (int i = 0; i < howMany; ++i)
		{
			game.apples.emplace_back();
			InitApple(game.apples.back());
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
			CollisionWithApple(game.apples, game.player, game.numEatenApples, game.gameMode);
			CollisionWithRock(game.rocks, game.player, game.isGameFinished, game.timeSinceGameFinish);
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
		DrawApple(game.apples, window);
		DrawRock(game.rocks, window);
		DrawStaticText(game.text, window);
		
		if (game.isGameFinished)
		{
			DrawDinamicText(game.text, window);
			DrawLeaderboardText(game.text, window);
		}
	}

	void DeinializeGame(Game& game)
	{
		game.apples.clear();
		game.rocks.clear();
	}
}
