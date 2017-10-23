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
	unsigned int ID;
public:
	Bicicleta(unsigned int ID);
	virtual ~Bicicleta();
	virtual double getPrecoportipo() const;
	unsigned int getID() const;
	virtual void setPrecoportipo(double newprice);

};

class Urbana: public Bicicleta
{
protected:
	static  double preco_hora; //Preco por hora, em função do tipo.
public:
	Urbana(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);

};

class Urbana_Simples: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Urbana_Simples(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);

};

class Infantil: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Infantil(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);

};

class Corrida: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Corrida(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);

};

#endif /* BICICLETA_H_ */
