
#ifndef MENU_H_
#define MENU_H_

#include "Cidade.h"

/* Auxiliary functions */


/**
* @brief uses cin.clean() and cin.ignore() to clean the input buffer and the error flag
*/
void cleanfunction();


/**
* @brief gets a number (int) between lower and upper (including both)
*
* @param lower lower number possible to get
* @param upper upper number possible to get
*
* @return the number in the interval given
*/
int getIntInInterval(int lower, int upper);


/**
* @brief gets a number (int)
*
* @return number if cin didn't fail, -1 otherwise
*/
int getInt();

/**
* @brief gets a bike type (string)
* @return the bike type string if it is in fact a bike type, throws an exception otherwise;
*/
string getBikeType();


/*Menu functions*/


void FirstMenu(Cidade &cidade);

void CityManagementMenu(Cidade &cidade);

void UserOptionsMenu(Cidade &cidade);

void AddNewLocationMenu(Cidade &cidade);

void RemoveLocationMenu(Cidade &cidade);

void BikeMenuRU(Cidade &cidade, Utente *utente);

void BikeMenuMember(Cidade &cidade, Utente *utente);

void SignUpMenu(Cidade &cidade);

void SignInMenu(Cidade &cidade);

void SignUpMemberMenu(Cidade &cidade);

void SignUpRegularMenu(Cidade &cidade);

void GetBikeMenu(Cidade &cidade , Utente *utente);

void ReturnBikeMenu(Cidade &cidade, Utente *utente);

void MonthlyPaymentMenu(Cidade &cidade, Utente *utente);

void ClosestLocationMenu(Cidade &cidade, Utente *utente);


#endif /* MENU_H_ */
