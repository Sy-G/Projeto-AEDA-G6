#include "Cidade.h"
#include <cmath>
using namespace std;


Coordenadas::Coordenadas(double cordX, double cordY)
{
	this->cordX = cordX;
	this->cordY = cordY;
}


double distance_between_coordinates(Coordenadas c1, Coordenadas c2)
{
	return sqrt((c1.cordX - c2.cordX)*(c1.cordX - c2.cordX)+ (c1.cordY - c2.cordY)*(c1.cordY - c2.cordY));
}

Coordenadas::Coordenadas()
{
	this->cordX = 0;
	this->cordY = 0;
}

bool Coordenadas::operator ==(const Coordenadas c1) const
{
	return (cordX == c1.cordX) && (cordY ==  c1.cordY);
}