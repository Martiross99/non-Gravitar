#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include  "textBox.h"

textBox::textBox(std::string txt)  {

	testo.setString(txt);

	font.loadFromFile("LucidaSansRegular.ttf");

	//if (!font.loadFromFile("LucidaSansRegular.ttf"))
	//{
	//	std::cout << "Error loading file" << std::endl;

	//	system("pause");
	//}
	//else {
	//	testo.setFont(font);
	//}
	testo.setFont(font);
	testo.setCharacterSize(20);
	testo.setFillColor(sf::Color::White);
	testo.setPosition(sf::Vector2f(10, 10));
	testo.setStyle(sf::Text::Style::Bold);

}

textBox::~textBox()
{
}

void textBox::updateText(std::string txt) {
	testo.setString(txt);
}


void textBox::draw(sf::RenderWindow& window, sf::Vector2f pos) {

	sf::Vector2f viewSize = window.getView().getCenter();

	testo.setPosition(viewSize.x - pos.x, viewSize.y - pos.y);

	window.draw(testo);

}

void textBox::draw1(sf::RenderWindow& window) {
	window.draw(testo);
}

void textBox::setTitle() {
	testo.setCharacterSize(50);
	testo.setFillColor(sf::Color::Red);
}

void textBox::setPosition(sf::Vector2f(pos)) {
	testo.setPosition(pos);
}

void textBox::setSize(int size) {
	testo.setCharacterSize(size);
}

void textBox::setColor(sf::Color color) {
	testo.setFillColor(color);
}

void textBox::setFont() {
	font.loadFromFile("LucidaSansRegular.ttf");
	testo.setFont(font);
}

void textBox::rotate(double rotation) {
	testo.rotate(rotation);
}