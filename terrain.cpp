#include <stdio.h>
#include <random>
#include <cmath>
#include "terrain.h"

#define PI 3.14159265

terrain::terrain(int nPianeta) : size(50), pianeta1("PLANET " + std::to_string(nPianeta)),
pianeta2("PLANET " + std::to_string(nPianeta)) {

}

terrain::~terrain()
{
}

void terrain::initTerrain(int size, int nPianeta) {
	this->size = size;
	ground.setPrimitiveType(sf::PrimitiveType::LineStrip);
	ground.resize(size);

	for (int i = 10; i < ground.getVertexCount() - 1; i++) {
		ground[i].position = sf::Vector2f(i * 128, rand() % 128 + 550);
		ground[i].color = sf::Color::Green;
	}
	ground[size - 1].position = sf::Vector2f(ground[10].position.x + (size - 10) * 128, ground[10].position.y);
	ground[size - 1].color = sf::Color::Green;

	for (int i = 0; i < 10; i++) {
		ground[i].position = sf::Vector2f((i - 1) * 128, ground[size - 11 + i].position.y);
		ground[i].color = sf::Color::Green;
	}

	this->setFlag();
}

void terrain::draw(sf::RenderWindow & window) {

	window.draw(ground);

	//disegna i riquadri che contraddistinguono il pianeta
	for (int i = 0; i < convexShape.size(); i++) {
		window.draw(convexShape[i]);
	}

	for (int i = rectVect.size() - 1; i >= 0; i--) {
		window.draw(rectVect[i]);
	}

	pianeta1.draw1(window); pianeta2.draw1(window);
	//
}

void terrain::setBunker(std::vector<bunker*> & bunkerVect) {

	int j = 3;
	for (int i = 0; i < bunkerVect.size(); i++) {
		if (j * 3 < getSize() - 11) {
			float x1 = ground[j * 3 + 1].position.x;
			float y1 = ground[j * 3 + 1].position.y;
			float x2 = ground[j * 3 + 2].position.x;
			float y2 = ground[j * 3 + 2].position.y;

			sf::Vertex line[] =
			{
					sf::Vertex(sf::Vector2f(x1, y1)),
					sf::Vertex(sf::Vector2f(x2, y2))
			};


			double alpha = (double)atan((y2 - y1) / (x2 - x1));
			alpha = (alpha * 180) / PI;
			bunkerVect[i]->setPosition(line->position);
			bunkerVect[i]->rotate(alpha);
			j = j + 1;
		}
	}

}


void terrain::setTank(std::vector<tank> & tankVect) {

	int j = 3;
	for (int i = 0; i < tankVect.size(); i++) {
		float x1 = ground[j * 3 + 2].position.x;
		float y1 = ground[j * 3 + 2].position.y;
		float x2 = ground[j * 3 + 3].position.x;
		float y2 = ground[j * 3 + 3].position.y;

		sf::Vertex line[] =
		{
				sf::Vertex(sf::Vector2f(x1, y1)),
				sf::Vertex(sf::Vector2f(x2, y2))
		};

		float deltaX = (x2 - x1) / 2;
		float deltaY = (y2 - y1) / 2;
		double alpha = (double)atan(deltaY / deltaX);
		alpha = (alpha * 180) / PI;

		tankVect[i].setPosition(sf::Vector2f(line->position.x + deltaX, line->position.y + deltaY));
		tankVect[i].rotate(alpha);

		j = j + 1;
	}
}


float terrain::collision(sf::Vector2f pos) {

	float posX = pos.x;
	float posY = pos.y;

	for (int i = 0; i < ground.getVertexCount() - 1; i++) {
		float x1 = ground[i].position.x;
		float y1 = ground[i].position.y;
		float x2 = ground[i + 1].position.x;
		float y2 = ground[i + 1].position.y;


		float minY = y1;  float minX = x1;

		if (y2 > y1) {
			minY = y2;
			minX = x2;
		}

		float deltaX = fabsf(posX - minX);
		float deltaY = deltaX * (fabsf((y2 - y1) / (x2 - x1)));

		double cY = fabsf(minY - deltaY);              //altezza del terreno nel punto nel punto in cui si trova la navicella

		if ((posX >= x1) && (posX <= x2)) {                            //colloca la navicella in un range deltaX e va a controllare che non tocchi
			return(abs(cY - posY));
		}
	}

	return(1);
}


int terrain::getSize() {
	return size;
}

void terrain::setFlag() {
	double y1 = ground[6].position.y; double y2 = ground[7].position.y;
	double tan = (-(y2 - y1) / 128);

	double minY = y1; 	double deltaX1 = 42; double deltaX2 = 57;

	if (y2 > y1) {
		minY = y2;
		deltaX1 = 42.0 - 128;
		deltaX2 = 57.0 - 128;
	}

	double deltaY = (deltaX1 * tan);
	double p1 = minY - deltaY;
	double p2 = minY - (deltaX2 * tan);

	for (int i = 0; i < 2; i++) {
		sf::RectangleShape newRect(sf::Vector2f(100, 45));
		rectVect.push_back(newRect);
		rectVect[i].setFillColor(sf::Color::Black);
		rectVect[i].setOutlineThickness(5.f);
		rectVect[i].setOutlineColor(sf::Color(148, 86, 6));
	}

	rectVect[0].setPosition(ground[size - 5].position.x, ground[size - 5].position.y - 150);
	rectVect[1].setPosition(5 * 128, ground[6].position.y - 150);


	for (int i = 0; i < 2; i++) {
		sf::ConvexShape newCS;
		convexShape.push_back(newCS);
		convexShape[i].setPointCount(4);
		convexShape[i].setPoint(0, sf::Vector2f(rectVect[i].getPosition().x + 42, rectVect[i].getPosition().y - 10));
		convexShape[i].setPoint(1, sf::Vector2f(rectVect[i].getPosition().x + 57, rectVect[i].getPosition().y - 10));
		convexShape[i].setPoint(2, sf::Vector2f(rectVect[i].getPosition().x + 57, p2));
		convexShape[i].setPoint(3, sf::Vector2f(rectVect[i].getPosition().x + 42, p1));

		convexShape[i].setFillColor(sf::Color(120, 70, 5));
	}

	pianeta1.setColor(sf::Color(130, 92, 62)); 	pianeta2.setColor(sf::Color(130, 92, 62));
	pianeta1.setSize(15); 	pianeta2.setSize(15);
	pianeta1.setPosition(sf::Vector2f(rectVect[0].getPosition().x + 10, rectVect[0].getPosition().y + 15)); pianeta2.setPosition(sf::Vector2f(rectVect[1].getPosition().x + 10, rectVect[1].getPosition().y + 15));

}

void terrain::update() {
	pianeta1.setFont(); pianeta2.setFont();
}