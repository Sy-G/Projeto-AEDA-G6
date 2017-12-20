/*
 * Cidade.h
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#ifndef CIDADE_H_
#define CIDADE_H_


#include "Hora.h"
#include "Coordenadas.h"
#include "Bicicleta.h"
#include "Ponto.h"
#include "Utente.h"
#include "loja.h"
#include "Part.h"
#include <vector>
#include <queue>
#include <set>
#include <tr1/unordered_set>

using namespace std;

//this structure will be used to keep track of bicycles sent to be disassembled via dispersion table
struct BicicleHash {

	int operator() (const Bicicleta& b1) const{
		//hash function, used to promote efficient collision-resolution
		return b1.getID();
	}

	bool operator() (const Bicicleta& b1, const Bicicleta b2) const{
		//comparison function, two bicycles are only the same if they have the same ID.

		if(b1.getID() == b2.getID()){
			return true;
		} else return false;
	}

};

typedef tr1::unordered_set<Bicicleta, BicicleHash, BicicleHash> HashTabBicycle;

/**
 * @brief Exception
 */
class NotAType
{
public:
	string type;
	NotAType(string i):type(i){};
};

/**
 * @brief Exception
 */
class NoPoint
{
public:
	NoPoint(){};
};


typedef priority_queue<Loja> HEAP_LOJAS;

class Cidade {
protected:
	vector<Ponto> pontos;
	vector<Utente *> utentes;
	string nome;
	HashTabBicycle brokenbikes;
	HEAP_LOJAS  lojas;
	multiset<Part> parts;
public:
	vector<Ponto>& getPontos();
	/**
	 * @brief Sorts point from the closer to farthest point according to some given coordinate.
	 *
	 * @param c1 Coordinates to sort by.
	 *
	 * @return reference to the new point vector
	 */
	Cidade& sortPointsByDistance(Coordenadas c1);


	/**
	 * @brief Adds a point to the array
	 *
	 * @param p1 Point to add
	 */
	Cidade& addPoint(Ponto p1);


	/**
	 * @brief If the vector is ordered by distance, finds the closer bicycle of a certain type, else  finds the first it can.
	 *
	 * @param bicycle Type of bike
	 *
	 * @return iterator to the bicycle, or vector<Ponto>.end() se não encontrar
	 */
	vector<Ponto>::iterator isThereBicycle(string bicycle);


	/**
	 * @brief calculates the closest point with a certain kind of bicycle
	 *
	 * @param coord Closest to this coordinates
	 * @param type Name of the type
	 *
	 * @return iterator to the point
	 */
	vector<Ponto>::iterator closestType(Coordenadas coord, string type);


	/**
	 * @return Returns an iterator to the first point with free space
	 */
	vector<Ponto>::iterator isThereSpace();


	/**
	 * @param coord Coordinates to calculate the distance
	 *
	 * @return Returns an iterator to the closest point with free space
	 */
	vector<Ponto>::iterator closestSpace(Coordenadas coord);


	/**
	 * @brief Adds a user to the array
	 *
	 * @param u1 User to add
	 */
	Cidade& addUtente(Utente* u1);


	/**
	 * @brief searches a point in the city
	 *
	 * @param name name of the point
	 *
	 * @return iterator to the point
	 */
	vector<Ponto>::iterator findPoint(string name);


	/**
	 * @brief searches a point in the city
	 *
	 * @param x coordinate x of the point
	 * @param y coordinate y of the point
	 *
	 * @return true if the point exists, false otherwise
	 */
	bool  findPoint(double x, double y);


	/**
	 * @brief removes an user from the city
	 *
	 * @param id id of the user
	 */
    Cidade& removeUtente(int id);


    /**
    * @brief removes a point from the city
    *
    * @param name name of the point
    */
    Cidade& removePonto(string name);


   /**
	 * @brief searches an user in the city
	 *
	 * @param id id of the user
	 *
	 * @return pointer to the user
	 */
	Utente* findUtente(int id);


	/**
	 * @brief redistribute bicycles evenly
	 *
	 * @return vector of bicycles that do not fit in the points
	 */
	vector<Bicicleta *> redistributeBikes();


	/**
	 * @brief redistributes a vector of bicycles.
	 *
	 * @param bicycles bikes to redistribute.
	 * @param percentage percentage of bicycles to go in each point.
	 * @return bicycles with no space.
	 */
	vector<Bicicleta *> redistributeVector(vector<Bicicleta *> &v, float percentage);


	/**
	 * @brief if the standard deviation of occupation is above a certain level, redistributes the bicycles.
	 *
	 * @return bikes that didn't fit (always empty due to implementation)
	 */
	vector<Bicicleta *> testOccupation();


	/**
	 * @brief prints all points to out.
	 *
	 * @param out output stream.
	 */
	void printPoints(ostream &out);


	/**
	 * @brief prints all points to out.
	 */
	void printPointsinMenu();


	/**
	 * @brief prints all Users to the screen;
	 *
	 */
	void printUsers();


	/**
	 * @brief prints all points to file.
	 *
	 * @param file to output to.
	 */
	void printPointsFile(const string &file);


	/**
	 * @brief reads points from a file.
	 *
	 * @param file to read.
	 */
	void readPoints(const string& file);


	/**
	 * @brief reads Users from a file.
	 *
	 * @param file to read.
	 */
	void readUsers(const string& file);


	/**
	 * @brief writes Users to a file.
	 *
	 * @param file to write to.
	 */
	void printUserstoFile(const string& file);


	/**
	 * @brief atributes a disassembly date to a bike
	 *
	 * @param bike to disassemble's ID;
	 * @param date of disassembly;
	 */
	void disassembleBike(unsigned int bikeID, string date);


	/**
	 * @brief consults all the bicycles prepped for disassembly
	 */
	void consultBikes();


	/**
	 * @brief deletes a given bike from the registry
	 */
	void deleteBike(unsigned int bikeID);


	/**
	 *	Adds a given part to the part tree
	 *
	 *	@param p1 Part to add to the tree
	 */
	void insertPart(Part& p1);


	/**
	 * Removes a part from the tree
	 *
	 * @param namePart Name of the part to remove
	 * @param supplier Supplier of the part to remove
	 */
	void removePart(const string& namePart, const string& supplier);


	/**
	 * Prints the tree in increasing order
	 *
	 * @param out Destination of the print
	 */
	void printTree(ostream& out);


	/**
	 * Changes the unit price of a given a part with a given supplier
	 *
	 * @param p1 Part with the new price
	 */
	void buyPart(Part &p1);


	/**
	 *	Gets the supplier with the lowest price for a given part.
	 *	Parts with unit price 0 do not count, as no purchase has been made from that supplier.
	 *
	 *	@param namePart Name of the part to check for lowest price
	 *
	 *	@return Part with the given name and the lowest price, that isn't 0
	 */
	const Part getLowestPrice(const string& namePart) const;


	/**
	 * Gets the name of all the suppliers in a vector
	 *
	 * @return Suppliers
	 */
	vector<string> getSuppliers() const;


	/**
	 * @brief Prints all the suppliers
	 *
	 * @param out Destination stream
	 */
	void printSuppliers(ostream& out);


	/**
	 * Prints the prices of each supplier of a given part that as already sold something
	 *
	 * @param namePart Lists the prices of the parts with this name
	 * @param out Destination stream
	 */
	void printLatestPrices(ostream& out, const string& namePart) const;


	/**
	 * Reads parts from a given file
	 *
	 * @param fileName Name of the file to read
	 */
	void readParts(const string& fileName);

	/**
	 * Reads bikes from a given file
	 *
	 * @param fileName Name of the file to read
	 */
	void readBikes(const string& fileName);

	/**
	 *	Prints all bikes to a certain file
	 *
	 *	@param file Destination of the print
	 */
	void printBikes(const string& file);


	/**
	 *	Prints all parts to a certain file
	 *
	 *	@param fileName Destination of the print
	 */
	void printParts(const string& fileName);


	 /**
	 * @brief searches a store in the city
	 *
	 * @param name Name of the store
	 *
	 * @return True if found, False otherwise
	 */
	bool findStore(string name);


	/**
	 * @brief reads Stores from a file
	 *
	 * @param file to read
	 */
	void readStores(const string& file);


	/**
	 * @brief Buys number amount of bikes of type type
	 *
	 * @param type Type of Bike
	 * @param number Amount of bikes to purchase
	 * @param purchase Vector that will contain the bikes purchased
	 *
	 * @return Name of the store where the bikes were purchased
	 */
	string BuyBikes(string type, int number, vector<Bicicleta*> & purchase);


	/**
	 * @brief Adds to the city points the previously purchased bikes
	 *
	 * @param purchase Vector that contains purchased bikes
	 *
	 * @return True if all the bikes were successfully added, False otherwise
	 */
	bool AddPurchasedBikes(vector<Bicicleta*> &purchase);


	/**
	 * @brief Gets the top 5 best reputes stores of the city
	 *
	 * @return Vector containing the 5 best reputed strores
	 */
	vector<Loja> getTop5() const;


	/**
	 * @brief Sets the reputation of the store specified
	 *
	 * @param storeName Name of the store  whose reputation will be set
	 * @param newreputation The store's new reputation
	 */
	void setStoreReputation(string storeName, int newreputation);


	/**
	 * @brief Adds a store to the city
	 *
	 * @param loja Store to be added
	 */
	Cidade& addStore(Loja loja);


	/**
	 * @brief writes Stores to Menu
	 */
	void printStoresInMenu();


	/**
	 * @brief writes Stores
	 *
	 * @param out Destination stream
	 */
	void printStores(ostream &out);


	/**
	 * @brief writes Stores to a file.
	 *
	 * @param file to write to.
	 */
	void printStoresFile(const string &file);


	Cidade();
	virtual ~Cidade();
};

/**
 * @brief Exception
 */
class JaTemBicicletaException{
public:
	string nome;

	string getNome(){
		return nome;
	}

	JaTemBicicletaException(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class NaoTemBicicletaException{
public:
	string nome;

	string getNome(){
		return nome;
	}

	NaoTemBicicletaException(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class PontoVazio{
public:
	string nome;

	string getNome(){
		return nome;
	}

	PontoVazio(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class UtenteNaoExistente{
public:
	string nome;

	string getNome(){
		return nome;
	}

	UtenteNaoExistente(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class NoUserFound
{
public:
	int id;
	NoUserFound (int id){this->id = id; };
};

/**
 * @brief Exception
 */
class PontoNaoExistente{
public:
	string nome;

	string getNome(){
		return nome;
	}

	PontoNaoExistente(string nome){
		this->nome = nome;
	}
};

/**
 * @brief Exception
 */
class BikeNotExist{
public:
	unsigned int ID;

	BikeNotExist(unsigned int ID){
		this->ID = ID;
	}
};

/**
 * @brief Exception
 */
class BikeAlreadyDisassembled{
public:
	unsigned int ID;

	BikeAlreadyDisassembled(unsigned int ID){
		this->ID = ID;
	}
};


/**
 * Not a point
 */
class NotAPoint
{
public:
	string name;
	NotAPoint(string n) : name(n){};
};


/**
 * Point already exists
 */
class existentPoint
{
public:
	string name;
	existentPoint(string n) : name(n){};
};


/**
 * Redistribution not needed
 */
class NoRedistributionNeeded
{
public:
	NoRedistributionNeeded(){};
};

/**
 * Not a file
 */
class NotAFile
{
public:
	string name;
	NotAFile(string n) : name(n){};
};

/**
 * Invalid File
 */
class InvalidFile
{
public:
	InvalidFile(){};
};


/**
 * @brief Exception
 */
class NoStores
{
public:
	NoStores(){};
};


/**
 * @brief Exception
 */
class InvalidPurchase
{
public:
	InvalidPurchase(){};
};

/**
 * Exception, triggered when the insertion in the set fails
 */
class InsertionError
{
public:
	Part offender;
	InsertionError(const Part& p1):offender(p1){}
};

/**
 * Exception, could not remove the desired Part
 */
class RemovingError
{
public:
	RemovingError(){};
};


/**
 * Exception, could not buy the part
 */
class InvalidPartPurchase
{
public:
	InvalidPartPurchase(){};
};

/**
 * Exception, could not find the part or it was never bought before
 */
class InvalidPart
{
public:
	InvalidPart(){};
};

#endif /* CIDADE_H_ */
