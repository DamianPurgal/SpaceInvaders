#include "GraphicObject.h"

//---------------------------------------------------------------------

GraphicObject::GraphicObject(Vector2f pPosition, Vector2f pSize, Texture pTexture)
	:position(pPosition),
	texture(pTexture),
	totalTime(0),
	switchTime(2)
{
	shape.setSize(pSize);
	shape.setPosition(pPosition);
	shape.setTexture(&texture);
}

//---------------------------------------------------------------------

void GraphicObject::setPosition(Vector2f pPosition)
{
	position.x = pPosition.x;
	position.y = pPosition.y;
	shape.setPosition(position);
}

//---------------------------------------------------------------------