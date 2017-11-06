/*
 * Coordenadas.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */
#ifndef COORDENADAS_H
#define COORDENADAS_H

class Coordenadas
{
public:
	double cordX;
	double cordY;

	Coordenadas(double cordX, double cordY);
	Coordenadas();
	/**
	 * @brief Verifies if they are equal
	 *
	 * @param c1 second coordinate
	 */
	bool operator==(const Coordenadas c1) const;
};

double distance_between_coordinates(Coordenadas c1, Coordenadas c2);
istream& operator>> (istream& in, Coordenadas &coord) ;

class InvalidCoordinates
{
public:
	InvalidCoordinates(){};
};

#endif /* COORDENADAS_H_ */
