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
#include <sstream>
#include "Bicicleta.h"

using namespace std;

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
	 *
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
	vector<Bicicleta *>& getBicicletas();

	/**
	 * @brief sets the vector of bicycles
	 *
	 * @param bikes new vector of bicycles
	 */
	void setBicicletas(vector<Bicicleta *>  bikes);

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

	/**
	 * @brief equal points have only equal names
	 *
	 * @param p2 second point
	 *
	 * @return true if points have the same point
	 */
	bool operator==(const Ponto& p2);

	/**
	 *	@brief outputs a point in text.
	 *
	 *	@param out stream to output to.
	 *	@param p point to print.
	 *
	 *	@return output stream.
	 */
	friend ostream& operator<<(ostream &out, const Ponto &p);

	/**
	 * @brief deletes all bicycles in a point.
	 *
	 */
	void deleteBicycles();

	/**
	 * @brief Creates point from strings.
	 *
	 * @param name name of the point.
	 *
	 * @param other other parameters
	 */
	Ponto(const string& name, const string& other);


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
 * @return True if there is an empty space
 */
bool isThereSpaceInPoint(Ponto &p1);

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

/**
 * @brief point not formated correctly
 */
class InvalidPoint
{
public:
	InvalidPoint(){};
};

#endif /* PONTO_H_ */
