/*
 * Bicicleta.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef BICICLETA_H_
#define BICICLETA_H_
#include <string>
using namespace std;

class Bicicleta
{
protected:
	/**
	 * @brief Bike's ID incremented statically
	 */
	static unsigned int ultimoID;
	/**
	 * @brief Biker's ID
	 */
	unsigned int ID;
public:
	Bicicleta();
	/**
     * @brief Destructor
	 */
	virtual ~Bicicleta();
	/**
	 * @brief This function gets the bike's price
	 */
	virtual double getPrecoportipo() const;
	/**
	 * @brief This function gets a bike's id
	 */
	unsigned int getID() const;

	/**
	 * @brief This function sets a bike's price to newprice
	 *
	 * @param newprice Price to set
	 */
	virtual void setPrecoportipo(double newprice);
	/**
	 * @brief This function gets a bike´s type
	 */
	virtual string getTipo();
};

class Urbana: public Bicicleta
{
protected:
	static  double preco_hora; //Preco por hora, em função do tipo.
public:
	Urbana();
	/**
	 * @brief This function gets the bike's price
	 */
	double getPrecoportipo()const;
	/**
	 * @brief This function sets a bike's price to newprice
	 *
	 * @param newprice Price to set
	 */
	void setPrecoportipo(double newprice);
	/**
	 * @brief This function gets a bike´s type
	 */
	string getTipo();

};

class Urbana_Simples: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Urbana_Simples();
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

class Infantil: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Infantil();
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

class Corrida: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Corrida();
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

#endif /* BICICLETA_H_ */
