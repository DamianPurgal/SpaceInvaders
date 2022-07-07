#include "Player.h"
#include "Game.h"

//---------------------------------------------------------------------

Player::Player(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame, sf::Vector2f pVelocity, int pHealth)
	:ShootingObject(pPosition, pSize, pTexture, pGame, pVelocity),
	health(pHealth)
{
}

//---------------------------------------------------------------------

int Player::getHealth()
{
	return health;
}

//---------------------------------------------------------------------

void Player::draw()
{
	if (health > 0)
	{
		game->getRenderWindow()->draw(shape);
	}
}

//---------------------------------------------------------------------

void Player::shoot()
{
	Projectile* p = new Projectile({ position.x - PROJECTILE_WIDTH / 2 + PLAYER_WIDTH / 2 , position.y - PROJECTILE_HEIGHT }, { PROJECTILE_WIDTH,PROJECTILE_HEIGHT }, projectileTexture, game, { 0,PROJECTILE_SPEED }, Projectile::moving_direction::up);
	game->addObject(p);
}

//---------------------------------------------------------------------

void Player::move(sf::Vector2f shift)
{
	if ((position.x + shift.x > 0) && (position.x + shift.x + PLAYER_WIDTH <= WINDOW_WIDTH))
		position.x += shift.x;
	if ((position.y + shift.y > 0) && (position.y + shift.y + PLAYER_HEIGHT <= WINDOW_HEIGHT))
		position.y += shift.y;
	shape.setPosition(position);
}

//---------------------------------------------------------------------

void Player::save(std::ostream& stream)
{
	stream << health << " " << position.x << " " << position.y << endl;
}

//---------------------------------------------------------------------

void Player::load(std::istream& stream)
{
	stream >> health >> position.x >> position.y;
	shape.setPosition(position);
}

//---------------------------------------------------------------------

void Player::onCollision()
{
	if (health > 0)
	{
		health--;
		game->subScore(PLAYER_HEALTH_MINUS_SCORE);
	}
}

//---------------------------------------------------------------------
