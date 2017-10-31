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

Utente::Utente(string nome,int ID, int cordX, int cordY): coordenada(cordX, cordY), horainicial("00:00"), horafinal("00:00") {
	// TODO Auto-generated constructor stub
	this->nome = nome;
	this->ID = ID;
	this->bicicleta = NULL; //no momento de registo/cria��o de UTENTE, este ainda n�o tem uma bicicleta associada, s� tem quando a levantar.
	this->tempouso = 0;
}

Regulares::Regulares(string nome,int ID, int cordX, int cordY): Utente(nome,ID,cordX, cordY){}

Socio::Socio(string nome,int ID,int cordX, int cordY): Utente(nome,ID,cordX, cordY){}

Bicicleta* Utente::getBicicleta(){
	return bicicleta;
}

Hora Utente::getHoraInicial(){
	return horainicial;
}

void Utente::levantaBicicleta(Ponto *&p1, string tipo, Hora horainical){
	bool sucesso;
	unsigned int i;

	sucesso = false; //para j� ..

	//verificar que no ponto em quest�o h� bicicletas disponiveis.

	if(p1->getnumbicicletasDisponiveis() == 0){
		cout << "N�o h� bicicletas dispon�veis neste ponto!" << endl;
		//EXCE��O PONTO VAZIO!
	}

	//verificar se o Utente j� tem uma bicicleta

	if(this->bicicleta != NULL){
		//EXCE��O J� TEM BICICLETA
	}

	//As bicicletas s�o levantadas por tipo.

	for(i = 0; i < p1->getBicicletas().size(); i++){

		if(p1->getBicicletas().at(i)->getTipo() == tipo){
			//atribu�-se essa bicicleta ao utente
			this->setBicicleta(p1->getBicicletas().at(i));

			//agora retira-se essa bicicleta do vetor de bicicletas disponiveis desse ponto
			p1->rmBicicleta(p1->getBicicletas().at(i)->getID());

			this->horainicial = Hora(horainical);
			sucesso = true;
			break;
		}

	}

	if(sucesso == false){
		//EXCE��O BICICLETA N�O EXISTENTE!!
	}
}

double Regulares::devolveBicicleta(Ponto *&p1, Hora horafinal){
	string hora;
	double pagamento;

	//deve de verificar se o ponto est� cheio

	if(p1->getBicicletas().size() == p1->getCapacidade()){
		cout << "O ponto est� cheio!" << endl;
		//EXCE��O PONTO CHEIO!!
	}

	//deve de verificar se o utente tem uma bicicleta para dar

	if(this->bicicleta == NULL){
		cout << "O cliente n�o tem uma bicicleta para devolver." << endl;
		//EXCE��O N�O TEM BICICLETA
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

double Socio::devolveBicicleta(Ponto *&p1, Hora horafinal){
	string verifica;
	double quantidade;

	//deve de verificar se o ponto est� cheio
	if(p1->getBicicletas().size() > p1->getCapacidade()){
		cout << "O ponto est� cheio!" << endl;
		//EXCE��O PONTO CHEIO!!
	}

	//deve de verificar se o utente tem uma bicicleta para dar
	if(this->bicicleta == NULL){
		cout << "O cliente n�o tem uma bicicleta para devolver." << endl;
		//EXCE��O N�O TEM BICICLETA
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

	cout << "O cliente � s�cio, deseja fazer o checkout do final do m�s? (S/N): ";
	cin >> verifica;

	if(verifica == "S"){
		quantidade = getPagamento();

		//reiniciar o vetor de acumula��o
		for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
			horasaccumuladas.erase(horasaccumuladas.begin()+i);
		}

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
	unsigned int horainicialtotal, horafinaltotal;

	horainicialtotal = horainicial.hora + ((horainicial.minutos)/60);
	horafinaltotal = horafinal.hora + ((horafinal.minutos)/60);

	this->tempouso = horafinaltotal - horainicialtotal;
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

	return quantia;
}

double Utente::getPagamento(){
	return 0.0;
}

Utente::~Utente() {}

double Utente::devolveBicicleta(Ponto *&p1, Hora horafinal){}

string Utente::getNome(){
	return nome;
}


Hora Utente::getHoraFinal(){
	return this->horafinal;
}

void Utente::setBicicleta(Bicicleta *b1){
	this->bicicleta = b1;
}
