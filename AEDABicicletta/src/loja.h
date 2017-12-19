#include  <iostream>
#include "Bicicleta.h"
#include <vector>
#include <sstream>


using namespace std;

class Loja
{
protected:


	/**
	 * @brief Store's name
	 */
	string name;
	/**
	 * @brief Store's reputation
	 */
	int reputacao;
	/**
	 * @brief  Holds pointers to the bicycles that are currently in the store's stock
	 */
	vector<Bicicleta*> stock;


public:
	/**
	 * @brief Creates a store with no bicycles attached to it
	 *
	 * @param nome Store's name
	 *
	 * @param reputacao Store's reputation
	 */
	Loja(string name, int reputacao);


    /**
	 * @brief Creates store from strings
	 *
	 * @param name name of the store
	 *
	 * @param other other parameters
	 */
	Loja(const string & name, const string & other);


	/**
	 * @brief Gets the store's reputation
	 *
	 * @return The store's reputation
	 */
	int getReputacao() const;


	/**
	 * @brief Gets the store's name
	 *
	 * @return The store's name
	 */
	string getName() const;


	/**
	 * @brief Gets the store's stock
	 *
	 * @return The store's stock
	 */
	vector<Bicicleta*> getStock() const;


	/**
	 * @brief Gets the number of bikes of type type in the store's stock
	 *
	 * @param type Bike type
	 *
	 * @return The number of bikes of type type in the store's stock
	 */
	int getNumberByType(string type) const;


	/**
	 * @brief Sets the reputation of the store
	 *
	 * @param newreputation The store's new reputation
	 */
	void setReputation(int newreputation);


	/**
	 * @brief Buys number amount of bikes of type type
	 *
	 * @param type Type of Bike
	 * @param number Amount of bikes to purchase
	 * @param purchase Vector that will contain the bikes purchased
	 *
	 * @return True if the purchase was successful, False otherwise
	 */
	bool Buy(string type, int number, vector<Bicicleta*>& purchase);


	/**
	 * @brief Adds a bike to the store
	 *
	 * @param bike Bike to be added
	 */
	void addBicicleta(Bicicleta* bike);


	/**
	 * @brief Prints the stores members
	 */
	void printStore();


    /**
	 * @brief True if the object that its applied has a smaller reputation than l1
	 *
	 * @param l1 Store to compare to
	 *
	 * @return Boolean
	 */
	bool operator<(const Loja& l1) const;


	/**
	 *	@brief outputs a store in text
	 *
	 *	@param out stream to output to
	 *	@param p store to print
	 *
	 *	@return output stream
	 */
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
