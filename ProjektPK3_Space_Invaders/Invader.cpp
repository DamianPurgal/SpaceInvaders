#include "Invader.h"
#include "Game.h"

//---------------------------------------------------------------------

Invader::Invader(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity, invaderType pType, bool pAlive)
	:ShootingObject(pPosition, pSize, pTexture, pGame, pVelocity),
	alive(pAlive),
	type(pType)
{
	sf::Vector2u textureSize = pTexture.getSize();
	textureSize.x /= 3;
	shape.setTextureRect(sf::IntRect(int(type) * textureSize.x, 0, textureSize.x, textureSize.y));
}

//---------------------------------------------------------------------

bool Invader::isAlive()
{
	return alive;
}

//---------------------------------------------------------------------

float Invader::getHeight()
{
	return position.y;
}

//---------------------------------------------------------------------

void Invader::draw()
{
	if (alive)
	{
		game->getRenderWindow()->draw(shape);
	}
}

//---------------------------------------------------------------------

void Invader::shoot()
{
	Projectile* p = new Projectile(
		{ position.x - PROJECTILE_WIDTH / 2 + INVADER_WIDTH / 2, position.y + INVADER_HEIGHT },
		{ PROJECTILE_WIDTH,PROJECTILE_HEIGHT },
		projectileTexture,
		game,
		{ 0,PROJECTILE_SPEED },
		Projectile::moving_direction::down);

	game->addObject(p);
}


//---------------------------------------------------------------------

void Invader::save(std::ostream& stream)
{
	stream << alive;
}

//---------------------------------------------------------------------

void Invader::load(std::istream& stream)
{
	stream >> alive;
}

//---------------------------------------------------------------------

void Invader::onCollision()
{
	alive = false;
	game->invaderDeath();
}

//---------------------------------------------------------------------

bool Invader::isColliding(GraphicObjectWithCollision& testedObject)
{
	if (alive)
	{
		if (this->getCollisionBox().intersects(testedObject.getCollisionBox()))
		{
			onCollision();
			testedObject.onCollision();
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------