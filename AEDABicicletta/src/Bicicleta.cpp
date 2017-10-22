/*
 * Bicicleta.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"

double  Infantil::preco_hora = 0.30;
double  Urbana::preco_hora = 0.75;
double  Urbana_Simples::preco_hora = 0.50;
double  Corrida::preco_hora = 0.80;

Bicicleta::Bicicleta() {}

Bicicleta::~Bicicleta() {
	// TODO Auto-generated destructor stub
}

double Bicicleta::getPrecoportipo(){
	return 0;
}

string Bicicleta::getTipo(){
	return "";
}

double Infantil::getPrecoportipo(){
	return preco_hora;
}

double Urbana::getPrecoportipo(){
	return preco_hora;
}

double Urbana_Simples::getPrecoportipo(){
	return preco_hora;
}

double Corrida::getPrecoportipo(){
	return preco_hora;
}

Urbana::Urbana(unsigned int ID){
	this->ID = ID;
}

Infantil::Infantil(unsigned int ID){
	this->ID = ID;
}

Urbana_Simples::Urbana_Simples(unsigned int ID){
	this->ID = ID;
	/*this->velocidade = velocidade;*/
}

Corrida::Corrida(unsigned int ID){
	this->ID = ID;
}

string Corrida::getTipo(){
	return "Corrida";
}

string Urbana::getTipo(){
	return "Urbana";
}

string Urbana_Simples::getTipo(){
	return "Urbana Simples";
}

string Infantil::getTipo(){
	return "Infantil";
}

unsigned int Bicicleta::getID(){
	return ID;
}

/*int Urbana_Simples::getVelocidade(){
	return velocidade;
}*/
