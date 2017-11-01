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
	/**
	 * @brief Pointer to the bicycle owned by this user
	 */
	Bicicleta* bicicleta;
	/**
	 * @brief User's name
	 */
	string nome;
	/**
	 * @brief Coordinates for later use in distance function
	 */
	Coordenadas coordenada;
	/**
	 * @brief Hour of bicycle withdrawal
	 */
	Hora horainicial;
	/**
	 * @brief Hour at which the user returns the bike
	 */
	Hora horafinal;
	/**
	 * @brief Time interval of a user's session with a given bike in hours
	 */
	double tempouso;
	/**
	 * @brief User's ID incremented statically
	 */
	static int ultimoID;
	/**
	 * @brief User's ID
	 */
	int ID;
public:
	/**
	 * @brief Creates a default User with no bicycle, hours set to 0, with a given coordinate, and an ID that is incremented upon creation
	 *
	 * @param nome Name of the user
	 * @param cordX X coordinate of the User
	 * @param cordY Y coordinate of the User
	 */
	Utente(string nome,int ID, int cordX, int cordY);
	/**
	 * @brief Destructor
	 */
	virtual ~Utente();
	/**
	 * @brief This function obtains a given user's payment, depends if he is a regular or not.
	 */
	virtual double getPagamento();
	/**
	 * @brief This function allows a user to withdraw a bike.
	 *
	 * * @param p1 Reference to the point from which the bike will be withdrawn
	 * * @param tipo The kind of bike that will be withdrawn
	 * * @param horainicial Time of withdrawal
	 */
	void levantaBicicleta(Ponto *&p1, string tipo, Hora horainicial);
	/**
	 * @brief This function allows a user to return a bike.
	 *
	 * * @param p1 Reference to the point of return
	 * * @param horafinal Time of return
	 */
	virtual double devolveBicicleta(Ponto *&p1, Hora horafinal);
	/**
	 * @brief This function calculates usage time by subtracting withdrawal hour to return hour
	 *
	 * * @param horainicial Time of withdrawal
	 * * @param horafinal Time of return
	 */
	void subtraiHora(Hora horafinal, Hora horainicial); //calcula o tempo de uso
	/**
	 * @brief This function gets a user's name
	 */
	string getNome();
	/**
	 * @brief This function gets a user's bicycle
	 */
	Bicicleta* getBicicleta();
	/**
	 * @brief This function gets a user's withdrawal hour
	 */
	Hora getHoraInicial();
	/**
	 * @brief This function gets a user's return hour
	 */
	Hora getHoraFinal();
	/**
	 * @brief This function sets a user's bicycle to b1
	 *
	 * * @param b1 bicycle to set
	 */
	void setBicicleta(Bicicleta *b1);
	/**
	 * @brief This function tells whether a user is an associate or not.
	 */
	virtual bool eSocio() = 0;
};

class Regulares: public Utente{
public:
	/**
	 * @brief Creates a Regular User with no bicycle, hours set to 0, with a given coordinate, and an ID that is incremented upon creation
	 *
	 * @param nome Name of the user
	 * @param cordX X coordinate of the User
	 * @param cordY Y coordinate of the User
	 */
	Regulares(string nome,int ID, int cordX, int cordY);
	/**
	 * @brief This function obtains a given user's payment, if he is regular he needs to pay after each use, the amount is given by multiplying usage time with bike price per hour.
	 */
	double getPagamento();
	void levantaBicicleta(Ponto *&p1, string tipo, Hora horainicial);
	double devolveBicicleta(Ponto *&p1, Hora horafinal);
	bool eSocio();
};

class Socio: public Utente{
protected:
	static double mensalidade; //mensalidade dos Socios
	vector<double> horasaccumuladas;
public:
	/**
	 * @brief Creates an Associate User with no bicycle, hours set to 0, with a given coordinate, and an ID that is incremented upon creation
	 *
	 * @param nome Name of the user
	 * @param cordX X coordinate of the User
	 * @param cordY Y coordinate of the User
	 */
	Socio(string nome,int ID, int cordX, int cordY);
	/**
	 * @brief This function obtains a given user's payment, in this case the user will accumulate hours until it's the end of the month, at that time it will checkout and calculate the user's monthly tax based on the usage hours.
	 */
	double getPagamento();
	void levantaBicicleta(Ponto *&p1, string tipo, Hora horainicial);
	double devolveBicicleta(Ponto *&p1, Hora horafinal);
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
class PontoNaoExistente{
	string nome;

	string getNome(){
		return nome;
	}

	PontoNaoExistente(string nome){
		this->nome = nome;
	}
};


#endif /* CIDADE_H_ */
