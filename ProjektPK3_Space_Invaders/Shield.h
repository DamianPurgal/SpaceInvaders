#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObjectWithCollision.h"
class Shield : public GraphicObjectWithCollision
{
protected:
private:
	int health = 5;
	bool isAlive();
public:
	Shield(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, int pHealth = 5);
	void onCollision();
	void move(sf::Vector2f shift) {};
	void draw();
	void Update(float deltaTime) {};
	void setActualTexture();
	void save(std::ostream& stream);
	void load(std::istream& stream);
	bool isColliding(GraphicObjectWithCollision& testedObject);

};

