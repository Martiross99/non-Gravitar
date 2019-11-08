#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <random>

#include "game.h"

#define NSTELLE 1000

using namespace std;


game::game(sf::RenderWindow& gameWindow)
	: spaceShip(), pianetiVect(), score(std::string("SCORE 0"))
{
	view = gameWindow.getView();

	points = 0;
	isInside = -1;

	alive = true;
	close = false;
	pausa = false;

	nPianeti = rand() % 3 + 5;

	newSolarSystem();

	planetsLeft = pianetiVect.size();

	for (int i = 0; i < NSTELLE; i++) {
		int x = -1, y = -1;
		bool isOutside;
		do {
			isOutside = true;
			x = rand() % 1280;
			y = rand() % 720;

		} while (!isOutside);

		sf::CircleShape stella;
		stelleVect.push_back(stella);
		stelleVect[i].setPosition(x, y);
		stelleVect[i].setRadius(0.25);
		stelleVect[i].setFillColor(sf::Color::Black);
		stelleVect[i].setOutlineColor(sf::Color(255, 255, 179));
		stelleVect[i].setOutlineThickness(1);
	}

}

game::~game()
{
}

int game::run(sf::RenderWindow& gameWindow) //per� come passiamo il punteggio finale?
{
	while (alive && !close)	//esce se hai finito le vite o se hai chiuso la finestra
	{
		time = clock.getElapsedTime();
		close = processEvents(gameWindow);
		if (!pausa) {
			alive = update(gameWindow);
			render(gameWindow);
		}
		if (pausa) paused(gameWindow);
    }
    
	if (close) return(-1);
    else return(points);
}

void game::paused(sf::RenderWindow& gameWindow) { //viene mostrato "pause", non pu� pi� giocare
  //e viene data la possibilit� di riprendere a giocare

	gameWindow.setView(view);

	Tpausa.setTitle();
	Tpausa.draw(gameWindow, sf::Vector2f(173, 80));
	Treplay.draw(gameWindow, sf::Vector2f(170, 10));

	gameWindow.display();

}


bool game::processEvents(sf::RenderWindow & gameWindow)
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type) {

		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);

			return false;

			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);

			return false;

			break;

		case sf::Event::Closed:
			return true;

			break;
		}
	}

}

void game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) //gestisce la pausa e poi manda i movimenti al metodo della navicella
{
	if (key == sf::Keyboard::C && planetsLeft == 0)
		newSolarSystem();
	if (key == sf::Keyboard::P)
		pausa = true;
	else if (key == sf::Keyboard::Return)
		pausa = false;
	else spaceShip.handleEvents(key, isPressed);
}



bool game::update(sf::RenderWindow & gameWindow)
{

	if (spaceShip.getLives() < 0) alive = false;  

	else {                              //controlla di essere in gioco prima di esguire gli update

		planetsLeft = pianetiVect.size();

		score.updateText(std::string("SCORE " + std::to_string(points)));   //aggiorna il punteggio

		bool moving = spaceShip.move(view);  
		spaceShip.update(time); //aggiorna i valori della navicella
		

		if (isInside == -1) {            //fuori dai pianeti

			spaceShip.disactivate();      //raggio traente disattivato
			for (int i = 0; i < pianetiVect.size(); i++) {
				if ((spaceShip.getBounds()).intersects(pianetiVect[i].getBounds())) {
					isInside = i;
					spaceShip.setPosition(sf::Vector2f(640, 360));
					spaceShip.getBullets().clear();
				}
			}
		}

		//CONTROLLING THE VIEW WHEN YOU ARE INSIDE THE PLANET

		if (isInside != -1) {

				view.setCenter(spaceShip.getPosition());
				pianetiVect[isInside].update(spaceShip, points);  //controlla tutto quanto avviene all'interno del pianeta ed effettua gli aggiornamenti

				if (view.getCenter().x >= (pianetiVect[isInside].getRaggio() - 10) * 128 + (1280 / 2)) { //il raggio equivale alla lunghezza del terreno
					view.setCenter((1280 / 2), spaceShip.getPosition().y);
					spaceShip.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));
				}
				if (view.getCenter().x < (1280 / 2)) {
					view.setCenter((pianetiVect[isInside].getRaggio() - 10) * 128 + (1280 / 2) , spaceShip.getPosition().y);
					spaceShip.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y));
				}

				if (time.asSeconds() > 0.25) {
					pianetiVect[isInside].recharge();
					clock.restart();
				}
					
				if (pianetiVect[isInside].checkBunker()) {          //controlla se sono stati distrutti tutti i bunker
						spaceShip.setPosition(pianetiVect[isInside].getPosition());
						spaceShip.getBullets().clear();                          //elimina tutti i proiettili
						view.setCenter(sf::Vector2f(640, 360));
						pianetiVect.erase(pianetiVect.begin() + isInside);
						isInside = -1;
				}
		
				else view.setCenter(spaceShip.getPosition());  

				if (view.getCenter().y < 100) {                    //controlla l'uscita della navicella da un pianeta
					spaceShip.setPosition(sf::Vector2f(640, 50));
					view.setCenter(sf::Vector2f(640, 360));
					spaceShip.getBullets().clear();
					isInside = -1;
				}

	    }

	   if (moving != 0) {      //controls fuel drecreasement
		   if (!spaceShip.decreaseFuel()) { //controlla che la funzione decrease abbia portato a conclusione
			   spaceShip.setLives(-1);          // la sottrazione del fuel e in caso contrario chiude la partita
		   }
	   }
	}

	return(alive);
}

void game::render(sf::RenderWindow & gameWindow)
{
	gameWindow.clear();
	gameWindow.setView(view);

	if (isInside == -1) {
		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}
		for (int i = 0; i < pianetiVect.size(); i++) {
			pianetiVect[i].draw(gameWindow);
		}

		if (planetsLeft == 0 && alive) {
			gameWindow.setView(view);
			Tcomplimenti.draw(gameWindow, sf::Vector2f(173, 80));
		}
	}
	else pianetiVect[isInside].drawGround(gameWindow);

	spaceShip.draw(gameWindow);

	score.draw(gameWindow, sf::Vector2f(630, 350));

	gameWindow.display();
}

void game::newSolarSystem() {

	nPianeti = rand() % 3 + 5;

	//nPianeti = 1;

	for (int i = 0; i < nPianeti; i++) {
		planet newPlanet(nPianeti, i);
		pianetiVect.push_back(newPlanet);
	}
}