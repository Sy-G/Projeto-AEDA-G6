/*
 * Cidade.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef CIDADE_H_
#define CIDADE_H_


#include "Hora.h"
#include <vector>

using namespace std;

class Bicicleta {
protected:
	unsigned int ID;
public:
	Bicicleta();
	virtual ~Bicicleta();
	virtual double getPrecoportipo();
	virtual string getTipo();
};

class Urbana: public Bicicleta{
protected:
	static  double preco_hora; //Preco por hora, em função do tipo.
public:
	Urbana(unsigned int ID);
	double getPrecoportipo();
	string getTipo();
};

class Urbana_Simples: public Bicicleta{
protected:
	static  double preco_hora;
	int velocidade; //velocidade única em (m/s)
public:
	Urbana_Simples(unsigned int ID, int velocidade);
	double getPrecoportipo();
	string getTipo();
};

class Infantil: public Bicicleta{
protected:
	static  double preco_hora;
public:
	Infantil(unsigned int ID);
	double getPrecoportipo();
	string getTipo();
};

class Corrida: public Bicicleta{
protected:
	static  double preco_hora;
public:
	Corrida(unsigned int ID);
	double getPrecoportipo();
	string getTipo();
};

class Ponto {
protected:
	vector<Bicicleta> bicicletas;
	unsigned int capacidade;
	string nome;
public:
	Ponto();
	virtual ~Ponto();
	vector<Bicicleta> getBicicletas(); //bicletas existentes
	unsigned int getnumbicicletasDisponiveis(); //número de bicicletas disponiveis.
	string getNome();
	unsigned int getCapacidade();
};

class Coordenadas {
public:
	int cordX;
	int cordY;

	Coordenadas(int cordX, int cordY){
		this->cordX = cordX;
		this->cordY = cordY;
	}
};

class Utente {
protected:
	Bicicleta* bicicleta;
	string nome;
	Coordenadas coordenada;
	Hora horainicial;
	Hora horafinal;
	double tempouso;
public:
	Utente(string nome, int cordX, int cordY);
	virtual ~Utente();
	virtual double getPagamento();
	void levantaBicicleta(Ponto *p1);
	virtual void devolveBicicleta(Ponto *p1);
	void subtraiHora(Hora horafinal, Hora horainicial); //calcula o tempo de uso
	string getNome();
};

class Regulares: public Utente{
public:
	Regulares(string nome, int cordX, int cordY);
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
	void levantaBicicleta(Ponto *p1);
	void devolveBicicleta(Ponto *p1);
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
	vector<double> horasaccumuladas;
public:
	Socio(string nome, int cordX, int cordY);
	double getPagamento();
	void levantaBicicleta(Ponto *p1);
	void devolveBicicleta(Ponto *p1);
};

class Cidade {
protected:
	vector<Ponto *> pontos;
	vector<Utente *> utentes;
	string nome;
public:
	vector<Ponto *> getPontos();
	Cidade();
	virtual ~Cidade();
};


#endif /* CIDADE_H_ */
