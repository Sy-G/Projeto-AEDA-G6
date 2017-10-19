/*
 * Hora.h
 *
 *  Created on: 19/10/2017
 *      Author: Work
 */

#ifndef SRC_HORA_H_
#define SRC_HORA_H_

#include <string>
using namespace std;

class Hora {
public:
	unsigned int hora;
	unsigned int minutos;

	Hora(string hora);
	virtual ~Hora();
};

#endif /* SRC_HORA_H_ */
