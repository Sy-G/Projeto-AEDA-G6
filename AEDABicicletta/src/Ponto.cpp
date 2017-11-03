/*
 * Ponto.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"
#include "Coordenadas.h"
<<<<<<< HEAD
#include "Bicicleta.h"
=======
#include <sstream>
#include <iostream>
>>>>>>> master

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

vector<Bicicleta *>& Ponto::getBicicletas()
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

bool isThereSpaceInPoint(Ponto &p1)
{
	return p1.getBicicletas().size() < p1.getCapacidade();
}

void Ponto::addBicicleta(Bicicleta* b1)
{
	if(bicicletas.size() == capacidade)
		throw NoSpace(capacidade);

	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		/*if(bicicletas.at(i)->getID() == b1->getID())
			throw Bicicleta_Existente(b1->getID());*/
	}
	bicicletas.push_back(b1);
}

void Ponto::rmBicicleta(unsigned int id)
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		/*if(bicicletas.at(i)->getID() == id)*/
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

bool Ponto::operator==(const Ponto& p2)
{
	return this->nome == p2.getNome();
}

void Ponto::setBicicletas(vector<Bicicleta*> bikes)
{
	if(bikes.size() > capacidade)
		throw NoSpace(bikes.size());
	bicicletas =  bikes;
}

ostream& operator<<(ostream &out, const Ponto &p)
{
	out << p.nome << endl;
	out << p.capacidade << ' ' << p.coord.cordX << '-' << p.coord.cordY << ' ';

	for(size_t i = 0; i < p.bicicletas.size(); i++)
	{
		if (p.bicicletas.at(i)->getTipo() == "Corrida")
			out << "C ";
		else if (p.bicicletas.at(i)->getTipo() == "Urbana")
			out << "U ";
		else if (p.bicicletas.at(i)->getTipo() == "Urbana_Simples")
			out << "S ";
		else if (p.bicicletas.at(i)->getTipo() == "Infantil")
			out << "I ";
	}

	return out;
}

Ponto::Ponto(const string& name, const string& other)
{
	istringstream in;
	in.str(other);
	this->nome = name;
	this->distance = 0;

	try
	{
		in >> capacidade >> coord;
		if(in.fail())
			throw InvalidPoint();
	}
	catch(InvalidCoordinates &e)
	{
		throw InvalidPoint();
	}
	this->distance_coords = coord;

//	int counter = 0;
	while(in.good())
	{
		try
		{
			char bicycle;
			in >> bicycle;
			if(in.fail())
				break;
			if(bicycle == 'C')
				addBicicleta(new Corrida);
			else if(bicycle == 'U')
				addBicicleta(new Urbana);
			else if(bicycle == 'S')
				addBicicleta(new Urbana_Simples);
			else if(bicycle == 'I')
				addBicicleta(new Infantil);
			else
				throw NotAType("");
//			counter++;
		}
		catch(NotAType &e)
		{
			for(size_t i = 0; i < bicicletas.size(); i++)
				delete bicicletas.at(i);
			throw InvalidPoint();
		}
	}
//	cout << counter << endl;
}

void Ponto::deleteBicycles()
{
	for(size_t i = 0; i< bicicletas.size(); i++)
		delete bicicletas.at(i);
}
