#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

#include "menu.h"

#define NSTELLE 1000

menu::menu()
	: gameWindow({ 1280, 720 }, "nongravitar"), titolo("NonGravitar"), avvio("PRESS ENTER TO PLAY\n\nYOU CAN PRESS P ANYTIME TO PAUSE")
{

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
		stelleVect[i].setOutlineColor(sf::Color(89, 89, 89));
		stelleVect[i].setOutlineThickness(1);
	}

	play = false;
	gameOver = false;
	closeWindow = false;
	gameReturn = 0;

	gameWindow.setPosition({ gameWindow.getPosition().x,0 });
	gameWindow.setFramerateLimit(60);

	gameView = gameWindow.getView();
}

menu::~menu()
{
}

const sf::RenderWindow& menu::getWindow() {
	return(gameWindow);
}

void menu::draw() {

	while (gameWindow.isOpen()) {

		gestisciEventi();
		aggiorna();
		display();

	}

}


void menu::aggiorna() {

	if (play) {
		initialize();
	}
	else if (closeWindow)
		closeGame(gameWindow);
	else display();

}

void menu::gestisciEventi() {

	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Return)
				play = true;

			break;

		case sf::Event::KeyReleased:

			break;

		case sf::Event::Closed:
			closeGame(gameWindow);

			break;
		}

	}

}

void menu::closeGame(sf::RenderWindow & gameWindow) {

	gameWindow.close();

}

void menu::initialize()
{
	game game(gameWindow);
	gameReturn = game.run(gameWindow);
	if (gameReturn == -1)	//se � un valore positivo vuol dire che il while di game.cpp si
		//� interrotto perch� l'utente ha chiuso la finestra, in caso contrario � perch� � morto
		closeWindow = true;
	else {    //se il return non � -1 allora vuol dire che il return contiene i punti e il
  //gioco si � concluso perch� l'utente ha finito le vite
		gameOver = true;
	}

	play = false; //in ogni caso il gioco � finito
}


void menu::display() {

	if (!play && !gameOver && !closeWindow) { //non sta giocando e non ha perso: viene mostrato il men� principale

		gameWindow.setView(gameView);


		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}
		titolo.setTitle();
		titolo.draw(gameWindow, sf::Vector2f(173, 80));
		avvio.draw(gameWindow, sf::Vector2f(170, 10));

		gameWindow.display();

	}
	else if (!play && gameOver) {   //non sta giocando perch� ha perso: viene mostrato "game over" e il
  //punteggio ottenuto nella partita -> d� la possibilit� di iniziare una nuova partita

		gameWindow.setView(gameView);

		GameOver.setTitle();
		GameOver.draw(gameWindow, sf::Vector2f(380, 250));
		newGame.draw(gameWindow, sf::Vector2f(430, 100));
		Points.updateText(std::string("SCORE " + std::to_string(gameReturn)));
		Points.draw(gameWindow, sf::Vector2f(270, 170));

		gameWindow.display();

	}

}