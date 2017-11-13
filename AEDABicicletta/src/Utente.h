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
#include "Cidade.h"
#include "Hora.h"
#include <vector>
#include <string>

using namespace std;



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
	static int ultimoID_u;
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
	Utente(string nome, int cordX, int cordY);
	/**
	 * @brief Destructor
	 */
	virtual ~Utente();
	/**
	 * @brief This function obtains a given user's payment, depends if he is a regular or not
	 */
	virtual double getPagamento();
	/**
	 * @brief This function allows a user to withdraw a bike
	 *
	 * @param p1 Reference to the point from which the bike will be withdrawn
	 * @param tipo The kind of bike that will be withdrawn
	 * @param horainicial Time of withdrawal
	 */
	void levantaBicicleta(vector<Ponto>:: iterator p1, string tipo, Hora horainicial);
	/**
	 * @brief This function allows a user to return a bike.
	 *
	 * * @param p1 Reference to the point of return
	 * * @param horafinal Time of return
	 */
	virtual double devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal);
	/**
	 * @brief This function calculates usage time by subtracting withdrawal hour to return hour
	 *
	 * @param horainicial Time of withdrawal
	 * @param horafinal Time of return
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
	 * @brief This function gets a user's ID
	 */
	int getID();
	/**
	 * @brief This function gets a user's Coordinates
	 */
	Coordenadas getCoordenadas();
	/**
	 * @brief This function sets a user's bicycle to b1
	 *
	 * * @param b1 bicycle to set
	 */
	void setBicicleta(Bicicleta *b1);
	/**
	 * @brief This function tells whether a user is an associate or not
	 */
	virtual bool eSocio();
	/**
	 * @brief This function helps print out users in different ways depending if they're associates or regulars
	 */
	 virtual void printUtente(ostream &OutStream) const;
	/**
	 * @brief Overloaded constructor for reading from a file.
	 */
	Utente(const string& name, const string& other);
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
	Regulares(string nome, int cordX, int cordY);
	/**
	 * @brief This function obtains a given user's payment, if he is regular he needs to pay after each use, the amount is given by multiplying usage time with bike price per hour.
	 */
	void levantaBicicleta(vector<Ponto>::iterator p1, string tipo, Hora horainicial);
	double devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal);
	double getPagamento(); //multiplica o tempo pelo preco por hora da bicleta correspondente.
	bool eSocio();
	Regulares(const string& name, const string& other);
	void printUtente(ostream &OutStream) const;
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
	Socio(string nome, int cordX, int cordY);
	/**
	 * @brief This function obtains a given user's payment, in this case the user will accumulate hours until it's the end of the month, at that time it will checkout and calculate the user's monthly tax based on the usage hours.
	 */
	double getPagamento();
	void levantaBicicleta(vector<Ponto>::iterator p1, string tipo, Hora horainicial);
	double devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal);
	bool eSocio();
	Socio(const string& name, const string& other);
	void printUtente(ostream &OutStream) const;
};

#endif /* UTENTE_H_ */
