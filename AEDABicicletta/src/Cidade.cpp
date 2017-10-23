/*
 * Cidade.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"
#include <algorithm>
#include <vector>

Cidade::Cidade() {
	// TODO Auto-generated constructor stub
}

Cidade::~Cidade() {
	// TODO Auto-generated destructor stub
}

vector<Ponto> Cidade::getPontos(){
	return pontos;
}

Cidade& Cidade::sortPointsByDistance(Coordenadas c1)
{
	for(size_t i = 0; i < pontos.size(); i++)
	{
		pontos.at(i).setDistanceCoords(c1);
		pontos.at(i).setDistance(distance_between_coordinates(pontos.at(i).getCoord(),c1));
	}

	sort(pontos.begin(), pontos.end());
	return *this;
}

Cidade& Cidade::addPoint(Ponto p1)
{
	pontos.push_back(p1);
	return *this;
}

vector<Ponto>::iterator Cidade::isThereBicycle(string bicycle)
{
	vector<Ponto>::iterator iter = pontos.begin();
	if(bicycle == "Urbana_Simples")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereUrbanaSimples)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Urbana")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereUrbana)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Infantil")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereInfantil)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Corrida")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereCorrida)) != pontos.end())
			return iter;
	}
	/*else
		throw;*/

	return pontos.end();
}
