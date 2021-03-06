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
#include <cmath>


//
//Hora::Hora(string horas)
//{
//	istringstream is;
//	char delim = ':';
//
//	is.str(horas);
//
//	is >> this->hora >> delim >> this->minutos;
//}


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
	if ( (hora1 == hora2) || (hora1 < hora2))
		throw HorasInvalidas(hora1.hora, hora1.minutos, hora2.hora, hora2.minutos);
	else
	{
		unsigned int totalminutes = hora1.hora * 60 + hora1.minutos;
		unsigned int totalminuteshora2 = hora2.hora * 60 + hora2.minutos;
		unsigned int result = totalminutes - totalminuteshora2;
		return (double) floor((result/60.0) * 100 + 0.5)/100;
	}
}

bool operator== (Hora hora1, Hora hora2)
		{
	if( (hora1.hora == hora2.hora) && (hora1.minutos == hora2.minutos))
		return true;
	else
		return false;
		}

bool operator< (Hora hora1,Hora hora2)
{
	unsigned int totalminutes = hora1.hora * 60 + hora1.minutos;
	unsigned int totalminuteshora2 = hora2.hora * 60 + hora2.minutos;
	return totalminutes < totalminuteshora2;

}


istream& operator>> (istream& in, Hora &hora)
{
	string hora_s;
	in >> hora_s;

	unsigned int index =  hora_s.find_first_of(':');
	if(index == string::npos)
		throw HoraInvalida();

	hora.hora = 0;
	string tmp =  hora_s.substr(0,index);
	for(size_t i = 0; i < tmp.size(); i++)
	{
		hora.hora *= 10;
		if(tmp.at(i) >= '0' && tmp.at(i) <= '9')
			hora.hora += tmp.at(i) - '0';
		else
			throw HoraInvalida();
	}

	hora.minutos = 0;
	tmp =  hora_s.substr(index+1,hora_s.size());
	for(size_t i = 0; i < tmp.size(); i++)
	{
		hora.minutos *= 10;
		if(tmp.at(i) >= '0' && tmp.at(i) <= '9')
			hora.minutos += tmp.at(i) - '0';
		else
			throw HoraInvalida();
	}

	if ((hora.hora > 23) || (hora.hora < 0))
		throw HoraInexistente(hora.hora,hora.minutos);
	else
	{
		if  ((hora.minutos > 59) || (hora.minutos < 0))
			throw HoraInexistente(hora.hora,hora.minutos);
	}

	return in;
}

ostream& operator<< (ostream& out, Hora &hora)
{
	out << hora.hora << ":" << hora.minutos;
	return out;
}

HoraInexistente::HoraInexistente(unsigned int horas, unsigned int minutos)
{
	this->hora = horas;
	this->minutos = minutos;
}

HoraInvalida::HoraInvalida()
{
}

HorasInvalidas::HorasInvalidas(unsigned int horasinicio, unsigned int minutosinicio, unsigned int horasfim, unsigned int minutosfim)
{
	this->horainicio = horasinicio;
	this->minutosinicio = minutosinicio;
	this->horafim = horasfim;
	this->minutosfim = minutosfim;
}
