/*
 * Hora.cpp
 *
 *  Created on: 19/10/2017
 *      Author: Work
 */

#include "Hora.h"
#include <sstream>
#include <string>
#include <iostream>



/*Hora::Hora(string horas)
{
	istringstream is;
	char delim = ':';

	is.str(horas);

	is >> this->hora >> delim >> this->minutos;

	 por no menu; assim o construtor nao tem de ser com string.....
	cout << "hora?" << endl;
	int horas, minutos;
	char c;
	cin >> horas >> c >> minutos;
	cout << horas << endl;
	cout << c << endl;
	cout << minutos << endl;
}*/


Hora::Hora() {
	this->hora = 0;
	this->minutos = 0;
}

Hora::Hora(unsigned int horas, unsigned int minutos)
{
	this->hora = horas;
	this->minutos = minutos;
}

Hora::~Hora() {
	// TODO Auto-generated destructor stub
}

void Hora::setHora(unsigned int newhoras, unsigned int newminutos)
{
	this->hora = newhoras;
	this->minutos = newminutos;
}

double operator-(Hora hora1, Hora hora2)
{
   unsigned int totalminutes = hora1.hora * 60 + hora1.minutos;
   unsigned int totalminuteshora2 = hora2.hora * 60 + hora2.minutos;
   unsigned int result = totalminutes - totalminuteshora2;

   return (double) result/60;
}

bool operator== (Hora hora1, Hora hora2)
{
	bool equal = false;
    if( (hora1.hora = hora2.hora) && (hora1.minutos = hora2.minutos))
    	equal = true;
	return equal;
}


HoraInexistente::HoraInexistente(unsigned int horas, unsigned int minutos)
{
	this->hora = horas;
	this->minutos = minutos;
}







