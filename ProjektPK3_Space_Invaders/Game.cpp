#include "Game.h"

//---------------------------------------------------------------------

Game::Game()
	:window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders")),
	score(0),
	player(nullptr),
	squadron(nullptr)
{
	font.loadFromFile("Rubik.ttf");
	score_text.setPosition({ SCORE_POS_WIDTH, SCORE_POS_HEIGHT });
	health_text.setPosition({ SCORE_POS_WIDTH, SCORE_POS_HEIGHT + FONT_SIZE });
	score_text.setFont(font);
	health_text.setFont(font);
	score_text.setCharacterSize(FONT_SIZE);
	health_text.setCharacterSize(FONT_SIZE);
	sf::Texture logoTexture;
	logoTexture.loadFromFile("SPACEINVADERS.png");
	menu = new Menu({ (WINDOW_WIDTH - float(logoTexture.getSize().x)) / 2,MENU_LOGO_HEIGHT }, { float(logoTexture.getSize().x),float(logoTexture.getSize().y) }, logoTexture, window);
}

//---------------------------------------------------------------------

Game::~Game()
{
	while (objects.size() > 0)
	{
		delete objects.back();
		objects.pop_back();
	}
	delete menu;
	delete window;
}

//---------------------------------------------------------------------

void Game::saveActualGame()
{
	ofstream Plik(SAVE_FILE);
	if (Plik)
	{
		Plik << score << endl;
		for (auto i : objects)
			i->save(Plik);
	}
	Plik.close();
}

//---------------------------------------------------------------------

void Game::loadGame()
{
	ifstream Plik(SAVE_FILE);
	if (Plik)
	{
		Plik >> score;
		for (auto i : objects)
			i->load(Plik);
	}
}

//---------------------------------------------------------------------

void Game::addObject(GraphicObjectWithCollision* objectToAdd)
{
	objects.push_back(objectToAdd);
}

//---------------------------------------------------------------------

void Game::removeObject(GraphicObjectWithCollision* objectToRemove)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (*it == objectToRemove)
		{
			objects.erase(it);
			delete objectToRemove;
			return;
		}
	}
}

//---------------------------------------------------------------------

sf::RenderWindow* Game::getRenderWindow()
{
	return window;
}

//---------------------------------------------------------------------

void Game::showEndScreen(string text)
{
	sf::Text endText;
	endText.setPosition({ WINDOW_WIDTH * 2 / 5, (WINDOW_HEIGHT - 50) / 2 });
	endText.setFont(font);
	endText.setCharacterSize(50);
	endText.setString(text);
	sf::Text endtTextButtonToClick;
	endtTextButtonToClick.setPosition({ WINDOW_WIDTH * 2 / 5, (WINDOW_HEIGHT) / 2 + 40 });
	endtTextButtonToClick.setFont(font);
	endtTextButtonToClick.setCharacterSize(20);
	endtTextButtonToClick.setString("Kliknij ENTER aby wyjsc");
	sf::Event event;

	while (window->isOpen())
	{
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			return;
		window->clear();
		window->draw(endText);
		window->draw(endtTextButtonToClick);
		window->display();
	}
}

//---------------------------------------------------------------------

void Game::handlePlayerMove(sf::Clock& playerMoveClock)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (playerMoveClock.getElapsedTime().asSeconds() >= PLAYER_MOVE_DELAY)
		{
			playerMoveClock.restart();
			player->move({ -PLAYER_SPEED,0 });
		}
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (playerMoveClock.getElapsedTime().asSeconds() >= PLAYER_MOVE_DELAY)
		{
			playerMoveClock.restart();
			player->move({ PLAYER_SPEED,0 });
		}
	}
}

//---------------------------------------------------------------------

void Game::handlePlayerShoot(sf::Clock& playerShootClock)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (playerShootClock.getElapsedTime().asSeconds() >= PLAYER_SHOOT_DELAY)
		{
			playerShootClock.restart();
			player->shoot();
		}
	}
}

//---------------------------------------------------------------------

void Game::handleSquadronShoot(sf::Clock& squadronShootClock)
{
	if (squadronShootClock.getElapsedTime().asSeconds() >= SQUADRON_SHOOT_DELAY)
	{
		squadronShootClock.restart();
		squadron->randomInvaderShoot();
	}
}

//---------------------------------------------------------------------

bool Game::isGameOver()
{
	if (squadron->getAliveInvaders() == 0)
	{
		showEndScreen("Wygrales");
		return true;
	}
	else if (player->getHealth() <= 0 || squadron->getBottomPosOfSquadron() >= SHIELD_POS_HEIGHT)
	{
		showEndScreen("Przegrales");
		return true;
	}
	return false;
}

//---------------------------------------------------------------------

GraphicObjectWithCollision* Game::operator+=(GraphicObjectWithCollision* objectToAdd)
{
	addObject(objectToAdd);
	return objectToAdd;
}

//---------------------------------------------------------------------

void Game::invaderDeath()
{
	addScore(INVADER_DEATH_SCORE);
	squadron->decrementAliveInvaders(1);
}

//---------------------------------------------------------------------

void Game::addScore(int score)
{
	this->score += score;
}

//---------------------------------------------------------------------

void Game::subScore(int score)
{
	this->score -= score;
}

//---------------------------------------------------------------------

void Game::drawUI()
{
	score_text.setString("Score: " + to_string(score));
	health_text.setString("Health: " + to_string(player->getHealth()));
	window->draw(score_text);
	window->draw(health_text);
}

//---------------------------------------------------------------------

void Game::init()
{
	sf::Texture SquadronTexture;
	SquadronTexture.loadFromFile("invaders.png");
	squadron = new Squadron({ SQUADRON_START_POS_WIDTH,SQUADRON_START_POS_HEIGHT }, { 0,0 }, SquadronTexture, this);
	squadron->init();
	(*this) += squadron;
	sf::Texture PlayerTexture;
	PlayerTexture.loadFromFile("player.png");
	player = new Player({ WINDOW_WIDTH / 2,SHIELD_POS_HEIGHT + SHIELD_HEIGHT + 50 }, { PLAYER_WIDTH, PLAYER_HEIGHT }, PlayerTexture, this, { 0,0 });
	(*this) += player;
	sf::Texture ShieldTexture;
	ShieldTexture.loadFromFile("shields.png");
	float shield_space = (WINDOW_WIDTH - SHIELD_AMOUNT * SHIELD_WIDTH) / (SHIELD_AMOUNT + 1);
	for (int i = 0; i < SHIELD_AMOUNT; i++)
	{
		Shield* shield = new Shield({ (i) * (SHIELD_WIDTH)+(i + 1) * (shield_space),SHIELD_POS_HEIGHT }, { SHIELD_WIDTH, SHIELD_HEIGHT }, ShieldTexture, this);
		(*this) += shield;
	}
}

//---------------------------------------------------------------------

void Game::startGame()
{
	int choosedButton = menu->showMenu();
	if (choosedButton == 0)
	{
		init();
		startGameLoop();
	}
	else if (choosedButton == 1)
	{
		init();
		loadGame();
		startGameLoop();
	}
}

//---------------------------------------------------------------------

void Game::startGameLoop()
{
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock playerShootClock;
	sf::Clock squadronShootClock;
	sf::Clock playerMoveClock;
	sf::Event event;
	playerShootClock.restart();
	squadronShootClock.restart();
	playerMoveClock.restart();
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();

		handlePlayerMove(playerMoveClock);
		handlePlayerShoot(playerShootClock);
		handleSquadronShoot(squadronShootClock);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			saveActualGame();

		for (unsigned int i = 0; i < objects.size(); i++)
			for (unsigned int j = i + 1; j < objects.size(); j++)
				objects[i]->isColliding(*objects[j]);

		for (auto i : objects)
			i->Update(deltaTime);
		window->clear();
		drawUI();
		for (auto i : objects)
			i->draw();
		window->display();

		if (isGameOver())
			break;
	}
}

//---------------------------------------------------------------------