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
	/**
	 * @brief Holds the hours
     */
	unsigned int hora;
	/*
	 * @brief Holds the minutes
	 * */
	unsigned int minutos;
	/**
	 * @brief Creates an Hour using a string int the format hours:minutes
	 *
	 * @param horas String that contains the hours
	 */
	Hora(string horas);
	/**
	 * @brief Creates an Hour with with hora ans minutos equal to zero
     */
	Hora();
	/**
	 * @brief Creates an Hour
	 *
	 * @param horas Hours of the hour
	 * @param minutos Minutes of the hour
	 */
	Hora(unsigned int horas, unsigned int minutos);
	/**
	 * @brief Destructor
	 */
	virtual ~Hora();

	/**
	 * @brief Sets the hour values
	 *
	 * @param newhoras New hours of the hour
	 * @param newminutos New minutes of the hour
	 */
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
