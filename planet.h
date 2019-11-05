#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <vector>
#include <ctime>

#include "terreno.h"
#include "textBox.h"


class planet {

public:

	planet(int nPianeti, int i);
	~planet();


	sf::FloatRect getBounds();

	sf::Vector2f getPosition();

	int getRaggio();


	void draw(sf::RenderWindow& window);

	void recharge();  //ricarica i proiettili dei bunker

	void update(navicella& spaceShip, int& x);   //aggiorna i bunker e i tank del pianeta e controlla tutto quanto avviene all'interno del pianeta

	bool checkBunker();

	void drawGround(sf::RenderWindow& window);   //disegna il terreno una volta che si è entrati in un pianeta



private:
	sf::CircleShape  pianeta;
	terreno ground;
	int raggio;
	std::vector<bunker*> bunkerVect;
	
	std::vector<tank> tankVect;
};
