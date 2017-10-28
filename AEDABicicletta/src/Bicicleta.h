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
	static unsigned int ultimoID;
	unsigned int ID;
public:
	Bicicleta();
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
	Urbana();
	double getPrecoportipo()const;
	void setPrecoportipo(double newprice);
	string getTipo() ;

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
