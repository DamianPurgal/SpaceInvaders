#pragma once
#include "ShootingObject.h"
#include "Projectile.h"
class Player : public ShootingObject
{
protected:
private:
	int health;
public:
	Player(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity, int pHealth = 3);
	int getHealth();
	void onCollision();
	void draw();
	void shoot();
	void move(sf::Vector2f shift);
	void Update(float deltaTime) {};
	void save(std::ostream& stream);
	void load(std::istream& stream);
};

