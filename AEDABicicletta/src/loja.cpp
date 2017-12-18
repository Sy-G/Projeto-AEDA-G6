
#include "loja.h"


Loja::Loja(string name, int reputacao)
{
	this->name = name;
	this->reputacao = reputacao;
	this->stock.clear();
}



Loja::Loja(const string & name, const string & other)
{
	istringstream in;
	in.str(other);
	this->name = name;

	in >> reputacao;
	if(in.fail())
		throw InvalidStore();

	while(in.good())
	{
		char bicycle;
		in >> bicycle;
		if(in.fail())
			break;
		if(bicycle == 'C')
			addBicicleta(new Corrida);
		else if(bicycle == 'U')
			addBicicleta(new Urbana);
		else if(bicycle == 'S')
			addBicicleta(new Urbana_Simples);
		else if(bicycle == 'I')
			addBicicleta(new Infantil);
		else
			throw NotAType2("");

	}
}


int Loja::getReputacao() const
{
	return this->reputacao;
}




string Loja::getName() const
{
	return this->name;
}




vector<Bicicleta*> Loja::getStock() const
{
	return this->stock;
}




int Loja::getNumberByType(string type) const
{
	int counter = 0;
	for (unsigned int i = 0; i < this->stock.size(); i++)
	{
		if (stock.at(i)->getTipo() == type)
		  counter++;
	}
	return counter;
}




void Loja::setReputation(int newreputation)
{
	this->reputacao = newreputation;
}




bool Loja::Buy(string type, int number, vector<Bicicleta*>& purchase)
{
	int counter = 0;
	if (this->getNumberByType(type) > number)
		return false;
	for (unsigned int i = 0; i < this->stock.size(); i++)
	{
		if (counter >= number)
			return true;
		if (stock.at(i)->getTipo() == type)
		{
			purchase.push_back(stock.at(i));
			stock.erase(stock.begin() + i);
			counter++;
		}
	}
	return false;
}



void Loja::printStore()
{
	cout << "Name : " << this->name << endl;
	cout << "Reputation : " << this->reputacao << endl;
	cout << " Number of bikes available : " << this->stock.size() << endl;
	cout
	<< " Urbana : " << this->getNumberByType("Urbana") << "; "
    << " Urbana Simples : " << this->getNumberByType("Urbana_Simples") << "; "
    << " Corrida : " << this->getNumberByType("Corrida") << "; "
	<< " Infantil : " << this->getNumberByType("Infantil") << endl;
}



ostream& operator<<(ostream &out, const Loja &p)
{
	out << p.name << endl;
	out << p.reputacao << " " ;

	for(size_t i = 0; i < p.stock.size(); i++)
	{
		if (p.stock.at(i)->getTipo() == "Corrida")
			out << "C ";
		else if (p.stock.at(i)->getTipo() == "Urbana")
			out << "U ";
		else if (p.stock.at(i)->getTipo() == "Urbana_Simples")
			out << "S ";
		else if (p.stock.at(i)->getTipo() == "Infantil")
			out << "I ";
	}
	return out;
}



bool Loja::operator <(const Loja &l1) const
{
	return l1.getReputacao() < this->reputacao;
}




void Loja::addBicicleta(Bicicleta* bike)
{
	this->stock.push_back(bike);
}
