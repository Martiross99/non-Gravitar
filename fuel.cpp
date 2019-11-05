#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "fuel.h"


	fuel::fuel() : testo(std::string("FUEL")) {
		contorno.setSize(sf::Vector2f(85, 20));
		contorno.setFillColor(sf::Color::Black);
		contorno.setOutlineColor(sf::Color::White);
		contorno.setOutlineThickness(2);

		carburante.setSize(sf::Vector2f(80, 15));
		carburante.setFillColor(sf::Color::White);
	}

	fuel::~fuel()
	{
	}

	void fuel::draw(sf::RenderWindow& window, sf::Vector2f pos) {

		sf::Vector2f viewSize = window.getView().getCenter();

		contorno.setPosition(viewSize.x - pos.x, viewSize.y - pos.y);
		window.draw(contorno);

		carburante.setPosition(contorno.getPosition().x + 2.5, contorno.getPosition().y + 2.5);
		window.draw(carburante);

		testo.draw(window, sf::Vector2f(630, 280));

	}


	float fuel::getSize() {
		return carburante.getSize().x;
	}


	void fuel::increase(float x) {
		if (carburante.getSize().x + x > 80) carburante.setSize(sf::Vector2f(80, 15));
		else carburante.setSize(sf::Vector2f(carburante.getSize().x + x, 15));
	}

	bool fuel::decrease() {
		if (this->getSize() >= 0) {
			carburante.setSize(sf::Vector2f(this->getSize() - 0.05, 15));
			return(true);
		}
		else return(false);	    //ritorna false quando il carburante è finito e il gioco finisce
	}
