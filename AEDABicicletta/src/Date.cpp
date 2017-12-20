/*
 * Date.cpp
 *
 *  Created on: 17/12/2017
 *
 */

#include "Date.h"
#include <sstream>


Date::Date(){
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(string date) {
	istringstream ss;

	ss.str(date);

	char delim = '/';

	ss >> day >> delim >> month >> delim >> year;
}

int Date::getDay() const{
	return day;
}

int Date::getMonth() const{
	return month;
}

int Date::getYear() const{
	return year;
}

Date::~Date() {
	// TODO Auto-generated destructor stub
}


