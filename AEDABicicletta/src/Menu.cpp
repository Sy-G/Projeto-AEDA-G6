#include <string>
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Hora.h"
#include "Coordenadas.h"
#include "Cidade.h"
#include "Ponto.h"
using namespace std;



void cleanfunction()
{
	cin.ignore();
	cin.clear();
}



int getIntInInterval(int lower, int upper)
{
	int num;
	bool validInput;
	do
	{
		validInput = true;
		cin >> num;
		if (cin.fail())
		{
			validInput = false;

				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input!" << endl;

		}
		else if (!(num <= upper && num >= lower))
		{
			validInput = false;
			cout << "Invalid Choice!" << endl;
		}
	} while (!validInput);

	return num;
}



int getInt()
{
	int num;
	cin >> num;

	if (cin.fail() || num < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input!\n";
			return -1;
		}
	return num;
}



string getFileName()
{
	string filename;
	cin >> filename;
	if (filename.size() <= 3)
	{
		filename += ".txt";
	}
	else if (filename.substr(filename.size() - 4, 4).compare(".txt") != 0)
		filename += ".txt";

 return filename;
}

string getBikeType()
{
	string biketype;
	cin >> biketype;

	if (biketype == "urbana") return "Urbana";
	if (biketype == "urbana_simples") return "Urbana_Simples";
	if (biketype == "infantil") return "Infantil";
	if (biketype == "corrida") return "Corrida";
	if ((biketype != "Urbana" ) && (biketype != "Urbana_Simples") && (biketype != "Infantil")  && (biketype != "Corrida"))
	   throw NotAType(biketype);
    else
	    return biketype;
}



void FirstMenu(Cidade &cidade)
{
	bool endInput = false;
    cout << "Welcome" << endl;

	do
	{
		cout
			<< "1- City Management" << endl
			<< "2- User options" << endl
			<< "3- Save " << endl
			<< "4- Quit" << endl
			<< "Select one" << endl;
		switch (getIntInInterval(1, 4))
				{
				case 1:
					CityManagementMenu(cidade);
					break;
				case 2:
                    UserOptionsMenu(cidade);
					break;
				case 3:
                    SaveChangesMenu(cidade);
					break;
				case 4:
					endInput = true;
					break;
				}
	} while(!endInput);
}



void CityManagementMenu(Cidade &cidade)
{
	cout
		    << "1- Bike redistribution" << endl
			<< "2- Add new location " << endl
			<< "3- Remove location " << endl
			<< "4- Print locations " << endl
			<< "5- Print Users " << endl
			<< "6- Go back" << endl
			<< "Select one" << endl;

		switch (getIntInInterval(1, 6))
		{
			case 1:
				try
				{
					cidade.testOccupation();
				}
				catch(NoRedistributionNeeded &r)
				{
					cout << "No redistribution needed." << endl;
					return;
				}
				cout << "Bikes redistributed successfully" << endl;
				cidade.printPointsinMenu();
				break;
			case 2:
                AddNewLocationMenu(cidade);
				break;

			case 3:
				RemoveLocationMenu(cidade);
				break;
			case 4:
                cidade.printPointsinMenu();
				break;
			case 5:
				cidade.printUsers();
				break;
			case 6:
				return;
				break;
		}
}



void AddNewLocationMenu(Cidade &cidade)
{
	string name;
	Coordenadas cord;
    int capacity;
	cleanfunction();

 	cout << "New location's name ? " << endl;
 	getline(cin,name);

 	cout << "Location's coordinates ? (x,y) " << endl;
	try
	{
	  cin >> cord;
	}
    catch(InvalidCoordinates &e)
	{
    	cout << "Invalid Coordinates" << endl;
    	return CityManagementMenu(cidade);
	}

    cout << "Location's capacity ? " << endl;
    capacity = getInt();

    if (capacity == -1)
    {
     cout << "Invalid capacity." << endl;
     return CityManagementMenu(cidade);
    }
    if(cidade.findPoint(cord.cordX, cord.cordY))
    {
     cout << "Invalid location, this point already exists." << endl;
     return CityManagementMenu(cidade);
    }

    Ponto newlocation(name, (unsigned) capacity, cord);
    try
    {
    	cidade.addPoint(newlocation);
    }
    catch (existentPoint &e)
    {
    	cout << "Invalid location, this point already exists." << endl;
        return CityManagementMenu(cidade);
    }

 	cout << "Location added  successfully." << endl;
}



void RemoveLocationMenu(Cidade &cidade)
{
	string pointname;
	cleanfunction();
	cout << "What is the location's name? " << endl;
	getline (cin,pointname);
	try
	{
	 cidade.removePonto(pointname);
	}
	catch(NotAPoint &p)
	{
	  cout << "Not an existent location" << endl;
	  return;
	}
	 cout << "Location removed successfully." << endl;
}



void UserOptionsMenu(Cidade &cidade)
{
	cout
	<< "1- Sign in (as a member or regular user)" << endl
	<< "2- Sign up (as a member or regular user) "<< endl
	<< "3- Go back" << endl
	<< "Select one" << endl;

	switch (getIntInInterval(1, 3))
	{
		case 1:
            SignInMenu(cidade);
			break;
		case 2:
            SignUpMenu(cidade);
			break;
		case 3:
			return;
			break;
	}
}



void SignInMenu(Cidade &cidade)
{
	int idnumber;
    cout << "Member ID number ? " << endl;
    idnumber = getInt();
    Utente *ptr;
    try
    {
    	ptr = cidade.findUtente(idnumber);
    }
    catch(NoUserFound &e)
    {
    	cout << "No user found with that id, try signing up" << endl;
    	return;
    }
    if (idnumber == -1)
    	return UserOptionsMenu(cidade);

   bool member = ptr->eSocio();
   if (member)
	   BikeMenuMember(cidade, ptr);
   else
	   BikeMenuRU(cidade, ptr);
}



void SignUpMenu(Cidade &cidade)
{
   cout
   << "1- Member" << endl
   << "2- Regular user" << endl
   << "3- Go back" << endl
   << "Select one" << endl;

	switch (getIntInInterval(1, 3))
	{
		case 1:
			SignUpMemberMenu(cidade);
			break;
		case 2:
			SignUpRegularMenu(cidade);
			break;
		case 3:
			return UserOptionsMenu(cidade);
			break;
	}
}



void SignUpMemberMenu(Cidade &cidade)
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);


	Utente *nsocio = new Socio(name,1,0);

	cidade.addUtente(nsocio);

	cout << "Sign up executed successfully." << endl;
	cout << "Your member ID number is "  << nsocio->getID() << "." << endl;

    BikeMenuMember(cidade, nsocio);
}



void SignUpRegularMenu(Cidade &cidade)
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);


	Utente *nregular = new Regulares(name,1,0);
	cidade.addUtente(nregular);

	cout << "Sign up executed successfully." << endl;
	cout << "Your user ID number is "  << nregular->getID() << "." << endl;

    BikeMenuRU(cidade ,nregular);
}



void BikeMenuRU(Cidade &cidade, Utente *utente)
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl
		<< "4- Delete account " << endl
		<< "5- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 5))
	{
		case 1:
            GetBikeMenu(cidade, utente);
			break;
		case 2:
            ReturnBikeMenu(cidade, utente);
			break;
		case 3:
			ClosestLocationMenu(cidade, utente);
		    break;
		case 4:
		    try
		    {
		    	cidade.removeUtente(utente->getID());
		    }
		    catch(NoUserFound &p)
		    {
                cout << "No user found " << endl;
                return UserOptionsMenu(cidade);
		    }
			cout << "Your account was deleted successfully, you will be missed." << endl;
		    break;
		case 5:
			return UserOptionsMenu(cidade);
			break;
	}
}



void BikeMenuMember(Cidade &cidade, Utente *utente)
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl
		<< "4- Monthly Payment" << endl
		<< "5- Delete account " << endl
		<< "6- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 6))
	{
		case 1:
            GetBikeMenu(cidade, utente);
			break;
		case 2:
            ReturnBikeMenu(cidade, utente);
			break;
		case 3:
			ClosestLocationMenu(cidade, utente);
		    break;
		case 4:
			MonthlyPaymentMenu(cidade, utente);
			break;
		case 5:
			 try
			   {
				cidade.removeUtente(utente->getID());
			   }
			  catch(NoUserFound &p)
			   {
			    cout << "No user found " << endl;
			    return UserOptionsMenu(cidade);
			   }
			cout << "Your account was deleted successfully, you will be missed." << endl;
			break;
		case 6:
			return UserOptionsMenu(cidade);
			break;
	}
}



void GetBikeMenu(Cidade &cidade, Utente *utente)
{
	bool esocio = utente->eSocio();
	string pointname, biketype;
	Hora horainicial;
    cleanfunction();
    vector<Ponto>::iterator it;
	cout << "Where are you picking the bike ?" << endl;
	getline(cin,pointname);
	try
	{
		it = cidade.findPoint(pointname);
	}
	catch (NotAPoint &p)
	{
		cout << "Not an existent location" << endl;
		if (esocio)
		  return BikeMenuMember(cidade, utente);
	    else
		  return BikeMenuRU(cidade, utente);
	}
	cout << "Type of bike you want ? " << endl;
	try
	{
     biketype = getBikeType();
	}
	catch(NotAType &e)
	{
	  cout << "Invalid type." << endl;
	  if (esocio)
		  return BikeMenuMember(cidade, utente);
	  else
		  return BikeMenuRU(cidade, utente);
	}

	cout << "What is the pick up hour ? " << endl;
	try
	{
	  cin >> horainicial;
	}
	catch(HoraInvalida &h)
    {
	   cout << "Invalid Input." << endl;
	   if (esocio)
	   	  return BikeMenuMember(cidade, utente);
	   else
	   	  return BikeMenuRU(cidade, utente);
	}
    catch(HoraInexistente &e)
	{
    	cout << "Invalid hour." << endl;
    	if (esocio)
    	   return BikeMenuMember(cidade, utente);
    	 else
    	   return BikeMenuRU(cidade, utente);
	}

    try
    {
    utente->levantaBicicleta(it,biketype,horainicial);
    }
    catch(PontoVazio &p)
    {
    	cout << "No bike to lift in this location." << endl;
    	if (esocio)
    	   return BikeMenuMember(cidade, utente);
    	 else
    	   return BikeMenuRU(cidade, utente);
    }
    catch(JaTemBicicletaException &p)
    {
    	cout << "You forgot to return your bike, try that and then come back." << endl;
    	  if (esocio)
    	     return BikeMenuMember(cidade, utente);
    	   else
    	      return BikeMenuRU(cidade, utente);
    }
    catch(Bicicleta_Inexistente &p)
    {
    	cout << "Invalid type." << endl;
       if (esocio)
           return BikeMenuMember(cidade, utente);
        else
    	   return BikeMenuRU(cidade, utente);
    }

	cout << "Bicycle lifted successfully." << endl ;
	cout << endl;

}



void ReturnBikeMenu(Cidade &cidade, Utente *utente)
{
	bool esocio = utente->eSocio();
	string pointname;
	Hora horafinal;
	vector<Ponto>::iterator it;
	double payment;
	cleanfunction();

	cout << "Where are you returning the bike ? " << endl;
	getline(cin, pointname);
	try
		{
			it = cidade.findPoint(pointname);
		}
		catch (NotAPoint &p)
		{
			cout << "Not an existent location." << endl;
			if (esocio)
			  return BikeMenuMember(cidade, utente);
		    else
			  return BikeMenuRU(cidade, utente);
		}
	cout << "What is the returning hour ? " << endl;
	try
		{
		  cin >> horafinal;
		}
	    catch(HoraInvalida &h)
	    {
	    	cout << "Invalid Input." << endl;
	    	if (esocio)
	    	  return BikeMenuMember(cidade, utente);
	    	else
	    	  return BikeMenuRU(cidade, utente);
	    }
	    catch(HoraInexistente &e)
		{
	    	cout << "Invalid hour" << endl;
	    	if (esocio)
	    	  return BikeMenuMember(cidade, utente);
	    	else
	    	  return BikeMenuRU(cidade, utente);
		}
	    try
		{
		  horafinal - utente->getHoraInicial();
		}
	    catch(HorasInvalidas &e)
		{
	    	cout << "Invalid schedule." << endl;
	    	return;
		}

	try
	{
		payment = utente->devolveBicicleta(it,horafinal);
	}
	catch(NoSpace &p)
	{
		cout << "This locations as no space for more bikes, please return it somewhere else." << endl;
		if (esocio)
		  return BikeMenuMember(cidade, utente);
	    else
	      return BikeMenuRU(cidade, utente);
	}
	catch(NaoTemBicicletaException &p)
	{
		cout << "You don't have a bike, try getting one and then return it." << endl;
		if (esocio)
	      return BikeMenuMember(cidade, utente);
	    else
		  return BikeMenuRU(cidade, utente);
	}

	if  ( (esocio) && (payment != 0))
		cout << "This month's payment is " << payment << " euros." << endl;

	if (!esocio)
		cout << "Today's payment is " << payment << " euros." << endl;

	cout << "Bicycle returned successfully." << endl;
	cout << endl;
}



void ClosestLocationMenu(Cidade &cidade, Utente *utente)
{
  bool esocio = utente->eSocio();
  string biketype;
  Coordenadas cord;
  vector<Ponto>::iterator it;
  cout << "1- To return a bike" << endl
	   << "2- To get a bike"  << endl
	   << "3- Go back" << endl
	   << "Select one" << endl;
  switch (getIntInInterval(1, 3))
  	{
  		case 1:
  			cout << "What are your coordinates at the moment ? (x,y)" << endl;
  			try
  			{
  			cin >> cord;
  			}
  			catch(InvalidCoordinates &c)
  			{
  				cout << "Invalid coordinates." << endl;
  				if (esocio)
  				 return BikeMenuMember(cidade, utente);
  				else
  				  return BikeMenuRU(cidade, utente);
  			}
  			try
  			{
  				it = cidade.closestSpace(cord);
  			}
  			catch(NoSpace &e)
  			{
  				cout << "There is no space to return the bike. " << endl;
  				if (esocio)
  				  return BikeMenuMember(cidade, utente);
  				else
  				  return BikeMenuRU(cidade, utente);
  			}

  			cout << "The closest point is " << it->getNome() << " with coordinates " << it->getCoord().cordX << "," << it->getCoord().cordY <<" at a distance of ";
  			cout << it->getDistance() << " kilometers." << endl;

  			break;
  		case 2:
  			cout << "What are your coordinates at the moment ? (x,y)" << endl;
			try
			{
				cin >> cord;
			}
			catch(InvalidCoordinates &c)
			{
				cout << "Invalid coordinates." << endl;
				if (esocio)
				   return BikeMenuMember(cidade, utente);
			    else
				    return BikeMenuRU(cidade, utente);
			}
  			cout << "What is the type of bike you want to get ? " << endl;
  			try
  			{
  		     biketype = getBikeType();
  			}
  			catch(NotAType &e)
  			{
  			  cout << "Invalid type" << endl;
  			if (esocio)
  			  return BikeMenuMember(cidade, utente);
  			else
  			  return BikeMenuRU(cidade, utente);
  			}

  			try
  			{
  				it = cidade.closestType(cord,biketype); //porque e que ele retorna o .end() e nao uma excecao??
  			}
  			catch(NotAType &e)
  			{
  				cout << "Invalid type" << endl;
  			  if (esocio)
  				 return BikeMenuMember(cidade, utente);
  			  else
  				 return BikeMenuRU(cidade, utente);
  			}
  			catch(NoPoint &e)
  			{
  				cout << "There is no bike of this type available at any of our locations." << endl;
  			  if (esocio)
  			  	 return BikeMenuMember(cidade, utente);
  			  else
  			  	  return BikeMenuRU(cidade, utente);
  			}

  			cout << "The closest point is " << it->getNome() << " with coordinates " <<it->getCoord().cordX << "," << it->getCoord().cordY << " at a distance of ";
  			cout << it->getDistance() << " kilometers." << endl;

  			break;
  		case 3:
  			if (esocio)
  			 return BikeMenuMember(cidade, utente);
  			else
  			 return BikeMenuRU(cidade, utente);
  			break;
  	}
}



void MonthlyPaymentMenu(Cidade &cidade, Utente *utente)
{
	double num = utente->getPagamento();
	cout << "This month's payment is " << num << " euros." << endl;
}



void SaveChangesMenu(Cidade &cidade)
{
	string pointfile, userfile;
	cout
	<< "1- Points" << endl
	<< "2- Users"  << endl
	<< "3- All" << endl
	<< "4- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,4))
	{
	case 1:
		cout << "Name of the file to save the points ?" << endl;
		pointfile = getFileName();
		cidade.printPointsFile(pointfile);
		break;
	case 2:
		cout << "Name of the file to save the users ? " << endl;
		userfile = getFileName();
		cidade.printUserstoFile(userfile);
		break;
	case 3:
		cout << "Name of the file to save the points ?" << endl;
		pointfile = getFileName();
		cidade.printPointsFile(pointfile);
		cout << "Name of the file to save the users ? " << endl;
		userfile = getFileName();
		cidade.printUserstoFile(userfile);
		break;
	case 4:
		return;
		break;
	}
}


