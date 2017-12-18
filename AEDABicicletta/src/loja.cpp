
#include "loja.h"



int Loja::getReputacao() const
{
	return this->reputacao;
}




string Loja::getName() const
{
	return this->name;
}




vector<vector<Bicicleta*> > Loja::getStock() const
{
	return this->stock;
}




vector<Bicicleta*> Loja::getStockByType(string type) const
{

	for (unsigned int i = 0; i < this->stock.size(); i++)
	{
		if (stock.at(i).at(0)->getTipo() == type)
		   return stock.at(i);
	}
	throw NoBikesOfThisType(type);
}




int Loja::getNumberByType(string type) const
{
	for (unsigned int i = 0; i < this->stock.size(); i++)
	{
		if (stock.at(i).at(0)->getTipo() == type)
		   return stock.at(i).size();
	}
	return -1;
}




void Loja::setReputation(int newreputation)
{
	this->reputacao = newreputation;
}




bool Loja::Buy(string type, int number)
{
	if (this->getNumberByType(type) > number)
		return false;
	for (unsigned int i = 0; i < this->stock.size(); i++)
	{
		if (stock.at(i).at(0)->getTipo() == type)
		{
			for (unsigned int j = 0; j < number; j++)
			{
				stock.at(i).erase(stock.at(i).begin(), stock.at(i).begin() + j);
			}
			return true;
		}
	}
	return false;
}



void Loja::printStore()
{
	cout << "Name : " << this->name << endl;
	cout << "Reputation : " << this->reputacao << endl;
	cout << "Bikes Available : " << endl;
	cout << "  - Urbana : " << this->getNumberByType("Urbana") << endl;
	cout << "  - Urbana Simples : " << this->getNumberByType("Urbana_Simples") << endl;
	cout << "  - Corrida : " << this->getNumberByType("Corrida") << endl;
	cout << "  - Infantil : " << this->getNumberByType("Infantil") << endl;
}



bool Loja::operator <(const Loja &l1) const
{
	return l1.getReputacao() < this->reputacao;
}
