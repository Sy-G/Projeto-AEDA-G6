/*
 * Ponto.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"

Ponto::Ponto() {
	// TODO Auto-generated constructor stub

}

Ponto::~Ponto() {
	// TODO Auto-generated destructor stub
}

vector<Bicicleta *> Ponto::getBicicletas(){
	return bicicletas;
}

unsigned int Ponto::getnumbicicletasDisponiveis(){
	return bicicletas.size();
}

string Ponto::getNome(){
	return nome;
}

unsigned int Ponto::getCapacidade(){
	return capacidade;
}
