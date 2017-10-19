/*
 * Ponto.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

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
};

#endif /* PONTO_H_ */
