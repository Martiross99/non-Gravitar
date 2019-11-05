#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "tank.h"



tank::tank() : testo("F ") {
	serbatoio.setSize(sf::Vector2f(40, 15));
	serbatoio.setOutlineColor(sf::Color::Black);
	serbatoio.setFillColor(sf::Color(184, 183, 180));
	serbatoio.setOutlineThickness(1.0);
	testo.setSize(14);
	testo.setColor(sf::Color::Black);

	this->type = rand() % 2;
	if (type == 0) {
		quantity = 15;
		testo.updateText(" F 2L");
	}
	else {
		quantity = 30;
		testo.updateText(" F 4L");
	}
}

tank::~tank()
{
}

void tank::draw(sf::RenderWindow& window) {
	window.draw(serbatoio);
	testo.draw1(window);
}

void tank::setPosition(sf::Vector2f pos) {
	serbatoio.setPosition(sf::Vector2f(pos.x, pos.y - 15));
	testo.setPosition(serbatoio.getPosition());
}

sf::Vector2f tank::getPosition() {
	return(serbatoio.getPosition());
}

void tank::rotate(double rotation) {
	serbatoio.setRotation(rotation);
	testo.rotate(rotation);
}

float tank::getQuantity() {
	return(quantity);
}

void tank::setQuantity(float x) {
	quantity = x;
}

int tank::getType() {
	return type;
}

void tank::setColor() {
	serbatoio.setFillColor(sf::Color::Black);
	testo.setFont();
	testo.setColor(sf::Color::White);
	serbatoio.setOutlineColor(sf::Color::White);
}

void tank::update() {
	testo.setFont();
}