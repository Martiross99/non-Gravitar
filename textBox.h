#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

class textBox {

public:

	textBox(std::string txt);
	textBox();
	~textBox();

	void updateText(std::string txt);
	//void updateText(std::string string);

	void draw(sf::RenderWindow& window, sf::Vector2f pos);
	void draw1(sf::RenderWindow& window);

	void setPosition(sf::Vector2f(pos));
	void setSize(int size);
	void setColor(sf::Color color);
	void setTitle();
	void setFont();
	void rotate(double rotation);

	std::string getText();

private:

	sf::Text testo;
	sf::Font font;
};
