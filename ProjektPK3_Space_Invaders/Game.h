#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "constant.h"
#include "Squadron.h"
#include "GraphicObjectWithCollision.h"
#include "Player.h"
#include "Shield.h"
#include "Menu.h"
using namespace std;
class Game
{
private:
	Menu* menu;
	Squadron* squadron;
	Player* player;
	vector<GraphicObjectWithCollision*> objects;
	int score;
	sf::Font font;
	sf::Text score_text;
	sf::Text health_text;
	sf::RenderWindow* window;
private:
	void saveActualGame();
	void loadGame();
	void init();
	void drawUI();
	void startGameLoop();
	void showEndScreen(string text);
	void handlePlayerMove(sf::Clock& playerMoveClock);
	void handlePlayerShoot(sf::Clock& playerShootClock);
	void handleSquadronShoot(sf::Clock& squadronShootClock);
	bool isGameOver();
	GraphicObjectWithCollision* operator+=(GraphicObjectWithCollision* objectToAdd);
public:
	Game();
	~Game();
	sf::RenderWindow* getRenderWindow();
	void addObject(GraphicObjectWithCollision* objectToAdd);
	void removeObject(GraphicObjectWithCollision* objectToRemove);
	void invaderDeath();
	void addScore(int score);
	void subScore(int score);
	void startGame();
};