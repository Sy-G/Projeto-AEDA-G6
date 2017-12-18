#include  <iostream>
#include "Bicicleta.h"
#include <vector>

using namespace std;

class Loja
{
	string name;
	int reputacao;
	vector<vector<Bicicleta*> > stock;
public:
	int getReputacao() const;
	string getName() const;
	vector<vector<Bicicleta*> > getStock() const;
	int getNumberByType(string type) const;
	vector<Bicicleta*> getStockByType(string type) const;
	void setReputation(int newreputation);
	bool Buy(string type, int number);
	void printStore();
	bool operator<(const Loja& l1) const;
};

/*
 * @brief Exception
 */
class NoBikesOfThisType
{
	string type;
public:
	NoBikesOfThisType(string type){
	this->type = type;
	};
};
