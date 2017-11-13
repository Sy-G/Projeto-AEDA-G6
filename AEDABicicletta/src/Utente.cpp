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

Utente::Utente(string nome, int cordX, int cordY): coordenada(cordX, cordY), horainicial("00:00"), horafinal("00:00"), ID(ultimoID++) {
	// TODO Auto-generated constructor stub
	this->nome = nome;
	this->bicicleta = NULL; //no momento de registo/cria��o de UTENTE, este ainda n�o tem uma bicicleta associada, s� tem quando a levantar.
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

	sucesso = false; //para j� ..

	//verificar que no ponto em quest�o h� bicicletas disponiveis.

	if(p1->getnumbicicletasDisponiveis() == 0){
		//EXCE��O PONTO VAZIO!
		throw PontoVazio(p1->getNome());
	}

	//verificar se o Utente j� tem uma bicicleta

	if(this->bicicleta != NULL){
		//EXCE��O J� TEM BICICLETA
		throw JaTemBicicletaException(this->nome);
	}

	//As bicicletas s�o levantadas por tipo.

	for(i = 0; i < p1->getBicicletas().size(); i++){

		if(p1->getBicicletas().at(i)->getTipo() == tipo){
			//atribu�-se essa bicicleta ao utente
			this->setBicicleta(p1->getBicicletas().at(i));

			//agora retira-se essa bicicleta do vetor de bicicletas disponiveis desse ponto
			p1->rmBicicleta(p1->getBicicletas().at(i)->getID());

			//regista-se a hora de levantamento
			this->horainicial = Hora(horainical);
			sucesso = true;
			break;
		}

	}

	if(sucesso == false){
		//EXCE��O BICICLETA N�O EXISTENTE!!
		throw Bicicleta_Inexistente(p1->getBicicletas().at(i)->getID());
	}
}

double Regulares::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){
	string hora;
	double pagamento;

	//deve de verificar se o ponto est� cheio

	if(p1->getBicicletas().size() >= p1->getCapacidade()){
		//EXCE��O PONTO CHEIO!!
		throw NoSpace(p1->getCapacidade());
	}

	//deve de verificar se o utente tem uma bicicleta para dar

	if(this->bicicleta == NULL){
		//EXCE��O N�O TEM BICICLETA
		throw NaoTemBicicletaException(this->nome);
	}

	//caso contr�rio, adiciona-se a bicicleta ao ponto e retira-se do cliente, mas, como a bicicleta guarda informa��es precisas para calcular o pagamento, s� ser� retirado o apontador mais tarde.
	p1->addBicicleta(this->bicicleta);

	this->horafinal = Hora(horafinal);

	//como o cliente � um regular, ter� de pagar j�, calcular o pagamento.
	pagamento = getPagamento();

	//depois de chamar getPagamento, poder� ser retirada a bicicleta.
	this->bicicleta = NULL;

	return pagamento;
}

double Socio::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){
	string verifica;
	double quantidade;

	//deve de verificar se o ponto est� cheio
	if(p1->getBicicletas().size() > p1->getCapacidade()){
		//EXCE��O PONTO CHEIO!!
		throw NoSpace(p1->getCapacidade());
	}

	//deve de verificar se o utente tem uma bicicleta para dar
	if(this->bicicleta == NULL){
		//EXCE��O N�O TEM BICICLETA
		throw NaoTemBicicletaException(this->nome);
	}

	//caso contr�rio, adiciona-se a bicicleta ao ponto e retira-se do cliente.
	p1->addBicicleta(this->bicicleta);

	//retira-se ao cliente
	this->bicicleta = NULL;


	this->horafinal = Hora(horafinal);

	//calcular o tempo de uso
	subtraiHora(this->horafinal, this->horainicial);

	//envia o tempo dessa sess�o de uso para o vetor para acumular.
	horasaccumuladas.push_back(tempouso);

	cout << "Do you want to pay your monthly bill? (S/N): ";
	cin >> verifica;

	if(verifica == "S"){
		quantidade = getPagamento();
		return quantidade;
	} else return 0;
}

double Regulares::getPagamento(){
	//o pagamento � calculado multiplicando as horas de uso pelo pre�o por tipo da bicicleta.
	double quantidade;

	//primeiro calcular o tempo de uso
	subtraiHora(this->horafinal, this->horainicial);

	//multiplicar o tempouso pelo preco por tipo da bicicleta.
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
		//tem 10% de desconto!
		quantia = mensalidade - (mensalidade*0.1);
	}

	if(acumulador <= 20 && acumulador > 0){
		//tem 5% de desconto
		quantia = mensalidade - (mensalidade*0.05);
	}

	if(acumulador == 0){
		quantia = mensalidade;
	}

	//reiniciar o vetor de acumula��o
	for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
		horasaccumuladas.erase(horasaccumuladas.begin()+i);
	}

	return quantia;
}

double Utente::getPagamento(){
	return 0.0;
}

Utente::~Utente() {}

double Utente::devolveBicicleta(vector<Ponto>::iterator p1, Hora horafinal){}

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

bool Utente::eSocio(){}

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

Utente::Utente(const string& name, const string& other): horainicial("00:00"), horafinal("00:00"), ID(ultimoID++) {
	istringstream in;
	in.str(other);
	this->nome = name;
	this->bicicleta = NULL; //no momento de registo/cria��o de UTENTE, este ainda n�o tem uma bicicleta associada, s� tem quando a levantar.
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
