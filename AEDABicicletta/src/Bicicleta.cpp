/*
 * Bicicleta.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Bicicleta.h"


double  Infantil::preco_hora = 0.30;
double  Urbana::preco_hora = 0.75;
double  Urbana_Simples::preco_hora = 0.50;
double  Corrida::preco_hora = 0.80;

Bicicleta::Bicicleta(unsigned int ID)
{
  this->ID = ID;
}

Bicicleta::~Bicicleta() {
	// TODO Auto-generated destructor stub
}

double Bicicleta::getPrecoportipo() const
{
	return 0;
}

unsigned int Bicicleta::getID() const
{
	return this->ID;
}

void Bicicleta::setPrecoportipo(double newprice)
{
}


/* Urbana */

Urbana::Urbana(unsigned int ID) : Bicicleta(ID)
{
}

double Urbana::getPrecoportipo() const
{
	return preco_hora;
}

void Urbana::setPrecoportipo(double newprice)
{
	this->preco_hora= newprice;
}

/* Urbana Simples */

Urbana_Simples::Urbana_Simples(unsigned int ID): Bicicleta(ID)
{
}

double Urbana_Simples::getPrecoportipo() const
{
	return preco_hora;
}

void Urbana_Simples::setPrecoportipo(double newprice)
{this->preco_hora= newprice;
}




/* Infantil */


Infantil::Infantil(unsigned int ID) : Bicicleta(ID)
{
}

double Infantil::getPrecoportipo() const
{
	return preco_hora;
}

void Infantil::setPrecoportipo(double newprice)
{
	 this->preco_hora= newprice;
}



/* Corrida */


Corrida::Corrida(unsigned int ID): Bicicleta(ID)
{
}

double Corrida::getPrecoportipo() const
{
	return preco_hora;
}

void Corrida::setPrecoportipo(double newprice)
{
	this->preco_hora= newprice;
}


