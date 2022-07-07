#include "Squadron.h"

//---------------------------------------------------------------------

Squadron::Squadron(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, Game* pGame)
	:GraphicObjectWithCollision(pPosition, pSize, pTexture, pGame),
	mDirection(moving_direction::right),
	aliveInvaders(SQUADRON_COLUMNS* SQUADRON_ROWS)
{
	switchTime = SQUADRON_SWITCH_TIME;
}

//---------------------------------------------------------------------

Squadron::~Squadron()
{
	while (invaders.size() > 0)
	{
		while (invaders.back().size() > 0)
		{
			delete invaders.back().back();
			invaders.back().pop_back();
		}
		invaders.pop_back();
	}
}

//---------------------------------------------------------------------

float Squadron::getBottomPosOfSquadron()
{
	for (int i = SQUADRON_ROWS - 1; i >= 0; i--) {
		for (int j = 0; j < SQUADRON_COLUMNS; j++) {
			if (invaders[j][i]->isAlive())
				return invaders[j][i]->getHeight() + INVADER_HEIGHT;
		}
	}
	return 0;
}

//---------------------------------------------------------------------

int Squadron::getAliveInvaders()
{
	return aliveInvaders;
}

//---------------------------------------------------------------------

void Squadron::init()
{
	Invader::invaderType type;
	invaders.resize(SQUADRON_COLUMNS);
	for (int i = 0; i < SQUADRON_COLUMNS; i++) {
		for (int j = 0; j < SQUADRON_ROWS; j++) {
			if (j == 0)
				type = Invader::invaderType::octopus;
			else if (j < 3)
				type = Invader::invaderType::crab;
			else
				type = Invader::invaderType::brain;
			invaders[i].push_back(new Invader(
				{
					position.x + i * (INVADER_WIDTH + SQUADRON_SPACE_ROWS),
					position.y + j * (INVADER_HEIGHT + SQUADRON_SPACE_COLUMNS)
				},
				{ INVADER_WIDTH,INVADER_HEIGHT },
				texture,
				game,
				{ 0,0 },
				type
			));
		}
	}
}

//---------------------------------------------------------------------

void Squadron::decrementAliveInvaders(int inv)
{
	aliveInvaders -= inv;
}

//---------------------------------------------------------------------

void Squadron::draw()
{
	for (auto i : invaders)
	{
		for (auto j : i)
		{
			j->draw();
		}
	}
}

//---------------------------------------------------------------------

void Squadron::move(sf::Vector2f shift)
{
	if ((position.x + shift.x > 0) && (position.x + shift.x + SQUADRON_COLUMNS * (INVADER_WIDTH + SQUADRON_SPACE_ROWS) - SQUADRON_SPACE_ROWS <= WINDOW_WIDTH))
	{
		position.x += shift.x;
		moveInvaders(shift);
	}
	else
	{
		moveInvaders({ 0, SQUADRON_MOVE_DOWN });
		mDirection = (mDirection == moving_direction::right) ? moving_direction::left : moving_direction::right;
	}
}

//---------------------------------------------------------------------

void Squadron::moveInvaders(sf::Vector2f shift)
{
	for (auto i : invaders)
	{
		for (auto j : i)
		{
			j->move(shift);
		}
	}
}

//---------------------------------------------------------------------

void Squadron::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		move({ float(mDirection) * SQUADRON_MOVE_X,0 });
	}
}

//---------------------------------------------------------------------

void Squadron::randomInvaderShoot()
{
	if (aliveInvaders > 0)
	{
		srand(time(NULL));
		int random_column;
		for (;;)
		{
			random_column = rand() % SQUADRON_COLUMNS;
			for (auto it = invaders[random_column].rbegin(); it != invaders[random_column].rend(); it++)
				if ((*it)->isAlive())
				{
					(*it)->shoot();
					return;
				}
		}
	}
}

//---------------------------------------------------------------------

void Squadron::save(std::ostream& stream)
{
	stream << position.x << " " << position.y << " " << int(mDirection) << endl;
	for (auto i : invaders)
	{
		for (auto j : i)
		{
			j->save(stream);
			stream << " ";
		}
		stream << endl;
	}
}

//---------------------------------------------------------------------

void Squadron::load(std::istream& stream)
{
	int moving_d;
	stream >> position.x >> position.y >> moving_d;
	shape.setPosition(position);
	mDirection = Squadron::moving_direction(moving_d);
	for (auto i : invaders)
	{
		for (auto j : i)
		{
			j->load(stream);
			j->move(position);
		}
	}
}

//---------------------------------------------------------------------

bool Squadron::isColliding(GraphicObjectWithCollision& testedObject)
{
	for (int i = 0; i < SQUADRON_COLUMNS; i++) {
		for (int j = 0; j < SQUADRON_ROWS; j++) {
			if (invaders[i][j]->isAlive())
			{
				if (invaders[i][j]->isColliding(testedObject))
					return true;
			}
		}
	}
	return false;
}

//---------------------------------------------------------------------