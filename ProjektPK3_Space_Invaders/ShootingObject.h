#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObjectWithCollision.h"

class ShootingObject : public GraphicObjectWithCollision
{

protected:
	sf::Vector2f velocity;
	sf::Texture projectileTexture;
public:
	ShootingObject(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity);
	virtual void shoot() {};
	virtual void Update(float deltaTime) {};
};

