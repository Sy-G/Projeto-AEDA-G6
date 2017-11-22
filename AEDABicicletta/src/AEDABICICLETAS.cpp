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


	cout << endl;
  	FirstMenu(c1);

	return 0;
}
