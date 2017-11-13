/*
 * Cidade.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"
#include "Ponto.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>

Cidade::Cidade() {
}

vector<Ponto>::iterator Cidade::isThereSpace()
{
	vector<Ponto>::iterator iter = find_if(pontos.begin(), pontos.end(), isThereSpaceInPoint);

	if(iter == pontos.end())
		throw NoSpace(0);
	else
		return iter;
}


Cidade::~Cidade()
{
	for(size_t i = 0; i < pontos.size(); i++)
	{
		for(size_t j = 0; j < pontos.at(i).getBicicletas().size(); j++)
		{
			delete pontos.at(i).getBicicletas().at(j);
		}
	}

	for(size_t i = 0; i < utentes.size(); i++)
	{
		delete utentes.at(i)->getBicicleta();
	}

	for(size_t i = 0; i < utentes.size(); i++)
	{
		delete utentes.at(i);
	}

}

vector<Ponto>& Cidade::getPontos(){
	return pontos;
}

Cidade& Cidade::sortPointsByDistance(Coordenadas c1)
{
	for(size_t i = 0; i < pontos.size(); i++)
	{
		pontos.at(i).setDistanceCoords(c1);
		pontos.at(i).setDistance(distance_between_coordinates(pontos.at(i).getCoord(),c1));
	}

	sort(pontos.begin(), pontos.end());
	return *this;
}

Cidade& Cidade::addPoint(Ponto p1)
{
	try
	{
		findPoint(p1.getNome());
	}
	catch(NotAPoint &p)
	{
		pontos.push_back(p1);
		return *this;
	}

	throw existentPoint(p1.getNome());
}

Cidade& Cidade::addUtente(Utente* u1)
{
	utentes.push_back(u1);
	return *this;
}

vector<Ponto>::iterator Cidade::isThereBicycle(string bicycle)
{
	vector<Ponto>::iterator iter = pontos.begin();
	if(bicycle == "Urbana_Simples")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereUrbanaSimples)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Urbana")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereUrbana)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Infantil")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereInfantil)) != pontos.end())
			return iter;
	}
	else if(bicycle == "Corrida")
	{
		if((iter = find_if(pontos.begin(), pontos.end(), isThereCorrida)) != pontos.end())
			return iter;
	}
	else
		throw NotAType(bicycle);
	throw NoPoint();

	//return pontos.end();
}

vector<Ponto>::iterator Cidade::closestType(Coordenadas coord, string type)
{
	sortPointsByDistance(coord);
	return isThereBicycle(type);
}

vector<Ponto>::iterator Cidade::closestSpace(Coordenadas coord)
{
	sortPointsByDistance(coord);
	return isThereSpace();
}

vector<Ponto>::iterator Cidade::findPoint(string name)
{
	vector<Ponto>::iterator iter;
	Ponto p1(name, 0, Coordenadas());
	if((iter = find(pontos.begin(), pontos.end(), p1)) == pontos.end())
		throw NotAPoint(name);
	return iter;
}

bool Cidade::findPoint(double x, double y)
{
	int index = -1;
	for (unsigned int i = 0; i < pontos.size(); i++)
	{
		if ((pontos.at(i).getCoord().cordX == x ) && (pontos.at(i).getCoord().cordY == y))
		{
			index = i;
			break;
		}
	}
	if (index == -1)
		return false;
	else
		return true;
}


Utente* Cidade::findUtente(int id)
{
	int index = -1;
	for (unsigned int i = 0; i < utentes.size(); i++)
	{
		if (utentes.at(i)->getID() == id)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
		throw NoUserFound(id);
	return utentes.at(index);
}

Cidade& Cidade::removeUtente(int id)
{
	int index = -1;
	for (unsigned int i = 0; i < utentes.size(); i++)
	{
		if (utentes.at(i)->getID() == id)
		{
			index = i;
			utentes.erase(utentes.begin() + i);
			break;
		}
	}
	if (index == -1)
		throw NoUserFound(id);
	return *this;
}

Cidade& Cidade::removePonto(string name)
{
	int index = -1;
	for (unsigned int i = 0; i < pontos.size(); i++)
	{
		if (pontos.at(i).getNome() == name)
		{
			index = i;
			pontos.erase(pontos.begin() + i);
			break;
		}
	}

	if (index == -1)
		throw NotAPoint(name);
	return *this;
}


bool operator<(const pair<Ponto *, float> &p1, const pair<Ponto *, float> &p2)
{
	return p1.second > p2.second;
}


vector<Bicicleta*> Cidade::redistributeBikes()
{
	vector<Bicicleta *> corrida;
	vector<Bicicleta *> urbana_simples;
	vector<Bicicleta *> urbana;
	vector<Bicicleta *> infantil;
	unsigned int total_capacity = 0;

	for(size_t i = 0; i < pontos.size(); i++)
	{
		total_capacity += pontos.at(i).getCapacidade();

		for(size_t j = 0; j < pontos.at(i).getBicicletas().size(); j++)
		{
			if(pontos.at(i).getBicicletas().at(j)->getTipo() == "Corrida")
			{
				corrida.push_back(pontos.at(i).getBicicletas().at(j));
			}
			if(pontos.at(i).getBicicletas().at(j)->getTipo() == "Urbana")
			{
				urbana.push_back(pontos.at(i).getBicicletas().at(j));
			}
			if(pontos.at(i).getBicicletas().at(j)->getTipo() == "Urbana_Simples")
			{
				urbana_simples.push_back(pontos.at(i).getBicicletas().at(j));
			}
			if(pontos.at(i).getBicicletas().at(j)->getTipo() == "Infantil")
			{
				infantil.push_back(pontos.at(i).getBicicletas().at(j));
			}
		}

		pontos.at(i).setBicicletas(vector<Bicicleta*>());
	}

	vector<Bicicleta *> ret;
	float percentage = corrida.size()/(float)total_capacity;
	vector<Bicicleta *> tmp = redistributeVector(corrida, percentage);
	ret.insert(ret.begin(), tmp.begin(), tmp.end());
	tmp.clear();

	percentage = urbana.size()/(float)total_capacity;
	tmp = redistributeVector(urbana, percentage);
	ret.insert(ret.begin(), tmp.begin(), tmp.end());
	tmp.clear();

	percentage = urbana_simples.size()/(float)total_capacity;
	tmp = redistributeVector(urbana_simples, percentage);
	ret.insert(ret.begin(), tmp.begin(), tmp.end());
	tmp.clear();

	percentage = infantil.size()/(float)total_capacity;
	tmp = redistributeVector(infantil, percentage);
	ret.insert(ret.begin(), tmp.begin(), tmp.end());
	tmp.clear();
	return ret;
}

vector<Bicicleta*> Cidade::redistributeVector(vector<Bicicleta*>& v, float percentage)
{
	vector<pair<Ponto *, float> > set_v;
	for(size_t i = 0; i < pontos.size(); i++)
	{
		set_v.insert(set_v.begin(),make_pair(&pontos.at(i), percentage * pontos.at(i).getCapacidade()));
	}

	sort(set_v.begin(), set_v.end());
	while (v.size() > 0)
	{
		if(set_v.begin()->second > 0)
		{
			//			cout << "HERE\n";
			set_v.begin()->first->addBicicleta(v.at(0));
			v.erase(v.begin());
			set_v.begin()->second--;
			sort(set_v.begin(), set_v.end());
		}
		else
		{
			//			cout << "here\n";
			break;
		}

		//		cout << "Size: " << v.size() << endl;
	}
	//	cout << "END\n";
	return v;
}

vector<Bicicleta*> Cidade::testOccupation()
{
	double average_occupancy_percentage = 0;
	for(size_t i = 0; i < pontos.size(); i++)
	{
		average_occupancy_percentage += pontos.at(i).getnumbicicletasDisponiveis()/(double)pontos.at(i).getCapacidade();
	}

	average_occupancy_percentage /= (double)pontos.size();
	double standard_deviation = 0;
	for(size_t i = 0; i < pontos.size(); i++)
	{
		standard_deviation += (pontos.at(i).getnumbicicletasDisponiveis()/(double)pontos.at(i).getCapacidade() - average_occupancy_percentage) * (pontos.at(i).getnumbicicletasDisponiveis()/(double)pontos.at(i).getCapacidade() - average_occupancy_percentage);
		//		cout << standard_deviation << endl;
	}

	standard_deviation = sqrt(standard_deviation);
	//	cout << endl << standard_deviation << endl << endl;

	if(standard_deviation < 0.3)
		throw NoRedistributionNeeded();
	else
		return redistributeBikes();
}

void Cidade::printPoints(ostream& out)
{
	for(size_t i = 0; i < pontos.size(); i++)
		out << pontos.at(i) << endl;
}

void Cidade::printPointsinMenu()
{
	for (unsigned int i = 0; i < pontos.size(); i++)
	{
		int ucounter = 0;
		int uscounter = 0;
		int icounter = 0;
		int ccounter = 0;
		cout <<"Name: " <<pontos.at(i).getNome() << endl;
		cout << "Coordinates: " << pontos.at(i).getCoord().cordX << "," << pontos.at(i).getCoord().cordY << endl;
		cout << "Capacity: " << pontos.at(i).getCapacidade() << endl;
		cout << "Number of bikes available: " << pontos.at(i).getBicicletas().size() << endl;
		for (unsigned int j = 0; j < pontos.at(i).getBicicletas().size(); j++)
		{
			if (pontos.at(i).getBicicletas().at(j)->getTipo() == "Urbana")
				ucounter++;
			if (pontos.at(i).getBicicletas().at(j)->getTipo() == "Urbana_Simples")
				uscounter++;
			if (pontos.at(i).getBicicletas().at(j)->getTipo() == "Infantil")
				icounter++;
			if (pontos.at(i).getBicicletas().at(j)->getTipo() == "Corrida")
				ccounter++;
		}
		cout  << "Urbana: " << ucounter << "; Urbana_Simples: " << uscounter << "; Infantil: " << icounter << "; Corrida: "  << ccounter << endl;
		cout << endl;
	}
}

void Cidade::printUsers()
{
	for(unsigned int i = 0; i < utentes.size(); i++){
		{
			utentes.at(i)->printUtente(cout);
			cout << endl;
		}
	}
}

void Cidade::printPointsFile(const string& file)
{

	ofstream out(file.c_str());
	if(out.is_open())
		printPoints(out);
	out.close();
}


void Cidade::readPoints(const string& file)
{
	vector<Ponto> v_p;
	ifstream in(file.c_str());
	if(in.is_open())
	{
		while(in.good())
		{
			try
			{
				string name;
				getline(in, name);
				if(!in.good())
				{

					throw InvalidPoint();
				}
				string other;
				getline(in, other);
				v_p.push_back(Ponto(name,other));

			}
			catch(InvalidPoint &e)
			{
				for(size_t i = 0; i < v_p.size(); i++)
					v_p.at(i).deleteBicycles();
				throw InvalidFile();
			}

		}

		try
		{
			for(size_t i = 0; i < v_p.size(); i++)
				addPoint(v_p.at(i));
		}
		catch(existentPoint& e)
		{
			throw InvalidFile();
		}

		in.close();
		return;
	}
	else
	{
		throw NotAFile(file);
	}
}

void Cidade::readUsers(const string& file){
	vector<Utente *> v_p;
	ifstream in(file.c_str());

	if(in.is_open())
	{
		try
		{
			while(in.good())
			{
				string ident;
				getline(in, ident);

				string name;
				getline(in, name);

				string other;
				getline(in, other);

				if(ident == "Socio"){
					v_p.push_back(new Socio(name,other));
				}

				if(ident == "Regular"){
					v_p.push_back(new Regulares(name,other));
				}
				else
					throw NotAType(ident);
			}


		}
		catch(...)
		{
			cout << "Here\n";
			for(size_t i = 0; i < v_p.size(); i++){
				if (v_p.at(i) != NULL)
					delete v_p.at(i);
			}
			throw InvalidFile();
		}
		for(size_t i = 0; i < v_p.size(); i++){
			this->addUtente(v_p.at(i));
		}
	}
	else
	{
		throw NotAFile(file);
	}
}

void Cidade::printUserstoFile(const string& file){
	ofstream out(file.c_str());
	if(out.is_open()){
		for(unsigned int i = 0; i < utentes.size(); i++){
			if(utentes.at(i)->eSocio()){
				out << "Socio" << endl;
			} else out << "Regular" << endl;
			out << utentes.at(i)->getNome() << endl;
			out << utentes.at(i)->getCoordenadas().cordX << " " << utentes.at(i)->getCoordenadas().cordY << endl;
		}
	}
	out.close();
}
