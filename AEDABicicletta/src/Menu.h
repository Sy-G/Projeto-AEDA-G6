
#ifndef MENU_H_
#define MENU_H_

#include "Cidade.h"

/* Auxiliary functions */


/**
* @brief Uses cin.clean() and cin.ignore() to clean the input buffer and the error flag
*/
void cleanfunction();



/**
* @brief Gets a number (int) between lower and upper (including both)
*
* @param lower Lower number possible to get
* @param upper Upper number possible to get
*
* @return A number in the interval given
*/
int getIntInInterval(int lower, int upper);



/**
* @brief Gets a number (int)
*
* @return Number if cin didn't fail, -1 otherwise
*/
int getInt();



/**
* @brief Gets a file name
*
* @return The name of the file
*/
string getFileName();



/**
* @brief Getts a bike type (string)
* @return The bike type string if it is in fact a bike type, throws an exception otherwise
*/
string getBikeType();



/*Menu functions*/

/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void FirstMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void CityManagementMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void UserOptionsMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void AddNewLocationMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void RemoveLocationMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 * @param utente User that is using the program
 */
void BikeMenuRU(Cidade &cidade, Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 * @param utente User that is using the program
 */
void BikeMenuMember(Cidade &cidade, Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void SignUpMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void SignInMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void SignUpMemberMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void SignUpRegularMenu(Cidade &cidade);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void GetBikeMenu(Cidade &cidade , Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 * @param utente User that is using the program
 */
void ReturnBikeMenu(Cidade &cidade, Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 * @param utente User that is using the program
 */
void MonthlyPaymentMenu(Cidade &cidade, Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 * @param utente User that is using the program
 */
void ClosestLocationMenu(Cidade &cidade, Utente *utente);



/*
 * @brief Calls the functions needed to implement the presented functionalities
 * @param cidade City where the points are located
 */
void SaveChangesMenu(Cidade &cidade);



#endif /* MENU_H_ */
