#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Text.h"
#include "Leaderboard.h"
#include <vector>
#include <sstream>

namespace CatAndApples
{
	enum class GameState
	{
		ModeSelection,
		Playing,
		GameOver,
		PauseExit
	};

	struct Game
	{
		Player player;
		std::vector <Apple> apples;
		std::vector <Rock> rocks;

		// Global game data
		int numEatenApples = 0;
		sf::RectangleShape background;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		Text text;

		unsigned int gameMode = 0;

		GameState state = GameState::ModeSelection;
		GameState previousState = GameState::Playing;
		int pauseSelection = 0;

		Leaderboard leaderboard;
		std::string playerName = "Player";
	};

	void RestartGame(Game& game);
	void ApplyGameMode(Game& game);
	void InitGame(Game& game);
	void ProcessSelectionMenu(Game& game, sf::Event event);
	void ModeSelection(Game& game, sf::RenderWindow& window);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinializeGame(Game& game);
}