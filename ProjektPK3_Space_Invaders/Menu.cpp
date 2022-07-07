#include "Menu.h"

//---------------------------------------------------------------------

int Menu::showMenu()
{
	unsigned int actualButtonFocus = 0;
	buttons[actualButtonFocus]->setFocused(true);
	sf::Event event;

	while (window->isOpen())
	{
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			return actualButtonFocus;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			if (actualButtonFocus - 1 >= 0)
			{
				buttons[actualButtonFocus]->setFocused(false);
				actualButtonFocus--;
				buttons[actualButtonFocus]->setFocused(true);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			if (actualButtonFocus + 1 < buttons.size())
			{
				buttons[actualButtonFocus]->setFocused(false);
				actualButtonFocus++;
				buttons[actualButtonFocus]->setFocused(true);
			}
		}
		window->clear();
		draw();
		window->display();
	}
	return ERROR;
}

//---------------------------------------------------------------------

Menu::Menu(sf::Vector2f pPosition, sf::Vector2f pSize, sf::Texture pTexture, sf::RenderWindow* pWindow)
	:GraphicObject(pPosition, pSize, pTexture),
	window(pWindow)
{
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("button.png");
	buttons.push_back(new Button({ (WINDOW_WIDTH - BUTTON_WIDTH) / 2,shape.getPosition().y + shape.getSize().y + MENU_SPACING }, { BUTTON_WIDTH,BUTTON_HEIGHT }, buttonTexture, window, "START GAME"));
	buttons.push_back(new Button({ (WINDOW_WIDTH - BUTTON_WIDTH) / 2,shape.getPosition().y + shape.getSize().y + MENU_SPACING * 2 + BUTTON_HEIGHT }, { BUTTON_WIDTH,BUTTON_HEIGHT }, buttonTexture, window, "LOAD GAME"));
}

//---------------------------------------------------------------------

Menu::~Menu()
{
	while (buttons.size() > 0)
	{
		delete buttons.back();
		buttons.pop_back();
	}
}

//---------------------------------------------------------------------

void Menu::draw()
{
	window->draw(shape);
	for (auto i : buttons)
		i->draw();
}

//---------------------------------------------------------------------
