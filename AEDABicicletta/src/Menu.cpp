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

/*Function: Gets a number from the user*/
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
	cin>> biketype;
	if (   (biketype != "Urbana" ) && (biketype != "Urbana_Simples") && (biketype != "Infantil")  && (biketype != "Corrida"))
		throw NotAType(biketype);
	else
		return biketype;
}

void FirstMenu()
{
	bool endInput = false;

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
					CityManagementMenu();
					break;
				case 2:
                    UserOptionsMenu();
					break;
				case 3:
					endInput = true;
					break;
				}
	} while(!endInput);
}

void CityManagementMenu()
{
	cout
		    << "1- Bike redistribution" << endl
			<< "2- Add new location " << endl
			<< "3- Go back" << endl
			<< "Select one" << endl;

		switch (getIntInInterval(1, 3))
		{
			case 1:
	            // chama a funcao que redistribui as bicicletas pelos pontos de forma equilibrada
				break;
			case 2:
                AddNewLocationMenu();
				break;
			case 3:
				return;
				break;
		}
}

void AddNewLocationMenu()
{
	string name;
	Coordenadas cord;
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
    	return;
	}

 	//apanha a excepcao caso o ponto ja exista

 	cout << "Location added  successfully" << endl;

}

void UserOptionsMenu()
{
	cout
	<< "1- Sign in (as a member or regular user)" << endl
	<< "2- Sign up (as a member or regular user) "<< endl
	<< "3- Go back" << endl
	<< "Select one" << endl;

	switch (getIntInInterval(1, 3))
	{
		case 1:
            SignInMenu();
			break;
		case 2:
            SignUpMenu();
			break;
		case 3:
			return;
			break;
	}
}

void SignInMenu()
{
	//string name;
	int idnumber;
	cleanfunction();
	//cout << "Name ? (first and last)" << endl;
	//getline(cin,name);

    cout << "Member ID number ? " << endl;
    idnumber = getInt();
    if (idnumber == -1)
    	return;

    bool member = true;
   if (member)
	   BikeMenuMember();
   else
	   BikeMenuRU();
}

void SignUpMenu()
{
   cout
   << "1- Member" << endl
   << "2- Regular user" << endl
   << "3- Go back" << endl
   << "Select one" << endl;

	switch (getIntInInterval(1, 3))
	{
		case 1:
			SignUpMemberMenu();
			break;
		case 2:
			SignUpRegularMenu();
			break;
		case 3:
			return;
			break;
	}
}

void SignUpMemberMenu()
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);

	//cria o socio
	//Utente *ptr = new Socio(name,0,0);
	//this->addUtente(ptr);

	//cout do numero de id do socio (para uso futuro)
	cout << "Your member ID number is "  << endl;

	cout << "Sign up executed successfully" << endl;

    BikeMenuMember();
}

void SignUpRegularMenu()
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);

	//cria o regular
	//Utente *ptr = new Regular(name,0,0);
	////this->addUtente(ptr);

	cout << "Your user ID number is "  << endl;

	cout << "Sign up executed successfully" << endl;

    BikeMenuRU();
}

void BikeMenuRU()
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl   //para retornar e para pegar;
		<< "4- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 4))
	{
		case 1:
            GetBikeMenu();
			break;
		case 2:
            ReturnBikeMenu();
			break;
		case 3:
			ClosestLocationMenu();
		    break;
		case 4:
			return;
			break;
	}
}


void BikeMenuMember()
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Closest location" << endl   //para retornar e para pegar;
		<< "4- Monthly Payment" << endl
		<< "5- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 4))
	{
		case 1:
            GetBikeMenu();
			break;
		case 2:
            ReturnBikeMenu();
			break;
		case 3:
			ClosestLocationMenu();
		    break;
		case 4:
			MonthlyPaymentMenu();
			break;
		case 5:
			return;
			break;
	}
}


void GetBikeMenu()
{
	string pointname, biketype;
	Hora horainicial;
    cleanfunction();
	cout << "Where are you picking the bike ?" << endl;
	getline(cin,pointname);
    //procura o ponto
	cout << "Type of bike you want ? " << endl;
	try
	{
     biketype = getBikeType();
	}
	catch(NotAType &e)
	{
	  cout << "Invalid type" << endl;
      return;
	}

	cout << "What is the pick up hour ? " << endl;
	try
	{
	  cin >> horainicial;
	}
    catch(HoraInexistente &e)
	{
    	cout << "Invalid hour" << endl;
    	return;
	}


	cout << "Bicycle lifted successfully" << endl ;
	cout << endl;

}

void ReturnBikeMenu()
{
	string returningpoint;
	Hora horafinal;
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
	getline(cin, returningpoint);
	//procura ponto
	cout << "What is the returning hour ? " << endl;
	try
		{
		  cin >> horafinal;
		}
	    catch(HoraInexistente &e)
		{
	    	cout << "Invalid hour" << endl;
	    	return;
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

void ClosestLocationMenu()
{
  string biketype;
  cout << "1- To return a bike" << endl
	   << "2- To get a bike"  << endl
	   << "3- Go back" << endl
	   << "Select one" << endl;
  switch (getIntInInterval(1, 3))
  	{
  		case 1:
            //chama a funcao
  			break;
  		case 2:
  			cout << "What is the type of bike you want to get ? " << endl;
  			try
  			{
  		     biketype = getBikeType();
  			}
  			catch(NotAType &e)
  			{
  			  cout << "Invalid type" << endl;
  		      return;
  			}
            //chama a funcao
  			break;
  		case 3:
  			return;
  			break;
  	}
}

void MonthlyPaymentMenu()
{
	int num = 0;  //num = funcao de pagamento
	cout << "This month's payment is " << num << " euros." << endl;
}
