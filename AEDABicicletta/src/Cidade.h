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
#include <vector>

using namespace std;

class Coordenadas;

class Bicicleta {
protected:
	unsigned int ID;
public:
	Bicicleta(unsigned int id);
	virtual ~Bicicleta();
	virtual double getPrecoportipo();
	virtual string getTipo();
	unsigned int getID();
};

class Urbana: public Bicicleta{
protected:
	static  double preco_hora; //Preco por hora, em fun��o do tipo.
public:
	Urbana(unsigned int ID);
	double getPrecoportipo();
	string getTipo();
};

class Urbana_Simples: public Bicicleta{
protected:
	static  double preco_hora;
	/*int velocidade; //velocidade �nica em (m/s)*/
public:
	Urbana_Simples(unsigned int ID);
	double getPrecoportipo();
	/*int getVelocidade();*/
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
	/**
	 * @brief Holds pointers to the bicycles that are currently in the point
	 */
	vector<Bicicleta *> bicicletas;
	/**
	 * @brief Max number of bicycles a point can hold
	 */
	unsigned int capacidade;
	/**
	 * @brief Name of the point
	 */
	string nome;
	/**
	 * @brief Location of the point
	 */
	Coordenadas coord;

	/**
	 * @brief Distance to a given coordinate
	 */
	double distance;

	/**
	 * @brief Coordinates that the distance corresponds to
	 */
	Coordenadas distance_coords;
public:
	/**
	 * @brief Creates a point with no bicycles attached to it
	 *
	 * @param nome Name of the point
	 * @param capacidade Max number of bicycles a point can hold
	 */
	Ponto(string nome, unsigned int capacidade, Coordenadas coord);
	/**
	 * @brief Destructor
	 */
	virtual ~Ponto();
	/**
	 * @brief
	 *
	 * @return Pointer to the vector of bicycles of the point
	 */
	vector<Bicicleta *> getBicicletas();
	/**
	 * @brief
	 *
	 * @return Number of bicycles available
	 */
	unsigned int getnumbicicletasDisponiveis() const;
	/**
	 * @return Name of the point
	 */
	string getNome() const;
	/**
	 * @return Capacity
	 */
	unsigned int getCapacidade() const;

	/**
	 * @brief Adds a "bicicleta" to the vector throws an exeception with already exists one with the same id
	 *
	 * @param b1 "Bicicleta to add to the vector
	 */
	void addBicicleta(Bicicleta* b1);

	/**
	 * @brief Removes a "bicicleta" from the vector with that "bicicleta" doesn't exist throws an exception
	 *
	 * @param id Id of the bicycle to remove
	 */
	void rmBicicleta(unsigned int id);

	/**
	 * @brief True if the object that its applied to is closer to distance_coords than p1, assumes distance_coords is equal in both.
	 *
	 * @param p1 Point to compare to
	 *
	 * @return Boolean
	 */
	bool operator<(Ponto p1);

	/**
	 * @brief Change "capacidade"
	 *
	 * @param capacidade New "capacidade"
	 */
	void setCapacidade(unsigned int capacidade);

	/**
	 * @return coord
	 */
	const Coordenadas& getCoord() const;

	/**
	 * @brief Change "coord"
	 *
	 * @param coord New "coord"
	 */
	void setCoord(const Coordenadas& coord);

	/**
	 * @return distance
	 */
	double getDistance() const;

	/**
	 * @brief Change "distance"
	 *
	 * @param distance New "distance"
	 */
	void setDistance(double distance);

	/**
	 * @return distance_coords
	 */
	const Coordenadas& getDistanceCoords() const;

	/**
	 * @brief Change "distance_coords"
	 *
	 * @param distanceCoords New "distance_coords"
	 */
	void setDistanceCoords(const Coordenadas& distanceCoords);

	/**
	 * @brief Change "nome"
	 *
	 * @param nome New "nome"
	 */
	void setNome(const string& nome);
};

/**
 * @return True if there is at least one "Urbana" in the point
 */
bool isThereUrbana( Ponto &p1);

/**
 * @return True if there is at least one "Urbana Simples" in the point
 */
bool isThereUrbanaSimples( Ponto &p1);

/**
 * @return True if there is at least one "Corrida" in the point
 */
bool isThereCorrida(Ponto &p1) ;

/**
 * @return True if there is at least one "Infantil" in the point
 */
bool isThereInfantil(Ponto &p1) ;


/**
 * @brief Exception
 */
class Bicicleta_Existente
{
public:
	unsigned int id;
	Bicicleta_Existente(int i):id(i){};
};

/**
 * @brief Exception
 */
class Bicicleta_Inexistente
{
public:
	unsigned int id;
	Bicicleta_Inexistente(int i):id(i){};
};

/**
 * @brief Exception
 */
class NoSpace
{
public:
	unsigned int capacidade;
	NoSpace(int i):capacidade(i){};
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
	vector<Ponto> pontos;
	vector<Utente *> utentes;
	string nome;
public:
	vector<Ponto> getPontos();
	/**
	 * @brief Sorts point from the closer to farthest point according to some given coordinate.
	 *
	 * @param c1 Coordinates to sort by.
	 *
	 * @return reference to the new point vector
	 */
	Cidade& sortPointsByDistance(Coordenadas c1);

	/**
	 * @brief Adds a point ro the array
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
	Cidade();
	virtual ~Cidade();
};


#endif /* CIDADE_H_ */
