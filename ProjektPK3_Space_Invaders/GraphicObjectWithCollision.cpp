#include "GraphicObjectWithCollision.h"

//---------------------------------------------------------------------

GraphicObjectWithCollision::GraphicObjectWithCollision(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame)
	:GraphicObject(pPosition, pSize, pTexture),
	game(pGame)
{
}

//---------------------------------------------------------------------

bool GraphicObjectWithCollision::isColliding(GraphicObjectWithCollision& testedObject)
{
	if (this->getCollisionBox().intersects(testedObject.getCollisionBox()))
	{
		this->onCollision();
		testedObject.onCollision();
		return true;
	}
	return false;
}

//---------------------------------------------------------------------

void GraphicObjectWithCollision::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
}

//---------------------------------------------------------------------

sf::FloatRect GraphicObjectWithCollision::getCollisionBox()
{
	return sf::FloatRect(shape.getPosition(), shape.getSize());
}

//---------------------------------------------------------------------
