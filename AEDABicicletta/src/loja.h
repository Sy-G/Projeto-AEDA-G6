#include  <iostream>
#include "Bicicleta.h"
#include <vector>
#include <sstream>


using namespace std;

class Loja
{
protected:
	string name;
	int reputacao;
	vector<Bicicleta*> stock;
public:
	Loja(string name, int reputacao);
	Loja(const string & name, const string & other);
	int getReputacao() const;
	string getName() const;
	vector<Bicicleta*> getStock() const;
	int getNumberByType(string type) const;
	void setReputation(int newreputation);
	bool Buy(string type, int number, vector<Bicicleta*>& purchase);
	void addBicicleta(Bicicleta* bike);
	void printStore();
	bool operator<(const Loja& l1) const;
	friend ostream& operator<<(ostream &out, const Loja &p);
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


/*
 * @brief Exception
 */
class InvalidStore
{
public :
	InvalidStore(){};
};


class NotAType2
{
public:
	string type;
	NotAType2(string i):type(i){};
};
