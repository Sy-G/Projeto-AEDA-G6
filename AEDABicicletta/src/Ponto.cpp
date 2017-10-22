/*
 * Ponto.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"

Ponto::Ponto(string nome, unsigned int capacidade, Coordenadas coord)
{
	this->nome = nome;
	this->capacidade = capacidade;
	this->coord = coord;
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

unsigned int Ponto::getnumbicicletasDisponiveis()
{
	return bicicletas.size();
}

string Ponto::getNome()
{
	return nome;
}

unsigned int Ponto::getCapacidade()
{
	return capacidade;
}

bool Ponto::isThereUrbana()
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getTipo() == "Urbana")
			return true;
	}
	return false;
}

bool Ponto::isThereUranaSimbles()
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getTipo() == "Urbana_Simples")
			return true;
	}
	return false;
}

bool Ponto::isThereCorrida()
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getTipo() == "Corrida")
			return true;
	}
	return false;
}

bool Ponto::isThereInfantil()
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		if(bicicletas.at(i)->getTipo() == "Infantil")
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
