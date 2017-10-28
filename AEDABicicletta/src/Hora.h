/*
 * Hora.h
 *
 *  Created on: 19/10/2017
 *      Author: Work
 */

#ifndef SRC_HORA_H_
#define SRC_HORA_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Hora
{
public:
	unsigned int hora;
	unsigned int minutos;

	//Hora(string horas);
	Hora(string horas);
	Hora();
	Hora(unsigned int horas, unsigned int minutos);
	virtual ~Hora();
	void setHora(unsigned int newhoras, unsigned int newminutos);

};

double operator-(Hora hora1, Hora hora2);
bool operator== (Hora hora1,Hora hora2);
bool operator< (Hora hora1,Hora hora2);
istream& operator>> (istream& in, Hora &hora) ;
ostream& operator>> (ostream& out, Hora &hora) ;


class HoraInexistente
{
public:
	unsigned int hora;
	unsigned int minutos;
	HoraInexistente(unsigned int horas, unsigned int minutos);

};

class HorasInvalidas
{
public:
	unsigned int horainicio;
	unsigned int minutosinicio;
	unsigned int horafim;
	unsigned int minutosfim;
	HorasInvalidas(unsigned int horasinicio, unsigned int minutosinicio, unsigned int horasfim, unsigned int minutosfim);
};



#endif /* SRC_HORA_H_ */
