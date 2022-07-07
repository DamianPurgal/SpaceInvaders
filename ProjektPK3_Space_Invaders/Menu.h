#pragma once
#include <vector>
#include "Button.h"
#include "GraphicObject.h"
#include "constant.h"
using namespace std;
class Menu : public GraphicObject
{
private:
	vector<Button*> buttons;
	sf::RenderWindow* window;
public:
	Menu(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, sf::RenderWindow* pWindow);
	~Menu();
	void Update(float deltaTime) {};
	void draw();
	int showMenu(); //zwraca wybrany przycisk
};

