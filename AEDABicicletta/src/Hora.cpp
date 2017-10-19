/*
 * Hora.cpp
 *
 *  Created on: 19/10/2017
 *      Author: Work
 */

#include "Hora.h"
#include <sstream>

Hora::Hora(string hora) {
	istringstream is;
	char delim = ':';

	is.str(hora);

	is >> this->hora >> delim >> this->minutos;
}

Hora::~Hora() {
	// TODO Auto-generated destructor stub
}

