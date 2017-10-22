/*
 * Ponto.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"

Ponto::Ponto(string nome, unsigned int capacidade)
{
	this->nome = nome;
	this->capacidade = capacidade;
}

Ponto::~Ponto()
{
	for(size_t i = 0; i < bicicletas.size(); i++)
	{
		delete bicicletas.at(i);
	}
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
