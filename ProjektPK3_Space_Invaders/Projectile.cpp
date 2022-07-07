#include "Projectile.h"
#include "Game.h"

//---------------------------------------------------------------------

Projectile::Projectile(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, Vector2f pVelocity, moving_direction pDirection)
	:GraphicObjectWithCollision(pPosition, pSize, pTexture, pGame),
	velocity(pVelocity),
	mDirection(pDirection)
{
	switchTime = PROJECTILE_SWITCH_TIME;
}

//---------------------------------------------------------------------

void Projectile::move(Vector2f shift)
{
	bool isOutOfMap = false;
	if ((position.x + shift.x > 0) && (position.x + shift.x + PLAYER_WIDTH <= WINDOW_WIDTH))
		position.x += shift.x;
	else isOutOfMap = true;
	if ((position.y + shift.y > 0) && (position.y + shift.y + PLAYER_HEIGHT <= WINDOW_HEIGHT))
		position.y += shift.y;
	else isOutOfMap = true;
	shape.setPosition(position);
	if (isOutOfMap)
		game->removeObject(this);
}

//---------------------------------------------------------------------

void Projectile::draw()
{
	game->getRenderWindow()->draw(shape);
}

//---------------------------------------------------------------------

void Projectile::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		move({ 0 , velocity.y * float(mDirection) });
	}
}

//---------------------------------------------------------------------

void Projectile::onCollision()
{
	game->removeObject(this);
}

//---------------------------------------------------------------------