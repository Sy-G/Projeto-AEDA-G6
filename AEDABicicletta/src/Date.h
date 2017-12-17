/*
 * Date.h
 *
 *  Created on: 17/12/2017
 *
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_

#include <string>

using namespace std;

class Date {
int day;
int month;
int year;
public:
	Date(string date);
	Date();
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	virtual ~Date();
};

#endif /* SRC_DATE_H_ */
