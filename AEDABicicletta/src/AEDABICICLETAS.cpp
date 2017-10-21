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
	Utente *a1 = new Regular("Jo�o",&c1,1,-4);
	Utente *b1 = new Socio("Rui",&c1,10,-2);
	Utente *c1 = new Regular("Louren�o",&c1,13,-7);
	(...)

	c1.addUtente(a1);
	c1.addUtente(b1);
	(...) e o mesmo para os pontos e bicicletas!

	menu Utente:
	==================================================================
	string nomeutente;
	Utente *u1; <- este � o utente que est� a ser tratado de momento.

	u1 = NULL <- inicializado com nada;

	cout << "qual o nome do utente?"
	cin >> nomeutente;

	for(unsigned int i = 0; i < c1.utentes.size(); i++){
		if(c1.utentes.at(i)->getNome() == nomeutente){
			u1 = c1.utentes.at(i);
		}
	}

	if(*u1 == NULL){
	se ainda n�o tem nada depois do for, n�o foi encontrado, n�o existe! EXE��O UTENE N�O EXISTENTE
	}

	se foi encontrado continua sem problemas ...

	||OP��ES||:

	- levanta bicicleta.
	- devolve bicicleta (pagamento imediato no caso de ser regular, accumula��o/checkout no caso de s�cio).
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

	se esse ciclo for n�o d�, � necess�rio implementar EXCE��O PONTO INEXISTENTE.
	==================================================================

	se devolve:
	==================================================================
	string nomepontodev;
	cout << "qual o nome do ponto de devolu��o?"
	cin >> nomepontodev;

	for(unsigned int i = 0; i < c1.pontos.size(); i++){
		if(c1.pontos.at(i)->getNome() == nomepontodev){
			u1.devolveBicicleta(c1.pontos.at(i)); <- passa o apontador
		}
	}

	se esse ciclo for n�o d�, � necess�rio implementar EXCE��O PONTO INEXISTENTE.
	==================================================================
	*/

	return 0;
}
