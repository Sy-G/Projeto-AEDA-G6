/*
 * Ponto.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"
#include "Coordenadas.h"

Ponto::Ponto(string nome, unsigned int capacidade, Coordenadas coord)
{
	this->nome = nome;
	this->capacidade = capacidade;
	this->coord = coord;
	this->distance = 0;
	this->distance_coords = coord;
}

Ponto::~Ponto()
{
	/*for(size_t i = 0; i < bicicletas.size(); i++)
	{
		delete bicicletas.at(i);
	}*/
}

vector<Bicicleta *> Ponto::getBicicletas()
{
	return bicicletas;
}

unsigned int Ponto::getnumbicicletasDisponiveis() const
{
	return bicicletas.size();
}

string Ponto::getNome() const
{
	return nome;
}

unsigned int Ponto::getCapacidade() const
{
	return capacidade;
}

bool isThereUrbana( Ponto &p1)
{
	for(size_t i = 0; i < p1.getBicicletas().size(); i++)
	{
		if(p1.getBicicletas().at(i)->getTipo() == "Urbana")
			return true;
	}
	return false;
}

bool isThereUrbanaSimples( Ponto &p1)
{
	for(size_t i = 0; i < p1.getBicicletas().size(); i++)
	{
		if(p1.getBicicletas().at(i)->getTipo() == "Urbana_Simples")
			return true;
	}
	return false;
}

bool isThereCorrida( Ponto &p1)
{
	for(size_t i = 0; i < p1.getBicicletas().size(); i++)
	{
		if(p1.getBicicletas().at(i)->getTipo() == "Corrida")
			return true;
	}
	return false;
}

bool isThereInfantil( Ponto &p1)
{
	for(size_t i = 0; i < p1.getBicicletas().size(); i++)
	{
		if(p1.getBicicletas().at(i)->getTipo() == "Infantil")
			return true;
	}
	return false;
}

void Ponto::addBicicleta(Bicicleta* b1)
{
	if(bicicletas.size() == capacidade)
		throw NoSpace(capacidade);

	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getID() == b1->getID())
			throw Bicicleta_Existente(b1->getID());
	}
	bicicletas.push_back(b1);
}

void Ponto::rmBicicleta(unsigned int id)
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getID() == id)
		{
			bicicletas.erase(bicicletas.begin() + i);
			return;
		}
	}
	throw Bicicleta_Inexistente(id);
}


bool Ponto::operator <(Ponto p1)
{
	return this->distance < p1.distance;
}


void Ponto::setCapacidade(unsigned int capacidade)
{
	this->capacidade = capacidade;
}

const Coordenadas& Ponto::getCoord() const
{
	return this->coord;
}

void Ponto::setCoord(const Coordenadas& coord)
{
	this->coord = coord;
}

double Ponto::getDistance() const
{
	return distance;
}

void Ponto::setDistance(double distance)
{
	this->distance = distance;
}

const Coordenadas& Ponto::getDistanceCoords() const
{
	return distance_coords;
}

void Ponto::setDistanceCoords(const Coordenadas& distanceCoords)
{
	distance_coords = distanceCoords;
}

void Ponto::setNome(const string& nome)
{
	this->nome = nome;
}
