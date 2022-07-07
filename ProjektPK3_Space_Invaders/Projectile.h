#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObjectWithCollision.h"
#include "constant.h"
using namespace sf;
class Projectile : public GraphicObjectWithCollision
{
public:
	enum class moving_direction {
		up = -1,
		down = 1
	};
private:
	moving_direction mDirection;
	sf::Vector2f velocity;
public:
	Projectile(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, Vector2f pVelocity, moving_direction pDirection);
	void move(Vector2f shift);
	void draw();
	void Update(float deltaTime);
	void onCollision();
};

