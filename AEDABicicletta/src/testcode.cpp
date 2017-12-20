/*
 * testcode.cpp
 *
 *  Created on: 20/12/2017
 *      Author: Work
 */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool checkdate(string date){
	istringstream ss;

	ss.str(date);

	char delim = '/';

	int day, month, year;

	ss >> day >> delim >> month >> delim >> year;

	if(month < 1 || month > 12){
		return false;
	}

	if(month == 1){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 2){
		if(day >= 1 && day <= 29){
			return true;
		} else return false;
	}

	if(month == 3){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 4){
		if(day >= 1 && day <= 30){
			return true;
		} else return false;
	}

	if(month == 5){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 6){
		if(day >= 1 && day <= 30){
			return true;
		} else return false;
	}

	if(month == 7){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 8){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 9){
		if(day >= 1 && day <= 30){
			return true;
		} else return false;
	}

	if(month == 10){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}

	if(month == 11){
		if(day >= 1 && day <= 30){
			return true;
		} else return false;
	}

	if(month == 12){
		if(day >= 1 && day <= 31){
			return true;
		} else return false;
	}
}
