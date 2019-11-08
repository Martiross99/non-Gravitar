#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "menu.h"

#define NSTELLE 1000

menu::menu()
	: gameWindow({ 1280, 720 }, "NonGravitar")
{
	loadTexts();

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
	showInst = false;
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
			if (event.key.code == sf::Keyboard::I)
				showInst = true;
			else if (event.key.code == sf::Keyboard::Return) {
				play = true;
				showInst = false;
			}

			break;

		case sf::Event::KeyReleased:

			break;

		case sf::Event::Closed:
			closeGame(gameWindow);

			break;
		}

	}

}

void menu::closeGame(sf::RenderWindow& gameWindow) {

	gameWindow.close();

}

void menu::initialize()
{
	game game(gameWindow);
	gameReturn = game.run(gameWindow);
	if (gameReturn == -1)	//se il return è -1 vuol dire che il gioco si è interrotto 
		//perché l'utente ha chiuso la finestra quindi viene chiamata la funzione di chiusura 
		//della finestra modificando il bool che ne gestisce la chiamata -> il gioco va concluso
		closeWindow = true;
	else {	//se il return non è -1 allora vuol dire che il return contiene i punti e il
		//gioco si è concluso perché l'utente ha finito le vite o il fuel
		gameOver = true;
	}

	play = false; //in ogni caso il gioco è finito
}


void menu::display() {

	if (!play && showInst && !gameOver && !closeWindow) {

		gameWindow.clear();

		//gameWindow.setView(gameView);

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		for (int i = 6; i < 13; i++) {
			allTB[i].setSize(35);
			allTB[i].draw(gameWindow, sf::Vector2f(250, 400 - (i * 40)));
		}

		gameWindow.display();
	}
	else if (!play && !showInst && !gameOver && !closeWindow) { //non sta giocando e non ha perso: viene mostrato il menù principale

		gameWindow.setView(gameView);

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		allTB[0].setTitle();
		allTB[0].draw(gameWindow, sf::Vector2f(173, 80));
		allTB[1].draw(gameWindow, sf::Vector2f(170, 20));
		allTB[2].draw(gameWindow, sf::Vector2f(170, 0));

		gameWindow.display();

	}
	else if (!play && gameOver) { //non sta giocando perché ha perso: viene mostrato "game over" e il
		//punteggio ottenuto nella partita -> dà la possibilità di iniziare una nuova partita

		gameWindow.setView(gameView);

		allTB[3].setTitle();

		allTB[5].updateText(std::string("SCORE " + std::to_string(gameReturn)));

		allTB[3].draw(gameWindow, sf::Vector2f(380, 250));
		allTB[4].draw(gameWindow, sf::Vector2f(430, 100));
		allTB[5].draw(gameWindow, sf::Vector2f(270, 170));

		gameWindow.display();

	}

}

void menu::loadTexts() {

	ifstream testo;
	string x;
	int i = 0;

	testo.open("texts.txt", ios::in);

	while (getline(testo, x)) {
		allTB[i] = textBox(x);
		i++;
	}

	testo.close();
}