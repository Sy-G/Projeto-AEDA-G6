/*
 * Utente.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 *
 *      NOTA: acerca do pagamento, é apenas -após- a utilização, tudo bem, mas o cliente pode
 *      definir logo à partida o tempo que vai usar essa bicicleta, se for regular,
 *      se não for, nem tem que definir um tempo porque a sua mensalidade cobre os custos de qualquer maneira.
 */

#ifndef UTENTE_H_
#define UTENTE_H_

#include "Coordenadas.h"
#include "Bicicleta.h"
#include <string>

using namespace std;

class Utente {
protected:
	Bicicleta* bicicleta;
	string nome;
	Coordenadas coordenada;
public:
	Utente(int cordX, int cordY);
	virtual ~Utente();
	virtual double getPagamento();
};

class Regulares: public Utente{
protected:
	double tempo; //tempo durante o qual o cliente vai usar a bicicleta.
public:
	Regulares();
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
	double tempomes;
public:
	Socio(string nome, Bicicleta* bicicleta, Coordenadas coordenada, double tempomes);
	double getPagamento(); //tem em conta a mensalidade e aplica descontos em função do numero de horas de aluger para esse mes.
	//seguindo a mesma lógica, tempomês é declarado no ínicio do mês.
	//se no contrutor não se especificar um tempomes paga-se a mensalidade sem desconto.
};


#endif /* UTENTE_H_ */
