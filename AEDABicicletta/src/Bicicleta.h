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
	virtual string getTipo();

};

class Urbana: public Bicicleta
{
protected:
	static  double preco_hora; //Preco por hora, em função do tipo.
public:
	Urbana(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

class Urbana_Simples: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Urbana_Simples(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

class Infantil: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Infantil(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

class Corrida: public Bicicleta
{
protected:
	static  double preco_hora;
public:
	Corrida(unsigned int ID);
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

};

#endif /* BICICLETA_H_ */
