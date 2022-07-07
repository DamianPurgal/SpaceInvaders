#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObjectWithCollision.h"
#include <vector>
#include <iostream>
#include <ctime>
#include "Invader.h"
#include "constant.h"
using namespace std;

class Squadron : public GraphicObjectWithCollision
{
protected:
	enum class moving_direction {
		left = -1,
		right = 1
	};
	moving_direction mDirection;
	vector<vector<Invader*>> invaders;
	int aliveInvaders;
public:
	Squadron(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame);
	~Squadron();
	float getBottomPosOfSquadron();
	int getAliveInvaders();
	bool isColliding(GraphicObjectWithCollision& testedObject);
	void init();
	void decrementAliveInvaders(int amountOfInvaders);
	void draw();
	void move(sf::Vector2f shift);
	void moveInvaders(sf::Vector2f shift);
	void Update(float deltaTime);
	void randomInvaderShoot();
	void save(std::ostream& stream);
	void load(std::istream& stream);
};

