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
#include "Hora.h"
#include <string>

using namespace std;

class Utente {
protected:
	Bicicleta* bicicleta;
	string nome;
	Coordenadas coordenada;
	Hora horainicial;
	Hora horafinal;
	double tempouso;
public:
	Utente(int cordX, int cordY);
	virtual ~Utente();
	virtual double getPagamento();
	double subtraiHora();
};

class Regulares: public Utente{
public:
	Regulares(string none, Bicicleta* bicicleta, Coordenadas coordenada);
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
public:
	Socio(string nome, Bicicleta* bicicleta, Coordenadas coordenada);
	double getPagamento();
};


#endif /* UTENTE_H_ */
