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
#include "Utente.h"
#include <vector>
#include <tr1/unordered_set>

using namespace std;

//this structure will be used to keep track of bicycles sent to be disassembled via dispersion table
struct BicicleHash {

	int operator() (const Bicicleta& b1) const{
		//hash function, quadratic sounding is used to promote efficient collision-resolution

	}

	bool operator() (const Bicicleta& b1, const Bicicleta b2) const{
		//comparison function, two bicycles are only the same if they have the same ID.

		if(b1.getID() == b2.getID()){
			return true;
		} else return false;
	}

};

typedef tr1::unordered_set<Bicicleta, BicicleHash, BicicleHash> HashTabBicycle;

/**
 * @brief Exception
 */
class NotAType
{
public:
	string type;
	NotAType(string i):type(i){};
};

/**
 * @brief Exception
 */
class NoPoint
{
public:
	NoPoint(){};
};


class Cidade {
protected:
	vector<Ponto> pontos;
	vector<Utente *> utentes;
	string nome;
	HashTabBicycle brokenbikes;
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
	 * @brief searches a point in the city
	 *
	 * @param x coordinate x of the point
	 * @param y coordinate y of the point
	 *
	 * @return true if the point exists, false otherwise
	 */
	bool  findPoint(double x, double y);

	/**
	 * @brief removes an user from the city
	 *
	 * @param id id of the user
	 */
    Cidade& removeUtente(int id);

    /**
    * @brief removes a point from the city
    *
    * @param name name of the point
    */
    Cidade& removePonto(string name);

   /**
	 * @brief searches an user in the city
	 *
	 * @param id id of the user
	 *
	 * @return pointer to the user
	 */
	Utente* findUtente(int id);


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

	/**
	 * @brief prints all points to out.
	 *
	 * @param out output stream.
	 */
	void printPoints(ostream &out);

	/**
	 * @brief prints all points to out.
	 */
	void printPointsinMenu();

	/**
	 * @brief prints all Users to the screen;
	 *
	 */
	void printUsers();

	/**
	 * @brief prints all points to file.
	 *
	 * @param file to output to.
	 */
	void printPointsFile(const string &file);

	/**
	 * @brief reads points from a file.
	 *
	 * @param file to read.
	 */
	void readPoints(const string& file);

	/**
	 * @brief reads Users from a file.
	 *
	 * @param file to read.
	 */
	void readUsers(const string& file);

	/**
	 * @brief writes Users to a file.
	 *
	 * @param file to write to.
	 */
	void printUserstoFile(const string& file);

	/**
	 * @brief atributes a disassembly date to a bike
	 *
	 * @param bike to disassemble's ID;
	 * @param date of disassembly;
	 */
	void disassembleBike(unsigned int bikeID, string date);

	/**
	 * @brief consults all the bicycles prepped for disassembly
	 */
	void consultBikes();

	/**
	 * @brief deletes a given bike from the registry
	 */
	void deleteBike(unsigned int bikeID);

	Cidade();
	virtual ~Cidade();
};

/**
 * @brief Exception
 */
class JaTemBicicletaException{
public:
	string nome;

	string getNome(){
		return nome;
	}

	JaTemBicicletaException(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class NaoTemBicicletaException{
public:
	string nome;

	string getNome(){
		return nome;
	}

	NaoTemBicicletaException(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class PontoVazio{
public:
	string nome;

	string getNome(){
		return nome;
	}

	PontoVazio(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class UtenteNaoExistente{
public:
	string nome;

	string getNome(){
		return nome;
	}

	UtenteNaoExistente(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class NoUserFound
{
public:
	int id;
	NoUserFound (int id){this->id = id; };
};

/**
 * @brief Exception
 */
class PontoNaoExistente{
public:
	string nome;

	string getNome(){
		return nome;
	}

	PontoNaoExistente(string nome){
		this->nome = nome;
	}
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
 * Redistribution not needed
 */
class NoRedistributionNeeded
{
public:
	NoRedistributionNeeded(){};
};

/**
 * Not a file
 */
class NotAFile
{
public:
	string name;
	NotAFile(string n) : name(n){};
};

/**
 * Invalid File
 */
class InvalidFile
{
public:
	InvalidFile(){};
};


#endif /* CIDADE_H_ */
