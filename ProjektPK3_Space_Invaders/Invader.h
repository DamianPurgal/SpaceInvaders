#pragma once
#include <SFML/Graphics.hpp>
#include "ShootingObject.h"

class Invader : public ShootingObject
{
public:
	enum class invaderType
	{
		brain = 0,
		crab = 1,
		octopus = 2
	};
private:
	bool alive;
	invaderType type;
public:
	Invader(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity, invaderType pType = invaderType::brain, bool pAlive = 1);
	float getHeight();
	void onCollision();
	void draw() override;
	void shoot();
	void Update(float deltaTime) {};
	void save(std::ostream& stream);
	void load(std::istream& stream);
	bool isAlive();
	bool isColliding(GraphicObjectWithCollision& testedObject);
};

