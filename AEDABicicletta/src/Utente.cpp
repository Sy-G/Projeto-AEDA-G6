/*
 * Utente.cpp
 *
 *  Created on: 18/10/2017
 *      Author: Work
 */

#include "Cidade.h"
#include "Ponto.h"
#include "Bicicleta.h"
#include <iostream>
using namespace std;

double Socio::mensalidade = 27.5;
int Utente::ultimoID = 0;

Utente::Utente(string nome, int cordX, int cordY): coordenada(cordX, cordY), horainicial(), horafinal(), ID(ultimoID++) {
	// TODO Auto-generated constructor stub
	this->nome = nome;
	this->bicicleta = NULL; //upon creation of the object, the user doesn't have a bike yet because he just registered.
	this->tempouso = 0;
}

Regulares::Regulares(string nome, int cordX, int cordY): Utente(nome, cordX, cordY){}

Socio::Socio(string nome, int cordX, int cordY): Utente(nome, cordX, cordY){}

Bicicleta* Utente::getBicicleta(){
	return bicicleta;
}

Hora Utente::getHoraInicial(){
	return horainicial;
}


void Utente::levantaBicicleta(vector<Ponto>:: iterator p1, string tipo, Hora horainical){
	bool sucesso;
	unsigned int i;

	sucesso = false; //for now ..

	//check if you have any bicycles available in this point.

	if(p1->getnumbicicletasDisponiveis() == 0){
		//Empty point exception
		throw PontoVazio(p1->getNome());
	}

	//check if he has a bike already

	if(this->bicicleta != NULL){
		//User already has a bike and can't withdraw one exception
		throw JaTemBicicletaException(this->nome);
	}

	//Bicycles are withdrawn by type

	for(i = 0; i < p1->getBicicletas().size(); i++){

		if(p1->getBicicletas().at(i)->getTipo() == tipo){

			//give that bicycle to the user
			this->setBicicleta(p1->getBicicletas().at(i));

			//take that bike away from the vector of available bikes
			p1->rmBicicleta(p1->getBicicletas().at(i)->getID());

			//register the withdrawal hour
			this->horainicial = Hora(horainical);

			sucesso = true;
			break;
		}

	}

	if(sucesso == false){
		//No bicycles of that type exist ..
		throw Bicicleta_Inexistente(p1->getBicicletas().at(i)->getID());
	}
}

double Regulares::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){
	string hora;
	double pagamento;

	//check if this point is full

	if(p1->getBicicletas().size() >= p1->getCapacidade()){
		//full point exception
		throw NoSpace(p1->getCapacidade());
	}

	//check if the user even has a bike to deposit

	if(this->bicicleta == NULL){
		//no bike exception
		throw NaoTemBicicletaException(this->nome);
	}

	//add this bicicle to the point in question
	p1->addBicicleta(this->bicicleta);

	//register deposit hour
	this->horafinal = Hora(horafinal);

	//since the client is a regular, we have to get his payment upon returning the bike.
	pagamento = getPagamento();

	//the function that acquires the payment still needs to interact with the bicycle pointer, after calling it there is no need for it anymore and so it must be removed.
	this->bicicleta = NULL;

	return pagamento;
}

double Socio::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){
	string verifica;
	double quantidade;

	// SAME LOGIC AS REGULAR
	if(p1->getBicicletas().size() > p1->getCapacidade()){
		throw NoSpace(p1->getCapacidade());
	}

	if(this->bicicleta == NULL){
		throw NaoTemBicicletaException(this->nome);
	}


	p1->addBicicleta(this->bicicleta);

	// Now here is the difference, in this case, we don't take the bike itself into account so we can remove the pointer right away.
	this->bicicleta = NULL;


	//deposit hour
	this->horafinal = Hora(horafinal);

	//calculates the time of use for this session.
	subtraiHora(this->horafinal, this->horainicial);

	//sends that time into a vector of accumulated hours
	horasaccumuladas.push_back(tempouso);

	//in case the user isn't going to use any more bikes after this, or he returned it at the end of the month ..

	cout << "Do you want to pay your monthly bill? (Y/N): ";
	cin >> verifica;

	if(verifica == "Y"){
		quantidade = getPagamento();
		return quantidade;
	} else return 0;
}

double Regulares::getPagamento(){
	//paymente caculation equals time of use times bicicle price per hour.
	double quantidade;

	//calculating time of use
	subtraiHora(this->horafinal, this->horainicial);

	//multiplying time of use by price per hour
	quantidade = this->bicicleta->getPrecoportipo()*this->tempouso;

	return quantidade;
}

void Utente::subtraiHora(Hora horafinal, Hora horainicial){
	this->tempouso = horafinal - horainicial;
}

double Socio::getPagamento(){
	double quantia;
	double acumulador;

	quantia = 0;
	acumulador = 0;

	for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
		acumulador = horasaccumuladas.at(i) + acumulador;
	}

	if(acumulador > 20){
		//10% discount
		quantia = mensalidade - (mensalidade*0.1);
	}

	if(acumulador <= 20 && acumulador > 0){
		//5% discount
		quantia = mensalidade - (mensalidade*0.05);
	}

	if(acumulador == 0){
		quantia = mensalidade;
	}

	//empty the accumulated hours, they've already been taken into account
	for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
		horasaccumuladas.erase(horasaccumuladas.begin()+i);
	}

	return quantia;
}

double Socio::getTotalHorasAcumuladas()
{
	 double acumulador = 0;
	 for(unsigned int i = 0; i < horasaccumuladas.size(); i++)
	 {
			acumulador = horasaccumuladas.at(i) + acumulador;
	 }
	 return acumulador;
}

double Utente::getPagamento(){
	return 0.0;
}

Utente::~Utente() {}

double Utente::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){return 0;}

string Utente::getNome(){
	return nome;
}

Hora Utente::getHoraFinal(){
	return this->horafinal;
}


void Utente::setBicicleta(Bicicleta *b1){
	this->bicicleta = b1;
}

bool Socio::eSocio()
{
	return true;
}

bool Regulares::eSocio()
{
	return false;
}

bool Utente::eSocio(){
	return false;
}

int Utente::getID(){
	return ID;
}

Coordenadas Utente::getCoordenadas(){
	return coordenada;
}

 inline ostream & operator<<(ostream &Outstream, const Utente &u){
	u.printUtente(Outstream);
	return (Outstream);
}

Utente::Utente(const string& name, const string& other): horainicial(), horafinal(), ID(ultimoID++) {
	istringstream in;
	in.str(other);
	this->nome = name;
	this->bicicleta = NULL;
	this->tempouso = 0;

	in >> this->coordenada;

}

Regulares::Regulares(const string& name, const string& other): Utente(name, other){}

Socio::Socio(const string& name, const string& other): Utente(name, other){}

void Utente::printUtente(ostream &OutStream) const{
	//empty space
}

void Regulares::printUtente(ostream &Outstream) const{
	Outstream << "Regular: ";
	Outstream << this->nome;
	Outstream << "\n";
	Outstream << "ID: ";
	Outstream << this->ID;
	Outstream << "\n";
	Outstream << "Coordinates: ";
	Outstream << this->coordenada.cordX;
	Outstream << ",";
	Outstream << this->coordenada.cordY;
	Outstream << "\n";
	Outstream << "Bicycle: ";
	if(this->bicicleta == NULL){
		Outstream << "This user has no bike at the moment.";
	} else {
		Outstream << "ID: ";
		Outstream << this->bicicleta->getID();
		Outstream << " ";
		Outstream << "Type: ";
		Outstream << this->bicicleta->getTipo();
		Outstream << "\n";
	}
	Outstream << endl;
}

void Socio::printUtente(ostream &Outstream) const {
	Outstream << "Member: ";
	Outstream << this->nome;
	Outstream << "\n";
	Outstream << "ID: ";
	Outstream << this->ID;
	Outstream << "\n";
	Outstream << "Coordinates: ";
	Outstream << this->coordenada.cordX;
	Outstream << ",";
	Outstream << this->coordenada.cordY;
	Outstream << " \n";
	Outstream << "Bicycle: ";
	if(this->bicicleta == NULL){
		Outstream << "This user has no bike at the moment.";
	} else {
		Outstream << "ID: ";
		Outstream << this->bicicleta->getID();
		Outstream << " ";
		Outstream << "Type: ";
		Outstream << this->bicicleta->getTipo();
		Outstream << "\n";
	}
	Outstream << endl;
}
