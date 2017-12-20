//============================================================================
// Name        : AEDABICICLETAS.cpp
// Author      : 2MIEIC02 -> GRUPO 4
// Version     : 1
// Description : This is the main function, includes menu and others ..
//============================================================================

#include <iostream>
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Bicicleta.h"
#include "Cidade.h"
#include "Coordenadas.h"
#include "Ponto.h"
#include "Utente.h"
#include "Hora.h"
#include "Menu.h"
using namespace std;


int main() {
	Cidade c1;
	string pointfile, userfile;
	bool validPfile = true;
	bool validUfile = true;
	bool validSfile = true;
	bool validPTfile = true;
	bool validBKfile = true;
	do{
		validPfile = true;
		cout << "Name of the file containing the points ? " << endl;
		pointfile = getFileName();
	    try
	    {
		  c1.readPoints(pointfile);
	    }
	    catch(NotAFile &f)
	    {
		  cout << "Not file." << endl;
		  validPfile = false;
	    }
	    catch(InvalidFile &f)
	    {
	    	cout << "Invalid file." << endl;
	    	validPfile = false;
	    }
	}while (validPfile == false);
    do{
    	validUfile = true;
    	cout << "Name of the file containing the users ? " << endl;
    	userfile = getFileName();
    	try
    	{
    	   c1.readUsers(userfile);
    	}
    	catch(NotAFile &f)
    	{
    	   cout << "Not file." << endl;
    	   validUfile = false;
    	}
    	catch(InvalidFile &f)
    	{
    		cout << "Invalid File."<< endl;
    		validUfile = false;
    	}
       }while(validUfile == false);

    do{
		validSfile = true;
		cout << "Name of the file containing the stores ? " << endl;
		pointfile = getFileName();
		try
		{
		  c1.readStores(pointfile);
		}
		catch(NotAFile &f)
		{
		  cout << "Not file." << endl;
		  validSfile = false;
		}
		catch(InvalidFile &f)
		{
			cout << "Invalid file." << endl;
			validSfile = false;
		}
	}while (validSfile == false);

    do{
   		validPTfile = true;
   		cout << "Name of the file containing the parts ? " << endl;
   		pointfile = getFileName();
   		try
   		{
   		  c1.readParts(pointfile);
   		}
   		catch(NotAFile &f)
   		{
   		  cout << "Not file." << endl;
   		  validPTfile = false;
   		}
   		catch(InvalidFile &f)
   		{
   			cout << "Invalid file." << endl;
   			validPTfile = false;
   		}
   		catch(InvalidPoint &p)
   		{
   			cout << "Invalid file." << endl;
   			validPTfile = false;
   		}
   	}while (validPTfile == false);

    do{
		validBKfile = true;
		cout << "Name of the file containing the bikes for disassemble ? " << endl;
		pointfile = getFileName();
		try
		{
		  c1.readBikes(pointfile);
		}
		catch(NotAFile &f)
		{
		  cout << "Not file." << endl;
		  validBKfile = false;
		}

	}while (validBKfile == false);

	cout << endl;
  	FirstMenu(c1);

	return 0;
}
