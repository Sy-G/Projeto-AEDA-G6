#include "Part.h"
#include <iostream>

Part::Part(const std::string& namePart, const std::string& supplier,
		double unitPrice){
	this->name_part = namePart;
	this->supplier = supplier;
	this->unit_price = unitPrice;
}

const std::string& Part::getNamePart() const {
	return name_part;
}

void Part::setNamePart(const std::string& namePart) {
	name_part = namePart;
}

const std::string& Part::getSupplier() const {
	return supplier;
}

double Part::getUnitPrice() const {
	return unit_price;
}

void Part::setUnitPrice(double unitPrice) {
	unit_price = unitPrice;
}

void Part::setSupplier(const std::string& supplier) {
	this->supplier = supplier;
}

bool Part::operator <(const Part& p1) const {
	return (this->name_part < p1.name_part) ||
			(this->name_part == p1.name_part && this->unit_price < p1.unit_price);
}

bool Part::operator ==(const Part& p1) const{
	return (this->name_part == p1.name_part);
}

std::ostream& operator <<(std::ostream& out, const Part& p1)
{
	out << p1.getNamePart() << ' ' //std::endl
			<< p1.getSupplier() << ' ' //std::endl
			<< p1.getUnitPrice() << ' '; //std::endl;
	return out;
}
