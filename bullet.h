#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "object.h"

class bullet : public object {

	public:
		bullet();   
		bullet(sf::Vector2f dir);
		~bullet();

		void setPosition(sf::Vector2f newPos);   

		sf::Vector2f getPosition();

		sf::FloatRect getBounds();

		void fire();
		void  fireDir(int x, int y);        //set bullet's direction when an object is firing
		void fireSpeed(bool add, int speed);  //change the movement of the bullet if the object which is firing is moving

		void setDirection(sf::Vector2f dir);
	    sf::Vector2f getDirection();

		bool checkCollision(sf::Vector2f(pos));  //ritorna true se il proiettile colpisce la navicella

		void draw(sf::RenderWindow& window);

	protected:
		sf::RectangleShape proiettile;
		sf::Vector2f direction;
};

