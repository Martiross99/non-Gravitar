#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bunker.h"


bunker::bunker() {
	forte.setSize(sf::Vector2f(60, 20));
	forte.setFillColor(sf::Color(168, 80, 50));
	puntiVita = 100;
	firing = false;
}


bunker::~bunker()
{
}

void bunker::setPosition(sf::Vector2f pos) {
	forte.setPosition(sf::Vector2f(pos.x, pos.y - 20));
}

sf::Vector2f bunker::getPosition() {
	return(sf::Vector2f(this->forte.getPosition().x + forte.getSize().x/2, this->forte.getPosition().y));
}

sf::FloatRect bunker::getBounds() {
	return forte.getGlobalBounds();
}

void bunker::rotate(double rotation) {
	forte.setRotation(rotation);
}

void bunker::recharge() {
	bullet newBullet;
	newBullet.setPosition(this->getPosition());
	bulletVect.push_back(newBullet);
}

bool bunker::update(sf::Vector2f(pos)) {

	bool colpito = false;

	for (int i = 0; i < bulletVect.size(); i++) {
		if (bulletVect[i].checkCollision(pos)) {          //se i proiettili colpiscono la navicella la funzione restituisce true
			bulletVect.erase(bulletVect.begin() + i);      //e i proiettili vengono eliminati
			colpito = true;                                   
		}

		else if (bulletVect[i].getPosition().y < this->getPosition().y - 600)    //ad una certa distanza dal bunker da quale sono stati
			bulletVect.erase(bulletVect.begin() + i);                       //sparati i proiettili vengono eliminati

	}
      
   return(colpito);
}

void bunker::draw(sf::RenderWindow & window) {      
	window.draw(forte);
}


void bunker::activate(bool isActive) {
	this->firing = isActive;
}


void bunker::decreaseLife() {
	if (puntiVita >= 1) {
		puntiVita--;
	}
}

bool bunker::isAlive() {
	return(puntiVita > 0);
}

int bunker::getLifePoints() {
	return(puntiVita);
}


//blueBunker

blueBunker::blueBunker() : bunker()
{
	forte.setSize(sf::Vector2f(40, 20));
	forte.setFillColor(sf::Color(50, 155, 168));
	puntiVita = 80;
	firing = false;
}

void blueBunker::draw(sf::RenderWindow& window) {
	bunker::draw(window);
	if (!bulletVect.empty()) {
		for (int i = 0; i < bulletVect.size(); i++) {
			if (firing) {
				bulletVect[i].draw(window);
				bulletVect[i].fire();
			}
		}
	}
}

void blueBunker::recharge() {
	bullet newBullet1(sf::Vector2f(2, -6));
	bullet newBullet2(sf::Vector2f(-2, -6));
	newBullet1.setPosition(this->getPosition()); newBullet2.setPosition(this->getPosition());
	bulletVect.push_back(newBullet1); bulletVect.push_back(newBullet2);
}



int blueBunker::getLifePoints() {
	return(80);
}


//redBunker

redBunker::redBunker() : bunker()
{
	forte.setSize(sf::Vector2f(60, 20));
	forte.setFillColor(sf::Color(168, 80, 50));
	puntiVita = 100;
	firing = false;
}


void redBunker::draw(sf::RenderWindow& window) {

	bunker::draw(window);

	sf::View view = window.getView();

	if (!bulletVect.empty()) {
		for (int i = 0; i < bulletVect.size(); i++) {
			if (firing) {
				bulletVect[i].draw(window);

				float dirX = -this->getPosition().x + view.getCenter().x ;
				float dirY = -this->getPosition().y + view.getCenter().y ;
				bulletVect[i].fireDir(dirX / 10, dirY / 10);
			}
		}
	}
}

void redBunker::recharge() {
	bunker::recharge();
}

int redBunker::getLifePoints() {
	return(100);
}