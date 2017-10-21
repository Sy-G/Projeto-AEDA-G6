//============================================================================
// Name        : AEDABICICLETAS.cpp
// Author      : 2MIEIC02 -> GRUPO 4
// Version     : 1
// Description : This is the main function, includes menu and others ..
//============================================================================

#include <iostream>
#include "Bicicleta.h"
#include "Cidade.h"
#include "Coordenadas.h"
#include "Ponto.h"
#include "Utente.h"
#include "Hora.h"
using namespace std;

int main() {
	/*Cidade c1;
	Utente *a1 = new Regular("João",&c1,1,-4);
	Utente *b1 = new Socio("Rui",&c1,10,-2);
	Utente *c1 = new Regular("Lourenço",&c1,13,-7);
	(...)

	c1.addUtente(a1);
	c1.addUtente(b1);
	(...) e o mesmo para os pontos e bicicletas!

	menu Utente:
	==================================================================
	string nomeutente;
	Utente *u1; <- este é o utente que está a ser tratado de momento.

	u1 = NULL <- inicializado com nada;

	cout << "qual o nome do utente?"
	cin >> nomeutente;

	for(unsigned int i = 0; i < c1.utentes.size(); i++){
		if(c1.utentes.at(i)->getNome() == nomeutente){
			u1 = c1.utentes.at(i);
		}
	}

	if(*u1 == NULL){
	se ainda não tem nada depois do for, não foi encontrado, não existe! EXEÇÃO UTENE NÃO EXISTENTE
	}

	se foi encontrado continua sem problemas ...

	||OPÇÕES||:

	- levanta bicicleta.
	- devolve bicicleta (pagamento imediato no caso de ser regular, accumulação/checkout no caso de sócio).
	==================================================================

	se levanta:
	==================================================================
	string nomeponto;
	cout << "qual o nome do ponto de levantamento?"
	cin >> nomeponto;

	for(unsigned int i = 0; i < c1.pontos.size(); i++){
		if(c1.pontos.at(i)->getNome() == nomeponto){
			u1.levantaBicicleta(c1.pontos.at(i)); <- passa o apontador
		}
	}

	se esse ciclo for não dá, é necessário implementar EXCEÇÃO PONTO INEXISTENTE.
	==================================================================

	se devolve:
	==================================================================
	string nomepontodev;
	cout << "qual o nome do ponto de devolução?"
	cin >> nomepontodev;

	for(unsigned int i = 0; i < c1.pontos.size(); i++){
		if(c1.pontos.at(i)->getNome() == nomepontodev){
			u1.devolveBicicleta(c1.pontos.at(i)); <- passa o apontador
		}
	}

	se esse ciclo for não dá, é necessário implementar EXCEÇÃO PONTO INEXISTENTE.
	==================================================================
	*/

	return 0;
}
