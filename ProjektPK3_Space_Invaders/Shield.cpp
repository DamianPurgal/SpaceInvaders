#include "Shield.h"
#include "Game.h"

//---------------------------------------------------------------------

Shield::Shield(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, int pHealth)
	:GraphicObjectWithCollision(pPosition, pSize, pTexture, pGame),
	health(pHealth)
{
	setActualTexture();
}

//---------------------------------------------------------------------

bool Shield::isAlive()
{
	if (health > 0)
		return true;
	return false;
}

//---------------------------------------------------------------------

void Shield::draw()
{
	if (health > 0)
		game->getRenderWindow()->draw(shape);
}

//---------------------------------------------------------------------

void Shield::onCollision()
{
	if (health > 0)
	{
		health--;
		setActualTexture();
	}
}

//---------------------------------------------------------------------

bool Shield::isColliding(GraphicObjectWithCollision& pObject)
{
	if (health > 0)
	{
		if (this->getCollisionBox().intersects(pObject.getCollisionBox()))
		{
			onCollision();
			pObject.onCollision();
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------

void Shield::setActualTexture()
{
	int actualFrame = 5 - health;
	sf::Vector2u textureSize = texture.getSize();
	textureSize.x /= 5;
	shape.setTextureRect(sf::IntRect(actualFrame * textureSize.x, 0, textureSize.x, textureSize.y));
}

//---------------------------------------------------------------------

void Shield::save(std::ostream& stream)
{
	stream << health << endl;
}

//---------------------------------------------------------------------

void Shield::load(std::istream& stream)
{
	stream >> health;
	setActualTexture();
}

//---------------------------------------------------------------------