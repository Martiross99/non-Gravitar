#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

#include "menu.h"

menu::menu()
	: gameWindow({ 1280, 720 }, "nongravitar"), titolo("NonGravitar"), avvio("PRESS ENTER TO PLAY\n\nYOU CAN PRESS P ANYTIME TO PAUSE")
{

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
	if (gameReturn == -1)	//se è un valore positivo vuol dire che il while di game.cpp si
		//è interrotto perché l'utente ha chiuso la finestra, in caso contrario è perché è morto
		closeWindow = true;
	else {    //se il return non è -1 allora vuol dire che il return contiene i punti e il
  //gioco si è concluso perché l'utente ha finito le vite
		gameOver = true;
	}

	play = false; //in ogni caso il gioco è finito
}


void menu::display() {

	if (!play && !gameOver && !closeWindow) { //non sta giocando e non ha perso: viene mostrato il menù principale

		gameWindow.setView(gameView);

		titolo.setTitle();
		titolo.draw(gameWindow, sf::Vector2f(173, 80));
		avvio.draw(gameWindow, sf::Vector2f(170, 10));

		gameWindow.display();

	}
	else if (!play && gameOver) {   //non sta giocando perché ha perso: viene mostrato "game over" e il
  //punteggio ottenuto nella partita -> dà la possibilità di iniziare una nuova partita

		gameWindow.setView(gameView);

		GameOver.setTitle();
		GameOver.draw(gameWindow, sf::Vector2f(380, 250));
		newGame.draw(gameWindow, sf::Vector2f(430, 100));
		Points.updateText(std::string("SCORE " + std::to_string(gameReturn)));
		Points.draw(gameWindow, sf::Vector2f(270, 170));

		gameWindow.display();

	}

}