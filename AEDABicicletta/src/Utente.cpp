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
	this->bicicleta = NULL; //no momento de registo/criação de UTENTE, este ainda não tem uma bicicleta associada, só tem quando a levantar.
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


void Utente::levantaBicicleta(Ponto *p1, string tipo, Hora &horainical){
	bool sucesso;
	unsigned int i;

	sucesso = false; //para já ..

	//verificar que no ponto em questão há bicicletas disponiveis.

	if(p1->getnumbicicletasDisponiveis() == 0){
		//EXCEÇÃO PONTO VAZIO!
		throw PontoVazio(p1->getNome());
	}

	//verificar se o Utente já tem uma bicicleta

	if(this->bicicleta != NULL){
		//EXCEÇÃO JÁ TEM BICICLETA
		throw JaTemBicicletaException(this->nome);
	}

	//As bicicletas são levantadas por tipo.

	for(i = 0; i < p1->getBicicletas().size(); i++){

		if(p1->getBicicletas().at(i)->getTipo() == tipo){
			//atribuí-se essa bicicleta ao utente
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
		//EXCEÇÃO BICICLETA NÃO EXISTENTE!!
		throw Bicicleta_Inexistente(p1->getBicicletas().at(i)->getID());
	}
}

double Regulares::devolveBicicleta(Ponto *p1, Hora horafinal){
	string hora;
	double pagamento;

	//deve de verificar se o ponto está cheio

	if(p1->getBicicletas().size() >= p1->getCapacidade()){
		//EXCEÇÃO PONTO CHEIO!!
		throw NoSpace(p1->getCapacidade());
	}

	//deve de verificar se o utente tem uma bicicleta para dar

	if(this->bicicleta == NULL){
		//EXCEÇÃO NÃO TEM BICICLETA
		throw NaoTemBicicletaException(this->nome);
	}

	//caso contrário, adiciona-se a bicicleta ao ponto e retira-se do cliente, mas, como a bicicleta guarda informações precisas para calcular o pagamento, só será retirado o apontador mais tarde.
	p1->addBicicleta(this->bicicleta);

	this->horafinal = Hora(horafinal);

	//como o cliente é um regular, terá de pagar já, calcular o pagamento.
	pagamento = getPagamento();

	//depois de chamar getPagamento, poderá ser retirada a bicicleta.
	this->bicicleta = NULL;

	return pagamento;
}

double Socio::devolveBicicleta(Ponto *p1, Hora horafinal){
	string verifica;
	double quantidade;

	//deve de verificar se o ponto está cheio
	if(p1->getBicicletas().size() > p1->getCapacidade()){
		//EXCEÇÃO PONTO CHEIO!!
		throw NoSpace(p1->getCapacidade());
	}

	//deve de verificar se o utente tem uma bicicleta para dar
	if(this->bicicleta == NULL){
		//EXCEÇÃO NÃO TEM BICICLETA
		throw NaoTemBicicletaException(this->nome);
	}

	//caso contrário, adiciona-se a bicicleta ao ponto e retira-se do cliente.
	p1->addBicicleta(this->bicicleta);

	//retira-se ao cliente
	this->bicicleta = NULL;


	this->horafinal = Hora(horafinal);

	//calcular o tempo de uso
	subtraiHora(this->horafinal, this->horainicial);

	//envia o tempo dessa sessão de uso para o vetor para acumular.
	horasaccumuladas.push_back(tempouso);

	cout << "O cliente é sócio, deseja fazer o checkout do final do mês? (S/N): ";
	cin >> verifica;

	if(verifica == "S"){
		quantidade = getPagamento();
		return quantidade;
	} else return 0;
}

double Regulares::getPagamento(){
	//o pagamento é calculado multiplicando as horas de uso pelo preço por tipo da bicicleta.
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

	//reiniciar o vetor de acumulação
	for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
		horasaccumuladas.erase(horasaccumuladas.begin()+i);
	}

	return quantia;
}

double Utente::getPagamento(){
	return 0.0;
}

Utente::~Utente() {}

double Utente::devolveBicicleta(Ponto *p1, Hora horafinal){}

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
	this->bicicleta = NULL; //no momento de registo/criação de UTENTE, este ainda não tem uma bicicleta associada, só tem quando a levantar.
	this->tempouso = 0;

	in >> this->coordenada.cordX >> this->coordenada.cordY;
}

Regulares::Regulares(const string& name, const string& other): Utente(name, other){}

Socio::Socio(const string& name, const string& other): Utente(name, other){}

void Utente::printUtente(ostream &OutStream) const{
	//empty space
}

void Regulares::printUtente(ostream &Outstream) const{
	Outstream << "Regular: ";
	Outstream << this->nome;
	Outstream << " ";
	Outstream << "ID: ";
	Outstream << this->ID;
	Outstream << " ";
	Outstream << "Coordinates: ";
	Outstream << "(";
	Outstream << this->coordenada.cordX;
	Outstream << ",";
	Outstream << this->coordenada.cordY;
	Outstream << ")";
	Outstream << " ";
	Outstream << "Bicycle: ";
	if(this->bicicleta == NULL){
		Outstream << "This user has no bike at the moment.";
	} else {
		Outstream << "ID: ";
		Outstream << this->bicicleta->getID();
		Outstream << " ";
		Outstream << "Type: ";
		Outstream << this->bicicleta->getTipo();
		Outstream << " ";
	}
	Outstream << endl;
}

void Socio::printUtente(ostream &Outstream) const {
	Outstream << "Associate: ";
	Outstream << this->nome;
	Outstream << " ";
	Outstream << "ID: ";
	Outstream << this->ID;
	Outstream << " ";
	Outstream << "Coordinates: ";
	Outstream << "(";
	Outstream << this->coordenada.cordX;
	Outstream << ",";
	Outstream << this->coordenada.cordY;
	Outstream << ")";
	Outstream << " ";
	Outstream << "Bicycle: ";
	if(this->bicicleta == NULL){
		Outstream << "This user has no bike at the moment.";
	} else {
		Outstream << "ID: ";
		Outstream << this->bicicleta->getID();
		Outstream << " ";
		Outstream << "Type: ";
		Outstream << this->bicicleta->getTipo();
		Outstream << " ";
	}
	Outstream << endl;
}
