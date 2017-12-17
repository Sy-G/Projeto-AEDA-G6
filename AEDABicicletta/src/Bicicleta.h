/*
 * Bicicleta.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef BICICLETA_H_
#define BICICLETA_H_
#include <string>
#include "Date.h"

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
	/**
	 * @brief Date of disassembly for broken bikes
	 */
	Date date;
public:
	/**
     * @brief Creates a bike
	 */
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
	 * @brief This function gets the bike's id
	 */
	unsigned int getID() const;

	/**
	 * @brief This function gets the bike큦 type
	 */
	virtual string getTipo();

	/**
	 * @brief This function gets the bike큦 disassembly date
	 */
	string getDate() const;

	/**
	 * @brief This function sets the bike큦 disassembly date
	 */
	void setDate(Date d1);
};



class Urbana: public Bicicleta
{
protected:
	static  double preco_hora; //Preco por hora, em fun豫o do tipo.
public:
	/**
	 * @brief Creates a bike of type "Urbana"
	 */
	Urbana();
	/**
	 * @brief This function gets the bike's price
	 */
	double getPrecoportipo()const;

	/**
	 * @brief This function gets the bike큦 type
	 */
	string getTipo();

	/**
	 * @brief This function gets the bike's price
	 */
	static double getPreco() {return Urbana::preco_hora; };

	/**
	 * @brief This function sets a bike's price to newprice
	 *
	 * @param newprice Price to set
	 */
	static void setPrecoportipo(double newprice) {Urbana::preco_hora = newprice;};
};



class Urbana_Simples: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	/**
	 * @brief Creates a bike of type "Urbana Simples"
	 */
	Urbana_Simples();
	/**
	 * @brief This function gets the bike's price
	 */
	 double getPrecoportipo()const;

	/**
	 * @brief This function gets the bike큦 type
	 */
	string getTipo() ;

	/**
	 * @brief This function gets the bike's price
	 */
	static double getPreco() {return Urbana_Simples::preco_hora; };

    /**
     * @brief This function sets a bike's price to newprice
	 *
	 * @param newprice Price to set
	 */
	static void setPrecoportipo(double newprice) {Urbana_Simples::preco_hora = newprice;};
};



class Infantil: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	/**
	 * @brief Creates a bike of type "Infantil"
	 */
	Infantil();
	/**
	 * @brief This function gets the bike's price
	 */
	double getPrecoportipo()const;
	/**
	 * @brief This function gets the bike큦 type
	 */
	string getTipo() ;

	/**
	 * @brief This function gets the bike's price
	 */
	static double getPreco() {return Infantil::preco_hora; };

    /**
	 * @brief This function sets a bike's price to newprice
	 *
	 * @param newprice Price to set
	 */
	static void setPrecoportipo(double newprice) {Infantil::preco_hora = newprice;};
};

class Corrida: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	/**
	 * @brief Creates a bike of type "Corrida"
	 */
	Corrida();
	/**
	 * @brief This function gets the bike's price
	 */
	double getPrecoportipo()const;
	/**
	 * @brief This function gets the bike큦 type
	 */
	string getTipo() ;

	/**
	 * @brief This function gets the bike's price
	 */
	static double getPreco() {return Corrida::preco_hora; };

	 /**
	  * @brief This function sets a bike's price to newprice
	  *
	  * @param newprice Price to set
	  */
	static void setPrecoportipo(double newprice) {Corrida::preco_hora = newprice;};

};



#endif /* BICICLETA_H_ */
