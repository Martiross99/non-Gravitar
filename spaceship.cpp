#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>

#include "spaceship.h"
#include "game.h"

#define PI 3.14159265

spaceship::spaceship() : carburante() {      //design spaceShip

	/*Navicella.setPointCount(44);

	Navicella.setPoint(0, sf::Vector2f(0, 20));
	Navicella.setPoint(1, sf::Vector2f(5, 25));
	Navicella.setPoint(2, sf::Vector2f(10, 25));
	Navicella.setPoint(3, sf::Vector2f(15, 30));
	Navicella.setPoint(4, sf::Vector2f(20, 30));
	Navicella.setPoint(5, sf::Vector2f(10, 40));
	Navicella.setPoint(6, sf::Vector2f(25, 40));
	Navicella.setPoint(7, sf::Vector2f(38, 27));
	Navicella.setPoint(8, sf::Vector2f(30, 29));
	Navicella.setPoint(9, sf::Vector2f(15, 30));
	Navicella.setPoint(10, sf::Vector2f(20, 30));
	Navicella.setPoint(11, sf::Vector2f(10, 40));
	Navicella.setPoint(12, sf::Vector2f(25, 40));
	Navicella.setPoint(13, sf::Vector2f(38, 27));

	Navicella.setPoint(14, sf::Vector2f(40, 27));
	Navicella.setPoint(15, sf::Vector2f(44, 26));
	Navicella.setPoint(16, sf::Vector2f(46, 25));
	Navicella.setPoint(17, sf::Vector2f(48, 24));
	Navicella.setPoint(18, sf::Vector2f(50, 23));
	Navicella.setPoint(19, sf::Vector2f(52, 22));
	Navicella.setPoint(20, sf::Vector2f(54, 21.5));

	Navicella.setPoint(21, sf::Vector2f(55, 21));
	Navicella.setPoint(22, sf::Vector2f(55.5, 20.5));
	Navicella.setPoint(23, sf::Vector2f(56, 20));
	Navicella.setPoint(24, sf::Vector2f(55.5, 19.5));
	Navicella.setPoint(25, sf::Vector2f(55, 19));
	Navicella.setPoint(26, sf::Vector2f(54, 18.5));

	Navicella.setPoint(27, sf::Vector2f(52, 18));
	Navicella.setPoint(28, sf::Vector2f(50, 17));
	Navicella.setPoint(29, sf::Vector2f(48, 16));
	Navicella.setPoint(30, sf::Vector2f(46, 15));
	Navicella.setPoint(31, sf::Vector2f(44, 14));
	Navicella.setPoint(32, sf::Vector2f(42, 13));
	Navicella.setPoint(33, sf::Vector2f(38, 13));

	Navicella.setPoint(34, sf::Vector2f(25, 0));
	Navicella.setPoint(35, sf::Vector2f(10, 0));
	Navicella.setPoint(36, sf::Vector2f(20, 10));
	Navicella.setPoint(37, sf::Vector2f(10, 0));
	Navicella.setPoint(38, sf::Vector2f(25, 0));
	Navicella.setPoint(39, sf::Vector2f(38, 13));
	Navicella.setPoint(40, sf::Vector2f(30, 11));
	Navicella.setPoint(41, sf::Vector2f(15, 10));
	Navicella.setPoint(42, sf::Vector2f(10, 15));
	Navicella.setPoint(43, sf::Vector2f(5, 15));*/

	double 
	X[43] = {5, 7.5, 11.5, 16.5, 6.5, 22.5, 30, 16.5, 6.5, 22.5, 30, 38, 40, 44, 46, 48, 50, 52, 54, 55, 55.5, 56, 55.5, 55, 54, 52, 50, 
		48, 46, 44, 40, 38, 30, 21.5, 6.5, 16.5, 30, 21.5, 6.5, 16.5, 11.5, 7.5, 5 }, 
	Y[43] = {20, 25, 25, 30, 35, 38.5, 30, 30, 35, 38.5, 30, 27, 27, 26, 25, 24, 23, 22, 21.5, 21, 20.5, 20, 19.5, 19, 18.5,18, 17, 16, 15, 14, 
		13, 13, 10, 2.5, 5, 10, 10, 2.5, 5, 10, 15, 15, 20	};

	Navicella.setPointCount(43);

	for (int i = 0; i < 43; i++) {

		cout << i << ": " << X[i] << " " << Y[i] << "\n";
		Navicella.setPoint(i, sf::Vector2f(X[i], Y[i]));


	}



	Navicella.setFillColor(sf::Color::Black);
	Navicella.setOutlineThickness(2);
	Navicella.setOutlineColor(sf::Color::White);
	Navicella.setPosition(sf::Vector2f(640, 50));

	float originX = (Navicella.getPoint(0).x + Navicella.getPoint(23).x) / 2;
	float originY = (Navicella.getPoint(11).y - Navicella.getPoint(35).y) / 2;
	Navicella.setOrigin(sf::Vector2f(originX, originY));

	firePoint = Navicella.getPosition();

	direction = sf::Vector2f(0, 0);
	IsMoving = false;
	IsFiring = false;
	IsRotatingL = false;
	IsRotatingR = false;
    raggioT = false;

	line1.setSize(sf::Vector2f(2, 80));
	line2.setSize(sf::Vector2f(2, 80));
	line1.setFillColor(sf::Color(255, 153, 102));
	line2.setFillColor(sf::Color(255, 153, 102));
	line1.setRotation(10);
	line2.setRotation(-10);
}

spaceship::~spaceship()
{
}

void spaceship::handleEvents(sf::Keyboard::Key key, bool isPressed) {

    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down)
		IsMoving = isPressed;
	else if(key == sf::Keyboard::Right)
		IsRotatingR = isPressed;
	else if (key == sf::Keyboard::Left)
		IsRotatingL = isPressed;
	else if (key == sf::Keyboard::Space)
		IsFiring = isPressed;
	else if (key == sf::Keyboard::Tab)
		raggioT = isPressed;

}

bool spaceship::move(sf::View view) {

	sf::Vector2f dir (0.f, 0.f);

	if ((IsMoving) && (this->getPosition().x > (view.getCenter().x - 637))) {
		dir.x = direction.x * 4;
		dir.y = direction.y * 4;
	}

	if ((IsRotatingL)) {
		Navicella.rotate(-2);	
		direction = sf::Vector2f(cos(-2*PI / 180), sin(-2*PI / 180));		
	}

	if ((IsRotatingR)) {
		Navicella.rotate(2);
		direction = sf::Vector2f(cos(2 * PI / 180), sin(2 * PI / 180));
	}

	Navicella.move(dir);   //muove la navicella

	return(IsMoving);
}

void spaceship::update(sf::Time time) {

	direction = sf::Vector2f(cos(Navicella.getRotation()*PI / 180), sin(Navicella.getRotation()*PI / 180));
	firePoint =  sf::Vector2f(Navicella.getPosition().x + 28*direction.x, Navicella.getPosition().y + 28*direction.y);

	if (IsFiring && time.asSeconds() > 0.20) {
		bullet newBullet(direction);
		newBullet.setPosition(this->getFirePoint());
		bulletVect.push_back(newBullet);
	}

	for (int i = 0; i < bulletVect.size(); i++) {                           //ad una certa distanza dalla navicella i proiettili vengono eliminati
		if (bulletVect[i].getPosition().y > Navicella.getPosition().y + 350)  bulletVect.erase(bulletVect.begin() + i);
	}

	if (raggioT) {
		line1.setPosition(this->getFirePoint());
		line2.setPosition(this->getFirePoint());
	}

}


//float navicella::getX() {
//	return Navicella.getPosition().x;  //ritorna il valore x del centro della navicella
//}
//
//float navicella::getY() {
//	return Navicella.getPosition().y;   //ritorna il valore y del centro della navicella
//}

sf::FloatRect spaceship::getBounds() {
	return(Navicella.getGlobalBounds());
}

int spaceship::getLives() {
	return puntiVita.getLives();
}

void spaceship::setLives(int n) {
	puntiVita.setLives(n);
}

void spaceship::decreaseLives() {
	puntiVita.decreaseLives();
}


void spaceship::decreaseLifePoints() {
	if (puntiVita.getSize() > 0) {
		this->puntiVita.setSize(-1);
	}
	else {
		this->decreaseLives();
		puntiVita.setSize(+80);
	}
}

bool spaceship::decreaseFuel() {
	return(carburante.decrease()); //ritorna false se il carburante � finito
}

void spaceship::increaseFuel(float x) {
	carburante.increase(x);
}

void spaceship::setPosition(sf::Vector2f newPos) {
	Navicella.setPosition(newPos);
}

sf::Vector2f spaceship::getPosition() {
	return(Navicella.getPosition());
}

int spaceship::getRotation() {
	return(Navicella.getRotation());
}

void spaceship::draw(sf::RenderWindow & window) {

	window.draw(Navicella);
	
	puntiVita.draw(window);
	carburante.draw(window, sf::Vector2f(570, 280));


	if (raggioT) {                 //se il raggio traente � attivo lo disegna
		window.draw(line1);
		window.draw(line2);
	}

	for (int i = 0; i < bulletVect.size(); i++) {
			bulletVect[i].draw(window);
			bulletVect[i].fireSpeed(IsMoving, 4);
	}

}


bool spaceship::isActive() {   
	return(raggioT);
}

void spaceship::disactivate() {
	raggioT = false;
}

void spaceship::setRaggio(float y1, float y2) {
	line1.setSize(sf::Vector2f(2, y1));
	line2.setSize(sf::Vector2f(2, y2));
}

sf::Vector2f spaceship::getFirePoint() {      
	return(firePoint);
}


std::vector<bullet> spaceship::getBullets() {
	return(bulletVect);
}

void spaceship::eraseBullet() {
	if (!bulletVect.empty())
		bulletVect.erase(bulletVect.begin());
}

