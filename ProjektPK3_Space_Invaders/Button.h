#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GraphicObject.h"
#include "constant.h"
using namespace sf;
class Button : public GraphicObject
{
private:
	RenderWindow* window;
	Text text;
	bool focused;
	Font font;
	void setActualTexture();
public:
	Button(Vector2f pPosition, Vector2f pSize, Texture pTexture, RenderWindow* pWindow, std::string pText, bool pFocused = false);
	bool isFocused();
	void setFocused(bool focus);
	void draw();
	void Update(float deltaTime) {};
};

