#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bullet.h"


class bunker {

public:
	bunker();
	~bunker();

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	sf::FloatRect getBounds();

	void rotate(double rotation);

	virtual void recharge();    //ricarica il vettore dei proiettili

	bool update(sf::Vector2f(pos));  //aggiorna il vettore dei proiettili e ritorna true se uno di essi colpisce la navicella

	virtual void draw(sf::RenderWindow& window);

	void activate(bool isActive);   //attiva il bunker se la navicella è abbastanza vicina

	void decreaseLife();

	bool isAlive();

	virtual int getLifePoints();

protected:
	sf::RectangleShape forte;
	int puntiVita;
	bool firing;
	std::vector<bullet> bulletVect;
};


//sottoclassi della classe bunker

class blueBunker : public bunker
{

public:
	blueBunker();
	void recharge();    
	void draw(sf::RenderWindow& window);
	int getLifePoints();
};


class redBunker : public bunker
{

public:
	redBunker();
	void draw(sf::RenderWindow& window);
	void recharge();
	int getLifePoints();

};