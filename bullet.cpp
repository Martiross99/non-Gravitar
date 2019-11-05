#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>


#include "bullet.h"
using namespace sf;

bullet::bullet() : direction(0,0) {
	proiettile.setSize(sf::Vector2f(2,2));
	proiettile.setFillColor(sf::Color::White);
}

bullet::bullet(sf::Vector2f dir) {
	proiettile.setSize(sf::Vector2f(2, 2));
	proiettile.setFillColor(sf::Color::White);
	direction.x = dir.x;
	direction.y = dir.y;
	proiettile.setOrigin(proiettile.getOrigin() + sf::Vector2f(1, 1));

}

bullet::~bullet()
{
}

void bullet::setPosition(sf::Vector2f newPos) {
	proiettile.setPosition(newPos);
}

sf::Vector2f bullet::getPosition() {
	return(proiettile.getPosition());
}

sf::FloatRect bullet::getBounds() {
	return(proiettile.getGlobalBounds());
}

void bullet::fire() {
	proiettile.move(direction);
}

void  bullet::fireDir(int x, int y) {  
	proiettile.move(x, y);
}

void bullet::fireSpeed(bool moving, int speed) {
	if(moving) proiettile.move(direction.x * (4+speed), direction.y * (4+speed));
	else proiettile.move(direction.x *4, direction.y *4);
}

void bullet::setDirection(sf::Vector2f dir) {
	direction = sf::Vector2f(dir.x, dir.y);
}

sf::Vector2f bullet::getDirection() {
	return this->direction;
}

bool bullet::checkCollision(sf::Vector2f(pos)) {

	if (fabsf(proiettile.getPosition().x - pos.x) < 20 && (proiettile.getPosition().y - pos.y) < 0) {
		return(true);
	}
	return(false);
}

void bullet::draw(sf::RenderWindow & window) {
	window.draw(proiettile);
}


