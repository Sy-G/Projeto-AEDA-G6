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
	Hora(string horas);
	Hora();
	Hora(unsigned int horas, unsigned int minutos);
	virtual ~Hora();
	void setHora(unsigned int newhoras, unsigned int newminutos);

};



/**
* @brief Subtracts hora2 from hora1
*
* @param hora1
* @param hora2
*
* @return A double which is the result of the operation in hours with 2 decimal houses
*/
double operator-(Hora hora1, Hora hora2);



/**
* @brief Verifies if hora1 and hora2 are equal
*
* @param hora1
* @param hora2
*
* @return True if hora1 and hora2 are equal, false otherwise
*/
bool operator== (Hora hora1,Hora hora2);




/**
* @brief Verifies if hora1 is less then hora2
*
* @param hora1
* @param hora2
*
* @return True if hora1 less then hora2, false otherwise
*/
bool operator< (Hora hora1,Hora hora2);




/**
* @brief Gets an hour with the right format (hours:minutes)
*
* @param in Input stream
* @param hora Hour to get
*
* @return The input stream
*/



istream& operator>> (istream& in, Hora &hora) ;

/**
* @brief Writes an hour with the right format (hours:minutes)
*
* @param out Output stream
* @param hora Hour to write
*
* @return The output stream
*/
ostream& operator<< (ostream& out, Hora &hora) ;



/**
 * @brief Exception
 */
class HoraInexistente
{
public:
	unsigned int hora;
	unsigned int minutos;
	HoraInexistente(unsigned int horas, unsigned int minutos);
};



/**
 * @brief Exception
 */
class HoraInvalida
{
public:
	HoraInvalida();
};



/**
 * @brief Exception
 */
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
