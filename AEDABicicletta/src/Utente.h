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

/*
#ifndef UTENTE_H_
#define UTENTE_H_

#include "Coordenadas.h"
#include "Bicicleta.h"
#include "Cidade.h"
#include "Hora.h"
#include <vector>
#include <string>

using namespace std;


class Utente {
protected:
	Bicicleta* bicicleta;
	Cidade* cidade;
	string nome;
	Coordenadas coordenada;
	Hora horainicial;
	Hora horafinal;
	double tempouso;
public:
	Utente(string nome,Cidade* cidade,int cordX, int cordY);
	virtual ~Utente();
	virtual double getPagamento();
	void levantaBicicleta(string nome);
	virtual void devolveBicicleta(string nome);
	double subtraiHora();
	string getNome();
};

class Regulares: public Utente{
public:
	Regulares(string nome,Cidade* cidade, int cordX, int cordY);
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
	void levantaBicicleta(string nome);
	void devolveBicicleta(string nome);
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
	vector<double> horasaccumuladas;
public:
	Socio(string nome,Cidade* cidade, int cordX, int cordY);
	double getPagamento();
	void levantaBicicleta(string nome);
	void devolveBicicleta(string nome);
};


#endif /* UTENTE_H_ */
