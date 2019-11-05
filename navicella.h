#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "bullet.h"
#include "fuel.h"
#include "lifeScore.h"
#include "object.h"


class navicella : public object
{

public:

	navicella();            //constructor - design spaceShip
	~navicella();

	bool move(sf::View view);     //moving spaceShip

	void update(sf::Time time);

	void handleEvents(sf::Keyboard::Key key, bool isPressed);

	//float getX();      //get top-left point's coordinate on x axis
	//float getY();      

	sf::FloatRect getBounds(); 

	int getLives(); 

	void decreaseLives();          //decrementa le vite della navicella
	void decreaseLifePoints();     //decrementa la barra della vita 

	bool decreaseFuel();            //diminuisce la quantità di carburante in relazione al tempo trascorso
	void increaseFuel(float x);    //aumenta il carburante di un valore x uguale alla quantità contenuta nel serbatoio raccolto


	void setPosition(sf::Vector2f newPos);           //change spaceShip position

	sf::Vector2f getPosition();   //ritorna il punto centrale della navicella

	int getRotation();     //ritorna la rotazione della navicella rispetto all'asse x

	void draw(sf::RenderWindow& window);    

	bool isActive();   //ritorna true se è attivo il raggio traente

	void disactivate();     //disattiva il raggio traente

	void setRaggio(float y1, float y2);      //setta il raggio traente della lunghezza corretta, a seconda della distanza tra navicella e terreno

	sf::Vector2f getFirePoint();             //setta il firing point in basso e al centro


	std::vector<bullet> getBullets();

	void eraseBullet();         //delete bullets when they touch the ground
	
private:
	sf::ConvexShape   Navicella;

	std::vector<bullet> bulletVect;

	lifeScore puntiVita;
	fuel carburante;

	sf::Vector2f direction;

	bool IsMoving;
	bool IsRotatingL;
	bool IsRotatingR;

	sf::Vector2f firePoint;
	bool IsFiring;

	bool raggioT;      //raggio traente
	sf::RectangleShape line1, line2;  //linee che delimitano il raggio traente
};