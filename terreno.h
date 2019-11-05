#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../../../../../SFML-2.5.1/include/SFML/Graphics/PrimitiveType.hpp"

#include "navicella.h"
#include "bunker.h"

#include "tank.h"
#include "textBox.h"
#include "object.h"


class terreno {

public:
	terreno(int nPianeta);
	~terreno();

	void initTerrain(int size, int nPianeta);

	void draw(sf::RenderWindow& window);

	void setBunker(std::vector<bunker*>& bunkerVect);   //posiziona i bunker sul terreno

	void setTank(std::vector<tank>& tankVect);     //posiziona i serbatoi sul terreno

	float collision(sf::Vector2f pos);           //restituisce la distanza tra l'ordinata in input e il terreno sottostante

	int getSize();

	void setFlag();

	void update();

private:
	sf::VertexArray ground;

	int size;

	std::vector<sf::RectangleShape> rectVect;
	std::vector<sf::ConvexShape> convexShape;
	textBox pianeta1 = textBox(std::string("PLANET "));
	textBox pianeta2 = textBox(std::string("PLANET "));

};