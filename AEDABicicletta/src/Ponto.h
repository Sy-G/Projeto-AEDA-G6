/*
 * Ponto.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */
 /*
#ifndef PONTO_H_
#define PONTO_H_

#include <vector>
#include <string>
#include "Bicicleta.h"

using namespace std;

class Ponto {
protected:
	vector<Bicicleta *> bicicletas;
	unsigned int capacidade;
	string nome;
public:
	Ponto();
	virtual ~Ponto();
	vector<Bicicleta *> getBicicletas(); //bicletas existentes
	int getnumbicicletasDisponiveis(); //número de bicicletas disponiveis.
	string getNome();
};

#endif /* PONTO_H_ */
