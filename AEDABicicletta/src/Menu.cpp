#include <string>
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Hora.h"
#include "Coordenadas.h"
#include "Cidade.h"
#include "Ponto.h"
using namespace std;

/*cenas das coordenadas, nao quis estar a mexer na parte do Gui*/





////////////////////////////////////////////////////////////
//  utentes: para distinguir se e ou nao socio
//class Utente  virtual bool eSocio() = 0;
//class Socio   bool eSocio();
//class Regulares  bool eSocio();

//bool Socio::eSocio()
//{
//	return true;
//}
//
//bool Regulares::eSocio()
//{
//	return false;
//}
/////////////////////////////////////////////////////////////////

//menus

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
			<< "3- Quit" << endl
			<< "Select one" << endl;
		switch (getIntInInterval(1, 3))
				{
				case 1:
					CityManagementMenu(cidade);
					break;
				case 2:
                    UserOptionsMenu(cidade);
					break;
				case 3:
					endInput = true;
					break;
				}
	} while(!endInput);
}

//done
void CityManagementMenu(Cidade &cidade)
{
	cout
		    << "1- Bike redistribution" << endl
			<< "2- Add new location " << endl
			<< "3- Print locations " << endl
			<< "4- Go back" << endl
			<< "Select one" << endl;

		switch (getIntInInterval(1, 4))
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
				break;
			case 2:
                AddNewLocationMenu(cidade);
				break;
			case 3:
				for (unsigned int i = 0; i < cidade.getPontos().size(); i++)
				{
					cout <<"Name: " <<cidade.getPontos().at(i).getNome() << endl;
					cout << "Coordinates: " << cidade.getPontos().at(i).getCoord().cordX << "-" << cidade.getPontos().at(i).getCoord().cordY << endl;
					cout << "Capacity: " << cidade.getPontos().at(i).getCapacidade() << endl;
					cout << "Number of bikes available: " << cidade.getPontos().at(i).getBicicletas().size() << endl;
					cout << endl;
				}
				break;
			case 4:
				return;
				break;
		}
}

//done
void AddNewLocationMenu(Cidade &cidade)
{
	string name;
	Coordenadas cord;
    int capacity;
	cleanfunction();

 	cout << "New location's name ? " << endl;
 	getline(cin,name);

 	cout << "Location's coordinates ? (x-y) " << endl;
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
    	return CityManagementMenu(cidade);

    Ponto newlocation(name, (unsigned) capacity, cord);
    try
    {
    	cidade.addPoint(newlocation);
    }
    catch (existentPoint &e)
    {
    	cout << "Invalid location, this point already exists" << endl;
        return CityManagementMenu(cidade);
    }

 	cout << "Location added  successfully" << endl;
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
    if (idnumber == -1)
    	return UserOptionsMenu(cidade);

   bool member = true;
   if (member)
	   BikeMenuMember(cidade);
   else
	   BikeMenuRU(cidade);
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

//falta a cena do id...
void SignUpMemberMenu(Cidade &cidade)
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);


	Utente *nsocio = new Socio(name,1,0,0);

	cidade.addUtente(nsocio);

	//cout do numero de id do socio (para uso futuro)
	//cout << "Your member ID number is "  << nsocio->getID() << "." << endl;

	cout << "Sign up executed successfully." << endl;

    BikeMenuMember(cidade);
}

//falta a cena do id....
void SignUpRegularMenu(Cidade &cidade)
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);


	Utente *nregular = new Regulares(name,1,0,0);
	cidade.addUtente(nregular);

	//cout << "Your user ID number is "  << nregular->getID() << "." << endl;

	cout << "Sign up executed successfully." << endl;

    BikeMenuRU(cidade);
}
//done
void BikeMenuRU(Cidade &cidade)
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl
		<< "4- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 4))
	{
		case 1:
            GetBikeMenu(cidade);
			break;
		case 2:
            ReturnBikeMenu(cidade);
			break;
		case 3:
			ClosestLocationMenu(cidade);
		    break;
		case 4:
			return UserOptionsMenu(cidade);
			break;
	}
}

//done
void BikeMenuMember(Cidade &cidade)
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl
		<< "4- Monthly Payment" << endl
		<< "5- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 5))
	{
		case 1:
            GetBikeMenu(cidade);
			break;
		case 2:
            ReturnBikeMenu(cidade);
			break;
		case 3:
			ClosestLocationMenu(cidade);
		    break;
		case 4:
			MonthlyPaymentMenu(cidade);
			break;
		case 5:
			return UserOptionsMenu(cidade);
			break;
	}
}

//falta chamar a funcao para ver se socio, e chamar a funcao que levanta a bicicleta
void GetBikeMenu(Cidade &cidade)
{
	bool esocio = true;  // funcao que ve se e socio ou nao
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
		  return BikeMenuMember(cidade);
	    else
		  return BikeMenuRU(cidade);
	}
	cout << "Type of bike you want ? " << endl;
	try
	{
     biketype = getBikeType();
	}
	catch(NotAType &e)
	{
	  cout << "Invalid type" << endl;
	  if (esocio)
		  return BikeMenuMember(cidade);
	  else
		  return BikeMenuRU(cidade);
	}

	cout << "What is the pick up hour ? " << endl;
	try
	{
	  cin >> horainicial;
	}
	catch(HoraInvalida &h)
    {
	   cout << "Invalid Input" << endl;
	   if (esocio)
	   	  return BikeMenuMember(cidade);
	   else
	   	  return BikeMenuRU(cidade);
	}
    catch(HoraInexistente &e)
	{
    	cout << "Invalid hour" << endl;
    	if (esocio)
    	   return BikeMenuMember(cidade);
    	 else
    	   return BikeMenuRU(cidade);
	}


	cout << "Bicycle lifted successfully." << endl ;
	cout << endl;

}


void ReturnBikeMenu(Cidade &cidade)
{
	bool esocio = true; // igual a funcao que ve se e ou nao socio
	string pointname;
	Hora horafinal;
	vector<Ponto>::iterator it;
	cleanfunction();
	/*bool endofthemonth = false;
	char verifyendofthemonth;
	cout << "Is this the end of the month ? (s/n)" << endl;
	cin >> verifyendofthemonth;
	if ( (cin.fail()) || ( (verifyendofthemonth != 's' ) &&  (verifyendofthemonth != 'n' )))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input!" << endl;
		return;
	}
	if (verifyendofthemonth == 's' )
		endofthemonth = true; */

	cout << "Where are you returning the bike ? " << endl;
	getline(cin, pointname);
	try
		{
			it = cidade.findPoint(pointname);
		}
		catch (NotAPoint &p)
		{
			cout << "Non existent location." << endl;
			if (esocio)
			  return BikeMenuMember(cidade);
		    else
			  return BikeMenuRU(cidade);
		}
	cout << "What is the returning hour ? " << endl;
	try
		{
		  cin >> horafinal;
		}
	    catch(HoraInvalida &h)
	    {
	    	cout << "Invalid Input" << endl;
	    	if (esocio)
	    	  return BikeMenuMember(cidade);
	    	else
	    	  return BikeMenuRU(cidade);
	    }
	    catch(HoraInexistente &e)
		{
	    	cout << "Invalid hour" << endl;
	    	if (esocio)
	    	  return BikeMenuMember(cidade);
	    	else
	    	  return BikeMenuRU(cidade);
		}
	    /*try
		{
		  horafinal - horainicial;
		}
	    catch(HorasInvalidas &e)
		{
	    	cout << "Invalid schedule" << endl;
	    	return;
		}*/

	cout << "Bicycle returned successfully" << endl;
	cout << endl;
}

//falta ver se e ou nao socio
// NoPoint exception !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void ClosestLocationMenu(Cidade &cidade)
{
  bool esocio = true; // igual a funcao que ve se e ou nao socio
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
  			cout << "What are your coordinates at the moment (x-y) ?" << endl;
  			try
  			{
  			cin >> cord;
  			}
  			catch(InvalidCoordinates &c)
  			{
  				cout << "Invalid coordinates." << endl;
  				if (esocio)
  				 return BikeMenuMember(cidade);
  				else
  				  return BikeMenuRU(cidade);
  			}
  			try
  			{
  				it = cidade.closestSpace(cord);
  			}
  			catch(NoSpace &e)
  			{
  				cout << "There is no space to return the bike. " << endl;
  				if (esocio)
  				  return BikeMenuMember(cidade);
  				else
  				  return BikeMenuRU(cidade);
  			}

  			cout << "The closest point is " << it->getNome() << " with coordinates " << it->getCoord().cordX << "-" << it->getCoord().cordY <<" at a distance of ";
  			cout << it->getDistance() << "." << endl;

  			break;
  		case 2:
  			cout << "What are your coordinates at the moment (x-y) ?" << endl;
			try
			{
				cin >> cord;
			}
			catch(InvalidCoordinates &c)
			{
				cout << "Invalid coordinates." << endl;
				if (esocio)
				   return BikeMenuMember(cidade);
			    else
				    return BikeMenuRU(cidade);
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
  			  return BikeMenuMember(cidade);
  			else
  			  return BikeMenuRU(cidade);
  			}

  			try
  			{
  				it = cidade.closestType(cord,biketype); //porque e que ele retorna o .end() e nao uma excecao??
  			}
  			catch(NotAType &e)
  			{
  			  if (esocio)
  				 return BikeMenuMember(cidade);
  			  else
  				 return BikeMenuRU(cidade);
  			}
            /////////////////////////////////////////////
  			if (it == cidade.getPontos().end())
  				return;
            ////////////////////////////////////////////

  			cout << "The closest point is " << it->getNome() << " with coordinates " <<it->getCoord().cordX << "-" << it->getCoord().cordY << " at a distance of ";
  			cout << it->getDistance() << "." << endl;

  			break;
  		case 3:
  			if (esocio)
  			 return BikeMenuMember(cidade);
  			else
  			 return BikeMenuRU(cidade);
  			break;
  	}
}

//falta a cena do socio....
void MonthlyPaymentMenu(Cidade &cidade)
{
	int num = 0;  //num = funcao de pagamento
	cout << "This month's payment is " << num << " euros." << endl;
}
