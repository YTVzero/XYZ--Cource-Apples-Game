#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Text.h"

namespace CatAndApples
{
	enum class GameState
	{
		ModeSelection,
		Playing,
		GameOver
	};

	struct Game
	{
		Player player;
		Apple* apples = nullptr;
		int numApples = 0;
		Rock rock[NUM_ROCKS];

		// Global game data
		int numEatenApples = 0;
		sf::RectangleShape background;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		Text text;

		unsigned int gameMode = 0;
		int fixedAppleCount = 10;

		GameState state = GameState::ModeSelection;
	};

	void RestartGame(Game& game);
	void ApplyGameMode(Game& game);
	void InitGame(Game& game);
	void ProcessSelectionMenu(Game& game, sf::Event event);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinializeGame(Game& game);
}