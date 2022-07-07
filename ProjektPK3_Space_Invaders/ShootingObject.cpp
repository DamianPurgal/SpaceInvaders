#include "ShootingObject.h"

//---------------------------------------------------------------------

ShootingObject::ShootingObject(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity)
	:GraphicObjectWithCollision(pPosition, pSize, pTexture, pGame),
	velocity(pVelocity)
{
}

//---------------------------------------------------------------------

