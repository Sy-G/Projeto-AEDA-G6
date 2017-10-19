/*
 * Bicicleta.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef BICICLETA_H_
#define BICICLETA_H_

class Bicicleta {
protected:
	unsigned int ID;
public:
	Bicicleta();
	virtual ~Bicicleta();
	virtual double getPrecoportipo();
};

class Urbana: public Bicicleta{
protected:
	static  double preco_hora; //Preco por hora, em função do tipo.
public:
	Urbana(unsigned int ID);
	double getPrecoportipo();
};

class Urbana_Simples: public Bicicleta{
protected:
	static  double preco_hora;
	int velocidade; //velocidade única em (m/s)
public:
	Urbana_Simples(unsigned int ID, int velocidade);
	double getPrecoportipo();
};

class Infantil: public Bicicleta{
protected:
	static  double preco_hora;
public:
	Infantil(unsigned int ID);
	double getPrecoportipo();
};

class Corrida: public Bicicleta{
protected:
	static  double preco_hora;
public:
	Corrida(unsigned int ID);
	double getPrecoportipo();
};

#endif /* BICICLETA_H_ */
