/*
 * Cidade.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef CIDADE_H_
#define CIDADE_H_


#include "Hora.h"
#include "Coordenadas.h"
#include "Bicicleta.h"
#include "Ponto.h"
#include <vector>

using namespace std;


/**
 * @brief Exception
 */
class NotAType
{
public:
	string type;
	NotAType(string i):type(i){};
};


class Utente {
protected:
	Bicicleta* bicicleta;
	string nome;
	Coordenadas coordenada;
	Hora horainicial;
	Hora horafinal;
	double tempouso;
	int ID;
public:
	Utente(string nome,int ID, int cordX, int cordY);
	virtual ~Utente();
	virtual double getPagamento();
	void levantaBicicleta(Ponto *p1);
	virtual void devolveBicicleta(Ponto *p1);
	void subtraiHora(Hora horafinal, Hora horainicial); //calcula o tempo de uso
	string getNome();
	Bicicleta* getBicicleta();
	Hora getHoraInicial();
	Hora getHoraFinal();
};

class Regulares: public Utente{
public:
	Regulares(string nome,int ID, int cordX, int cordY);
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
	void levantaBicicleta(Ponto *p1);
	void devolveBicicleta(Ponto *p1);
	bool eSocio();
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
	vector<double> horasaccumuladas;
public:
	Socio(string nome,int ID, int cordX, int cordY);
	double getPagamento();
	void levantaBicicleta(Ponto *p1);
	void devolveBicicleta(Ponto *p1);
	bool eSocio();
};

class Cidade {
protected:
	vector<Ponto> pontos;
	vector<Utente *> utentes;
	string nome;
public:
	vector<Ponto>& getPontos();
	/**
	 * @brief Sorts point from the closer to farthest point according to some given coordinate.
	 *
	 * @param c1 Coordinates to sort by.
	 *
	 * @return reference to the new point vector
	 */
	Cidade& sortPointsByDistance(Coordenadas c1);

	/**
	 * @brief Adds a point to the array
	 *
	 * @param p1 Point to add
	 */
	Cidade& addPoint(Ponto p1);

	/**
	 * @brief If the vector is ordered by distance, finds the closer bicycle of a certain type, else  finds the first it can.
	 *
	 * @param bicycle Type of bike
	 *
	 * @return iterator to the bicycle, or vector<Ponto>.end() se não encontrar
	 */
	vector<Ponto>::iterator isThereBicycle(string bicycle);

	/**
	 * @brief calculates the closest point with a certain kind of bicycle
	 *
	 * @param coord Closest to this coordinates
	 * @param type Name of the type
	 *
	 * @return iterator to the point
	 */
	vector<Ponto>::iterator closestType(Coordenadas coord, string type);

	/**
	 * @return Returns an iterator to the first point with free space
	 */
	vector<Ponto>::iterator isThereSpace();

	/**
	 * @param coord Coordinates to calculate the distance
	 *
	 * @return Returns an iterator to the closest point with free space
	 */
	vector<Ponto>::iterator closestSpace(Coordenadas coord);

	/**
	 * @brief Adds a user to the array
	 *
	 * @param u1 User to add
	 */
	Cidade& addUtente(Utente* u1);

	/**
	 * @brief searches a point in the city
	 *
	 * @param name name of the point
	 *
	 * @return iterator to the point
	 */
	vector<Ponto>::iterator findPoint(string name);

	/**
	 * @brief redistribute bicycles evenly
	 *
	 * @return vector of bicycles that do not fit in the points
	 */
	vector<Bicicleta *> redistributeBikes();

	/**
	 * @brief redistributes a vector of bicycles.
	 *
	 * @param bicycles bikes to redistribute.
	 * @param percentage percentage of bicycles to go in each point.
	 * @return bicycles with no space.
	 */
	vector<Bicicleta *> redistributeVector(vector<Bicicleta *> &v, float percentage);

	/**
	 * @brief if the standard deviation of occupation is above a certain level, redistributes the bicycles.
	 *
	 * @return bikes that didn't fit (always empty due to implementation)
	 */
	vector<Bicicleta *> testOccupation();

	Cidade();
	virtual ~Cidade();
};


/**
 * Not a point
 */
class NotAPoint
{
public:
	string name;
	NotAPoint(string n) : name(n){};
};

/**
 * Point already exists
 */
class existentPoint
{
public:
	string name;
	existentPoint(string n) : name(n){};
};

/**
 * Redistribution not neededs
 */
class NoRedistributionNeeded
{
public:
	NoRedistributionNeeded(){};
};

#endif /* CIDADE_H_ */
