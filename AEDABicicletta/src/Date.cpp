/*
 * Date.cpp
 *
 *  Created on: 17/12/2017
 *
 */

#include "Date.h"
#include <sstream>
#include <vector>

Date::Date(){
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(string date) {
	istringstream ss;

	ss.str(date);

	char delim = '/';

	int daytemp, monthtemp, yeartemp;

	ss >> daytemp >> delim >> monthtemp >> delim >> yeartemp;

	this->day = daytemp;
	this->month = monthtemp;
	this->year = yeartemp;
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
