#include <string>
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Hora.h"
#include "Cidade.h"

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

//quais sao as outras opcoes para este menu???
void CityManagementMenu()
{
	cout
		    << "1- Bike redistribution" << endl
			<< "2- " << endl
			<< "3- Go back" << endl
			<< "Select one" << endl;

		switch (getIntInInterval(1, 3))
		{
			case 1:
	            // chama a funcao que redistribui as bicicletas pelos pontos de forma equilibrada
				break;
			case 2:
                // nao sei mais opcoes.......
				break;
			case 3:
				return;
				break;
		}
}

void UserOptionsMenu()
{
	cout
	<< "1- Sign in (as a member)" << endl
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
	string name;
	int idnumber;
	cleanfunction();
	cout << "Name ? (first and last)" << endl;
	getline(cin,name);

    cout << "Member ID number ? " << endl;
    idnumber = getInt();
    if (idnumber == -1)
    	return;


    //confirmar que de facto e um socio
    //excepcao se nao for socio

    // se for socio

    BikeMenu();
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

	//cout do numero de id do socio (para uso futuro)
	cout << "Your member ID number is "  << endl;

	cout << "Sign up executed successfully" << endl;

    BikeMenu();
}

void SignUpRegularMenu()
{
	string name;
	cleanfunction();
	cout << "Name ? (first and last) " << endl;
	getline(cin, name);

	//cria o regular
	//Utente *ptr = new Regular(name,0,0);

	//nao precisa de fazer cout do id....

	cout << "Sign up executed successfully" << endl;

    BikeMenu();
}

void BikeMenu()
{
	cout
	    << "1- Get Bike" << endl
		<< "2- Return bike" << endl
		<< "3- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 3))
	{
		case 1:
            GetBikeMenu();
			break;
		case 2:
            ReturnBikeMenu();
			break;
		//case 3:
			// MonthlyPaymentMenu();
		    break;
		case 3:
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

	cout << "Type of bike you want ? " << endl;
	cin >> biketype;

	cout << "What is the pick up hour ? " << endl;
	try
	{
	  cin >> horainicial;
	}
    catch(HoraInexistente &e)
	{
    	cout << "Invalid hour" << endl;
    	//return;
	}


	cout << "Bicycle lifted successfully" << endl ;
	cout << endl;

}



void ReturnBikeMenu()
{
	string returningpoint;
	Hora horafinal;
	cleanfunction();
	cout << "Where are you returning the bike ? " << endl;
	getline(cin, returningpoint);
	cout << "What is the returning hour ? " << endl;

	try
		{
		  cin >> horafinal;
		}
	    catch(HoraInexistente &e)
		{
	    	cout << "Invalid hour" << endl;
		}


	cout << "Bicycle returned successfully" << endl;
	cout << endl;
}



