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
	this->bicicleta = NULL; //no momento de registo/criação de UTENTE, este ainda não tem uma bicicleta associada, só tem quando a levantar.
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

void Utente::levantaBicicleta(Ponto *p1){
	string tipo;
	string hora;
	bool sucesso;

	sucesso = false; //para já ..

	//verificar que no ponto em questão há bicicletas disponiveis.

	if(p1->getnumbicicletasDisponiveis() == 0){
		cout << "Não há bicicletas disponíveis neste ponto!" << endl;
		//EXCEÇÃO PONTO VAZIO!
	}

	//verificar se o Utente já tem uma bicicleta

	if(this->bicicleta != NULL){
		//EXCEÇÃO JÁ TEM BICICLETA
	}

	//As bicicletas são levantadas por tipo.

	cout << "Qual o tipo de bicicleta que vai querer levantar? ";
	cin >> tipo;

	for(unsigned int i = 0; i < p1->getBicicletas().size(); i++){
		if(p1->getBicicletas().at(i)->getTipo() == tipo){

			//agora vamos associar a bicicleta ao utente em função do seu tipo.

			if(tipo == "Urbana")
			{
				this->bicicleta = new Urbana(p1->getBicicletas().at(i)->getID());
				break;
			};

			if(tipo == "Urbana_Simples")
			{
				this->bicicleta = new Urbana_Simples(p1->getBicicletas().at(i)->getID());
				break;
			}

			if(tipo == "Infantil")
			{
				this->bicicleta = new Infantil(p1->getBicicletas().at(i)->getID());
				break;
			}

			if(tipo == "Corrida")
			{
				this->bicicleta = new Corrida(p1->getBicicletas().at(i)->getID());
				break;
			}
		}

			p1->getBicicletas().erase(p1->getBicicletas().begin()+i);
			//agora retira-se essa bicicleta do vetor de bicicletas disponiveis desse ponto.

			cout << "Bicicleta levantada com sucesso!" << endl;
			cout << endl;
			sucesso = true;

			//registar a hora de entrada para começar a contar o tempo de uso!
			cout << "Qual a hora de levantamento? ";
			cin >> hora;

			this->horainicial = Hora(hora);
		}

	if(sucesso == false){
		cout << "Não há bicicletas desse tipo neste ponto." << endl;
		//EXCEÇÃO BICICLETA NÃO EXISTENTE!!
	}
}

void Regulares::devolveBicicleta(Ponto *p1){
	string hora;

	//deve de verificar se o ponto está cheio

	if(p1->getBicicletas().size() == p1->getCapacidade()){
		cout << "O ponto está cheio!" << endl;
		//EXCEÇÃO PONTO CHEIO!!
	}

	//deve de verificar se o utente tem uma bicicleta para dar

	if(this->bicicleta == NULL){
		cout << "O cliente não tem uma bicicleta para devolver." << endl;
		//EXCEÇÃO NÃO TEM BICICLETA
	}

	//caso contrário, adiciona-se a bicicleta ao ponto e retira-se do cliente, mas, como a bicicleta guarda informações precisas para calcular o pagamento, só será retirado o apontador mais tarde.

	p1->getBicicletas().push_back(bicicleta);
	//adciona-se ao ponto

	cout << "Bicicleta devolvida!" << endl;
	cout << endl;

	cout << "Qual a hora de devolução? ";
	cin >> hora;

	Hora temp(hora);

	if(temp.hora < this->horainicial.hora){
		cout << "Hora inválida!" << endl;
		//EXCEÇÃO HORA INVÁLIDA!
	}

	this->horafinal = Hora(hora);

	//como o cliente é um regular, terá de pagar já

	cout << "O cliente tem de pagar: ";
	cout << getPagamento();

	//depois de chamar getPagamento, poderá ser retirada a bicicleta.
	this->bicicleta = NULL;

	cout << " euros.";
}

void Socio::devolveBicicleta(Ponto *p1){
	//deve de verificar se o ponto está cheio
	string hora;
	string verifica;

	if(p1->getBicicletas().size() > p1->getCapacidade()){
		cout << "O ponto está cheio!" << endl;
		//EXCEÇÃO PONTO CHEIO!!
	}

	//deve de verificar se o utente tem uma bicicleta para dar
	if(this->bicicleta == NULL){
		cout << "O cliente não tem uma bicicleta para devolver." << endl;
		//EXCEÇÃO NÃO TEM BICICLETA
	}

	//caso contrário, adiciona-se a bicicleta ao ponto e retira-se do cliente.

	p1->getBicicletas().push_back(bicicleta);
	//adciona-se ao ponto

	//retira-se ao cliente
	this->bicicleta = NULL;

	cout << "Bicicleta devolvida!" << endl;
	cout << endl;

	cout << "Qual a hora de devolução? ";
	cin >> hora;

	this->horafinal = Hora(hora);

	//calcular o tempo de uso
	subtraiHora(this->horafinal, this->horainicial);

	//envia o tempo dessa sessão de uso para o vetor para acumular.
	horasaccumuladas.push_back(tempouso);

	cout << "As horas do cliente foram acumuladas para o possível desconto. Deseja fazer checkout do final do mês? (S/N): ";
	cin >> verifica;

	if(verifica == "S"){
		cout << "O valor da mensalidade é: ";
		getPagamento();

		//reiniciar o vetor de acumulação
		for(unsigned int i = 0; i < horasaccumuladas.size(); i++){
			horasaccumuladas.erase(horasaccumuladas.begin()+i);
		}

		//saír
	}
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

void Utente::devolveBicicleta(Ponto *p1){}

string Utente::getNome(){
	return nome;
}


Hora Utente::getHoraFinal(){
	return this->horafinal;
}
