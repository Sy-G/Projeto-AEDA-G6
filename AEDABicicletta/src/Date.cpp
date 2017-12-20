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

	/*
	istringstream ss;

	string delimiter = "/";
	vector<int> tokenholder;

	size_t pos = 0;
	string token;

	while ((pos = date.find(delimiter)) != std::string::npos) {
	    token = date.substr(0, pos);

	    ss.str(token);

	    int temp;

	    ss >> temp;

	    tokenholder.push_back(temp);
	    date.erase(0, pos + delimiter.length());
	}

	ss.str(date);

	int yeartemp;

	ss >> yeartemp;

	this->day = tokenholder.at(0);
	this->month = tokenholder.at(1);
	this->year = yeartemp;*/
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
