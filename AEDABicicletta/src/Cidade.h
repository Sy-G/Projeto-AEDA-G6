/*
 * Cidade.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef CIDADE_H_
#define CIDADE_H_


#include "Ponto.h"
#include "Utente.h"
#include <vector>

using namespace std;

class Cidade {
protected:
	vector<Ponto> pontos;
	vector<Utente *> utentes;
	string nome;
public:
	Cidade();
	virtual ~Cidade();
};

#endif /* CIDADE_H_ */
