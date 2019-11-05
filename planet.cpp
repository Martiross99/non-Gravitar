#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <cmath>

#include "planet.h"


planet::planet(int nPianeti, int nCorrente) : ground(nCorrente) {

	raggio = (rand() % 16 + 35);
	this->ground.initTerrain(raggio, nCorrente);
	pianeta.setRadius(raggio);
	pianeta.setFillColor(sf::Color::Black);
	pianeta.setOutlineColor(sf::Color::White);
	pianeta.setOutlineThickness(2);

	auto posX = nCorrente * (1280 / nPianeti) + rand() % ((1280 / nPianeti - raggio * 2) - 20) + 10;
	auto posY = (rand()*nCorrente)% 510 + 120;

	pianeta.setPosition(posX, posY);

	int x = (raggio - 16);
	for (int i = 0; i < (x / 3) - 1; i++) {

		bunker* newBunker;

		if(rand() % 2 == 0)  newBunker = new redBunker;
		else  newBunker = new blueBunker;

		bunkerVect.push_back(newBunker);
	}
	

	for (int i = 0; i < (x / 4) - 1; i++) {
		tank newTank;
		tankVect.push_back(newTank);
	}

	if (!bunkerVect.empty() && !tankVect.empty())
		ground.setBunker(bunkerVect);                //posiziona i bunker sul terreno

	if (!tankVect.empty());               //posiziona i serbatoi sul terreno
		ground.setTank(tankVect);

}

planet::~planet()
{
}


sf::FloatRect planet::getBounds() {
	return pianeta.getGlobalBounds();
}

sf::Vector2f planet::getPosition() {
	return(pianeta.getPosition());
}

int planet::getRaggio() {
	return raggio;
}


void planet::draw(sf::RenderWindow & window) {
	window.draw(pianeta);
}

void planet::recharge() {
	for (int i = 0; i < bunkerVect.size(); i++) {
		bunkerVect[i]->recharge();                           //ricarica il vettore proiettili del bunker
	}
}

void planet::update(navicella& spaceShip, int& points) {

	ground.update();

	for (int i = 0; i < tankVect.size(); i++) {
		tankVect[i].update();

		if ((fabsf(spaceShip.getFirePoint().x - (tankVect[i].getPosition().x + 20)) < 30) && (spaceShip.isActive())) {
			spaceShip.increaseFuel(tankVect[i].getQuantity());
			tankVect[i].setColor();
			tankVect[i].setQuantity(0);  //azzera il carburante nella tanica
		}
	}

	std::vector<bullet> bulletVect = spaceShip.getBullets();

	if (!bulletVect.empty()) {                             //controlla le collisioni dei proiettili sparati dalla navicella con il terreno
		for (int i = 0; i < bulletVect.size(); i++) {
			if(bulletVect.size() > 2)
		std::cout << bulletVect[0].getDirection().x << std::endl; // "  " << bulletVect[0].getPosition().y << " " << bulletVect[0].getDirection().x << "  " << bulletVect[0].getDirection().y << std::endl;
		   if (ground.collision(sf::Vector2f(bulletVect[i].getPosition().x + bulletVect[i].getDirection().x * 4, bulletVect[i].getPosition().y + bulletVect[i].getDirection().y * 4))< 5)  spaceShip.eraseBullet();

		}
	}

	//controlla le collisioni della navicella e del raggio traente

	float h = ground.collision(spaceShip.getPosition());             
	if (h < 20) {
		spaceShip.decreaseLives();
		spaceShip.setPosition(sf::Vector2f(spaceShip.getPosition().x, spaceShip.getPosition().y - 200));
	}

	if (h > 250 || (spaceShip.getRotation() < 10) || (spaceShip.getRotation() > 170)) spaceShip.disactivate();   //sopra a una certa altezza non è possibile attivare il raggio traente
	else {
		float posRl = 40; float posRr = 40;        //setta il raggio traente della lunghezza  opportuna

		 posRl = ground.collision(sf::Vector2f(spaceShip.getFirePoint().x - h/5.6713, spaceShip.getFirePoint().y));  
		 posRr = ground.collision(sf::Vector2f(spaceShip.getFirePoint().x + h/5.6713, spaceShip.getFirePoint().y));

		spaceShip.setRaggio(posRl,posRr); 
	}
	//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	for (int i = 0; i < bunkerVect.size(); i++) {

		if (abs(bunkerVect[i]->getPosition().x - (spaceShip.getPosition().x + 28)) < 200) {
			bunkerVect[i]->activate(true);   //attiva i bunker se la navicella  si trova in loro prossimita'
		}
		else bunkerVect[i]->activate(false);

		if (bunkerVect[i]->update(sf::Vector2f(spaceShip.getPosition())))  spaceShip.decreaseLifePoints();

		int x = i;
		std::vector<bullet> bulletVect = spaceShip.getBullets();

		for (int i = 0; i < bulletVect.size(); i++) {
			if (bulletVect[i].getBounds().intersects(bunkerVect[x]->getBounds()))         //se i proiettili della navicella colpiscono un bunker, decrementa
				bunkerVect[x]->decreaseLife();                                             //i punti vita del bunker
		}

		if (!bunkerVect[i]->isAlive()) {                      //per ogni bunker controlla che sia ancora in vita, altrimenti lo elimina
			points = points + bunkerVect[i]->getLifePoints();
			bunkerVect.erase(bunkerVect.begin() + i);
		}
	}
}

bool planet::checkBunker() {
	if (!bunkerVect.empty())  return false;
	else return true;   //ritorna true se tutti i bunker sono stati distrutti
}


void planet::drawGround(sf::RenderWindow& window) {

	sf::View view = window.getView();

	ground.draw(window);

	if (!bunkerVect.empty()) {

		for (int i = 0; i < bunkerVect.size(); i++) {
			 bunkerVect[i]->draw(window);     //disegna i bunker con i relativi proiettili e se uno dei proiettili
																			 //colpisce la navicella, decrementa i punti vita della navicella
		}
	}

    for (int i = 0; i < tankVect.size(); i++) {
			tankVect[i].draw(window);
	}
}



