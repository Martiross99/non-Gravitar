#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "lifeScore.h"
#include "menu.h"


lifeScore::lifeScore() : life(std::string("LIFE")) {

	livesLeft = 3;
	lives.setPointCount(8);

	lives.setPoint(0, sf::Vector2f(0, 5));
	lives.setPoint(1, sf::Vector2f(10, 15));
	lives.setPoint(2, sf::Vector2f(20, 5));
	lives.setPoint(3, sf::Vector2f(17, 0));
	lives.setPoint(4, sf::Vector2f(13, 0));
	lives.setPoint(5, sf::Vector2f(10, 5));
	lives.setPoint(6, sf::Vector2f(7, 0));
	lives.setPoint(7, sf::Vector2f(3, 0));
	lives.setFillColor(sf::Color::Red);


	contorno.setSize(sf::Vector2f(85, 20));
	contorno.setFillColor(sf::Color::Black);
	contorno.setOutlineColor(sf::Color::White);
	contorno.setOutlineThickness(2);

	lifeBar.setSize(sf::Vector2f(80, 15));
	lifeBar.setFillColor(sf::Color::White);
}

lifeScore::~lifeScore()
{
}

int lifeScore::getLives() {
	return livesLeft;
}



//MODIFICA PER LA SCHERMATA GAME-OVER E INIZIO NUOVA PARTITA
void lifeScore::decreaseLives() {
	livesLeft = livesLeft - 1;
}


float lifeScore::getSize() {
	return(lifeBar.getSize().x);
}

void lifeScore::setSize(float x) {
	lifeBar.setSize(sf::Vector2f(this->getSize() + x, 15));
}

void lifeScore::draw(sf::RenderWindow& window) {
	sf::View view = window.getView();

	for (int i = 0; i < livesLeft; i++) {
		lives.setPosition(view.getCenter().x + 600 - i * 30, view.getCenter().y - 340);
		window.draw(lives);
	}

	sf::Vector2f viewSize = window.getView().getCenter();

	contorno.setPosition(viewSize.x - 570, viewSize.y - 315);
	window.draw(contorno);

	lifeBar.setPosition(contorno.getPosition().x + 2.5, contorno.getPosition().y + 2.5);
	window.draw(lifeBar);

	life.draw(window, sf::Vector2f(630, 315));

}