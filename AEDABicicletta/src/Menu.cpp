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



double getDouble()
{
	double num;
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
    cin.ignore();
	if (biketype == "urbana") return "Urbana";
	if (biketype == "urbana_simples") return "Urbana_Simples";
	if (biketype == "infantil") return "Infantil";
	if (biketype == "corrida") return "Corrida";
	if ((biketype != "Urbana" ) && (biketype != "Urbana_Simples") && (biketype != "Infantil")  && (biketype != "Corrida"))
	   throw NotAType(biketype);
    else
	    return biketype;
}



bool anobissexto(int ano)
{
	if ((ano % 400) == 0)
		return true;
	else
	{
		if (((ano % 4) == 0) && ((ano % 100) != 0))
			return true;
		else
			return false;
	}
}



int ndiasmes(int mes, int ano)
{
	int res;
	switch (mes)
	{
	case (1): case (3): case (5): case (7): case (8): case (10): case (12):
		res = 31;
		break;
	case (4): case (6): case (9): case (11):
		res = 30;
		break;
	case (2):
	{
		if (anobissexto(ano))
			res = 29;
		else
			res = 28;
	}
	break;
	}
	return res;
}



bool validDate(int dia, int mes, int ano)
{
	if ((mes > 12) || (mes < 0))
		return false;
	if (dia < 0)
		return false;
	int ndias = ndiasmes(mes, ano);
	if (dia > ndias)
		return false;
	return true;
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
			<< "6- Change prices " << endl
			<< "7- Store options" << endl
			<< "8- Part options " << endl
			<< "9- Disassemble options" << endl
			<< "10- Go back" << endl
			<< "Select one" << endl;

		switch (getIntInInterval(1, 10))
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
				cout << "Bikes redistributed successfully." << endl;
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
				ChangePricesMenu(cidade);
				break;
			case 7:
				StoreOptionsMenu(cidade);
				break;
			case 8:
				PartOptionsMenu(cidade);
				break;
			case 9:
				DisassembleBikeMenu(cidade);
				break;
			case 10:
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

 	cout << "Location's coordinates ? (x y) " << endl;
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

 	cout << "Location added successfully." << endl;
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



void ChangePricesMenu(Cidade &cidade)
{
	cout
	<< "1- Change monthly payment (current payment : " << Socio::getMensalidade() << " euros) " << endl
	<< "2- Change bikes price" << endl
	<< "3- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,3))
	{
	case 1:
		double mpayment;
		cout << "New monthly payment ? " << endl;
		mpayment = getDouble();
		if (mpayment == -1)
			return CityManagementMenu(cidade);
		Socio::setMensalidade(mpayment);
		break;
	case 2:
		ChangeBikesPriceMenu(cidade);
		break;
	case 3:
		return CityManagementMenu(cidade);
		break;
	}
}



void ChangeBikesPriceMenu(Cidade &cidade)
{
	double newprice;
	cout
	<< "1- Urbana (current price : " << Urbana::getPreco() << " euros) " << endl
	<< "2- Urbana_Simples (current price : " << Urbana_Simples::getPreco() << " euros) " << endl
	<< "3- Infantil (current price : " << Infantil::getPreco() << " euros) " << endl
	<< "4- Corrida (current price : " << Corrida::getPreco() << " euros) " << endl
	<< "5- All" << endl
	<< "6- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,6))
	{
	case 1:
		cout << "New price ? " << endl;
		newprice = getDouble();
		if (newprice == -1)
			return ChangePricesMenu(cidade);
	    Urbana::setPrecoportipo(newprice);
		break;
	case 2:
		cout << "New price ? " << endl;
		newprice = getDouble();
		if (newprice == -1)
			return ChangePricesMenu(cidade);
		Urbana_Simples::setPrecoportipo(newprice);
		break;
	case 3:
		cout << "New price ? " << endl;
		newprice = getDouble();
		if (newprice == -1)
			return ChangePricesMenu(cidade);
		Infantil::setPrecoportipo(newprice);
		break;
	case 4:
		cout << "New price ? " << endl;
		newprice = getDouble();
		if (newprice == -1)
			return ChangePricesMenu(cidade);
		Corrida::setPrecoportipo(newprice);
		break;
	case 5:
		cout << "New price for Urbana ? " << endl;
		newprice = getDouble();
		if (newprice == -1)
			return ChangePricesMenu(cidade);
	    Urbana::setPrecoportipo(newprice);
	    cout << "New price for Urbana_Simples ? " << endl;
	    newprice = getDouble();
	    if (newprice == -1)
	    	return ChangePricesMenu(cidade);
	    Urbana_Simples::setPrecoportipo(newprice);
	    cout << "New price for Infantil ? " << endl;
	    newprice = getDouble();
	    if (newprice == -1)
	    	return ChangePricesMenu(cidade);
	    Infantil::setPrecoportipo(newprice);
	    cout << "New price for Corrida ? " << endl;
	    newprice = getDouble();
	    if (newprice == -1)
	    	return ChangePricesMenu(cidade);
	    Corrida::setPrecoportipo(newprice);
		break;
	case 6:
		return ChangePricesMenu(cidade);
		break;

	}
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



void StoreOptionsMenu(Cidade &cidade)
{
	string type;
	int number;
	string name;
	vector<Loja> top5;
	vector<Bicicleta*> purchase;
	cout
	<< "1- Get top 5 best reputed stores " << endl
	<< "2- Buy Bikes " << endl
	<< "3- Print Stores" << endl
	<< "4- Go back" << endl
	<< "Select one" << endl;

	switch (getIntInInterval(1, 4))
	{
	case 1:
		try
		{
			top5 = cidade.getTop5();
		}
		catch(NoStores &p)
		{
		    return CityManagementMenu(cidade);
		}
		for (unsigned int i = 0; i < top5.size(); i++)
		{
			top5.at(i).printStore();
			cout << endl;
		}
		break;
	case 2:
		cout << "How many bikes do you want to buy ? " << endl;
		number = getInt();
		cout << "Type of bike ? " << endl;
		try
		{
			type = getBikeType();
		}
		catch (NotAType &t)
		{
			cout << "Invalid type! " << endl;
			return CityManagementMenu(cidade);
		}
		try
		{
			name = cidade.BuyBikes(type,number, purchase);
		}
		catch(InvalidPurchase &i)
		{
		    cout << "Invalid purchase, there is no stores with the number and type of bike you desire." << endl;
		    return CityManagementMenu(cidade);
		}

		cidade.AddPurchasedBikes(purchase);

		cout << "Successful purchase! What is your value of satisfaction with the store services ?  (0-15) " << endl;
		number = getIntInInterval(0,15);
		try
		{
			cidade.setStoreReputation(name,number);
		}
		catch(InvalidStore &p)
		{
			cout << "Invalid operation." << endl;
			return CityManagementMenu(cidade);
		}
		break;
	case 3:
		cidade.printStoresInMenu();
		break;
	case 4 :
	    return CityManagementMenu(cidade);
		break;
	}
}



void PartOptionsMenu(Cidade &cidade)
{
	string name;
	string supplier ;
	double price;
	double lowestprice;
	string lowestsupplier;
	Part p1 ("","",0);

	cout
	<< "1- Add part" << endl
	<< "2- Remove part" << endl
	<< "3- Buy part " << endl
	<< "4- Lowest price" << endl
	<< "5- Print suppliers" << endl
	<< "6- Go back" << endl
	<< "Select one" << endl;

	switch (getIntInInterval(1, 6))
	{

	case 1:
		cleanfunction();
		cout << "Name of the part ?  " << endl;
		getline(cin,name);
		cout << "Name of the supplier ? " << endl;
		getline(cin,supplier);
		cout << "Price ? " << endl;
		price = getDouble();
		p1.setNamePart(name);
		p1.setSupplier(supplier);
		p1.setUnitPrice(price);
		try
		{
			cidade.insertPart(p1);
			cout << "Part added successfully !" << endl;
		}
		catch(InsertionError &p)
		{
			cout << "Error inserting the part !" << endl;
			return CityManagementMenu(cidade);
		}
		break;
	case 2:
		cleanfunction();
		cout << "Name of the part ?  " << endl;
		getline(cin,name);
		cout << "Name of the supplier ? " << endl;
		getline(cin,supplier);
		cout << "Price ? " << endl;
		price = getDouble();
		try
		{
			cidade.removePart(name,supplier);
			cout << "Part removed successfully ! " << endl;
		}
		catch( RemovingError &p)
		{
			cout << "Error removing the part !" << endl;
			return CityManagementMenu(cidade);
		}
		break;
	case 3:
		cleanfunction();
		cout << "Name of the part ?  " << endl;
		getline(cin,name);
		cout << "Name of the supplier ? " << endl;
		getline(cin,supplier);
		cout << "Price ? " << endl;
		price = getDouble();
		p1.setNamePart(name);
		p1.setSupplier(supplier);
		p1.setUnitPrice(price);
		try
		{
			cidade.buyPart(p1);
			cout << "Successful purchase ! " << endl;
		}
		catch(InvalidPartPurchase &p)
		{
			cout << "Invalid purchase ! " << endl;
			return CityManagementMenu(cidade);
		}
		break;
	case 4:
		cleanfunction();
		cout << "Name of the part ? " << endl;
		getline(cin,name);
		try
		{
			Part p2  = cidade.getLowestPrice(name);
			lowestprice = p2.getUnitPrice();
			lowestsupplier = p2.getSupplier();
		}
		catch(InvalidPart &p)
		{
			cout << "Invalid part ! " << endl;
			return CityManagementMenu(cidade);
		}
		cout << "The lowest price for part " << name << " is " << lowestprice << " from supplier " << lowestsupplier << ". "<< endl;
		break;
	case 5 :
		cidade.printSuppliers(cout);
		break;
	case 6:
	    return CityManagementMenu(cidade);
		break;
	}
}



void DisassembleBikeMenu(Cidade &cidade)
{
	int bikeid;
	cout
	<< "1- Disassemble bike" << endl
	<< "2- Delete bike " << endl
	<< "3- Print bikes for disassemble" << endl
	<< "4- Go back" << endl
	<< "Select one" << endl;

	switch (getIntInInterval(1,4))
	{
	case 1:
		DisassembleMenu(cidade);
		break;
	case 2 :
		cout << "Bike's id number ?" << endl;
		bikeid = getInt();
		try
		{
			cidade.deleteBike(bikeid);
		}
		catch(BikeNotExist &r)
		{
			cout << "The bike does not exist ! " << endl;
			return CityManagementMenu(cidade);
		}
		break;
	case 3:
		cidade.consultBikes();
		break;
	case 4:
		return CityManagementMenu(cidade);
		break;
	}

}



void DisassembleMenu(Cidade & cidade)
{
	int bikeid;
	string date;
	cout << "Bike's id number ?" << endl;
	bikeid = getInt();
	cout << "Disassemble date ? (day/month/year) " << endl;
	cin >> date;
	Date d1(date);

	if (validDate(d1.getDay(),d1.getMonth(), d1.getYear()) == false)
	{
		cout << "Invalid date !" << endl;
		return CityManagementMenu(cidade);
	}

	try
	{
		cidade.disassembleBike(bikeid,date);
	}
	catch( BikeAlreadyDisassembled &o)
	{
		cout << "The bike has already been disassembled !" << endl;
		return CityManagementMenu(cidade);
	}
	catch (BikeNotExist &t)
	{
		cout << "The bike does not exist ! " << endl;
		return CityManagementMenu(cidade);
	}
	cout << "Bike disassembled successfully !" << endl;
}



void SignInMenu(Cidade &cidade)
{
	int idnumber;
    cout << "ID number ? " << endl;
    idnumber = getInt();
    if (idnumber == -1)
    	return UserOptionsMenu(cidade);
    Utente *ptr;
    try
    {
    	ptr = cidade.findUtente(idnumber);
    }
    catch(NoUserFound &e)
    {
    	cout << "No user found with that id, try signing up." << endl;
    	return;
    }

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
		<< "4- Delete account" << endl
		<< "5- Check bike prices" << endl
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
			cout
			<< "Urbana : " << Urbana::getPreco() << " euros per hour." << endl
			<< "Urbana_Simples : " << Urbana_Simples::getPreco() << " euros per hour." << endl
			<< "Infantil : " << Infantil::getPreco()<< " euros per hour." << endl
			<< "Corrida : " << Corrida::getPreco() << " euros per hour." << endl
			<< endl;
			break;
		case 6:
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
		<< "4- Check accumulated hours " << endl
		<< "5- Monthly Payment" << endl
		<< "6- Delete account " << endl
		<< "7- Go back" << endl
		<< "Select one" << endl;

	switch (getIntInInterval(1, 7))
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
			cout << "Total renting hours : " << utente->getTotalHorasAcumuladas() << "." << endl;
			break;
		case 5:
			MonthlyPaymentMenu(cidade, utente);
			break;
		case 6:
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
		case 7:
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

	cout << "What is the pick up hour ? (horas:minutes) " << endl;
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
	cout << "What is the returning hour ? (horas:minutes)" << endl;
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
	    	cout << "Invalid hour." << endl;
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
	    	cout << horafinal << endl;
	    	cout << utente->getHoraInicial().hora << " " << utente->getHoraInicial().minutos << endl;
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
  			cout << "What are your coordinates at the moment ? (x y)" << endl;
  			try
  			{
  			cin >> cord;
  			}
  			catch(InvalidCoordinates &c)
  			{
  				if(cin.fail())
  				{
  					cin.ignore(1000, '\n');
  					cin.clear();
  				}
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
  			cout << "What are your coordinates at the moment ? (x y)" << endl;
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
  			  cout << "Invalid type." << endl;
  			if (esocio)
  			  return BikeMenuMember(cidade, utente);
  			else
  			  return BikeMenuRU(cidade, utente);
  			}

  			try
  			{
  				it = cidade.closestType(cord,biketype);
  			}
  			catch(NotAType &e)
  			{
  				cout << "Invalid type." << endl;
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
	string pointfile, userfile, storefile, partfile, bikefile;
	cout
	<< "1- Points" << endl
	<< "2- Users"  << endl
	<< "3- Stores" << endl
	<< "4- Parts" << endl
	<< "5- Bikes for disassemble" << endl
	<< "6- All" << endl
	<< "7- Go back" << endl
	<< "Select one" << endl;

	switch(getIntInInterval(1,7))
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
		cout << "Name of the file to save the stores ? " << endl;
		storefile = getFileName();
		cidade.printStoresFile(storefile);
		break;
	case 4:
		cout << "Name of the file to save the parts ? " << endl;
		partfile = getFileName();
		cidade.printParts(storefile);
		break;
	case 5:
		cout << "Name f the file to save the bikes for disassemble ? " << endl;
		bikefile = getFileName();
		cidade.printBikes(bikefile);
		break;
	case 6:
		cout << "Name of the file to save the points ?" << endl;
		pointfile = getFileName();
		cidade.printPointsFile(pointfile);
		cout << "Name of the file to save the users ? " << endl;
		userfile = getFileName();
		cidade.printUserstoFile(userfile);
		cout << "Name of the file to save the stores ? " << endl;
		storefile = getFileName();
		cidade.printStoresFile(storefile);
		cout << "Name of the file to save the parts ? " << endl;
		partfile = getFileName();
		cidade.printParts(storefile);
		cout << "Name of the file to save the bikes for disassemble ? " << endl;
		bikefile = getFileName();
		cidade.printBikes(bikefile);
		break;
	case 7:
		return;
		break;
	}
}


