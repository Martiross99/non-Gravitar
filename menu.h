#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"


class menu
{
public:
	menu();
	~menu();

	void draw();
	void initialize();
	void gestisciEventi();
	void aggiorna();
	void display();
	void closeGame(sf::RenderWindow& gameWindow);

	const sf::RenderWindow& getWindow();

private:
	sf::RenderWindow gameWindow;
	sf::View gameView;

	std::vector<sf::CircleShape> stelleVect;

	bool play;
	bool gameOver;
	bool closeWindow;
	int gameReturn;

	textBox titolo;
	textBox avvio;

	textBox GameOver = textBox("GAME OVER:");
	textBox newGame = textBox("PRESS ENTER TO PLAY A NEW GAME");
	textBox Points = textBox("SCORE ");
	//int finalPoints;

};
