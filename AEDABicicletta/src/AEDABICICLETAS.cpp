//============================================================================
// Name        : AEDABICICLETAS.cpp
// Author      : 2MIEIC02 -> GRUPO 4
// Version     : 1
// Description : This is the main function, includes menu and others ..
//============================================================================

#include <iostream>
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Bicicleta.h"
#include "Cidade.h"
#include "Coordenadas.h"
#include "Ponto.h"
#include "Utente.h"
#include "Hora.h"
using namespace std;

void testAddAndRmBicicletas()
{
	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	ASSERT_EQUAL(0,p1.getnumbicicletasDisponiveis() );
	ASSERT_EQUAL(4, p1.getCapacidade());

	Bicicleta* b = new Bicicleta(1);
	p1.addBicicleta(b);
	b = new Bicicleta(2);
	p1.addBicicleta(b);
	b = new Bicicleta(3);
	p1.addBicicleta(b);

	ASSERT_EQUAL(3,p1.getnumbicicletasDisponiveis() );
	b = new Bicicleta(3);

	ASSERT_THROWS(p1.addBicicleta(b), Bicicleta_Existente);
	try
	{
		p1.addBicicleta(b);
	}
	catch(Bicicleta_Existente &e)
	{
		ASSERT_EQUAL(3, e.id);
		//cout << e.id << endl;
	}

	b = new Bicicleta(4);
	ASSERT_EQUAL(3,p1.getnumbicicletasDisponiveis() );

	p1.addBicicleta(b);

	ASSERT_EQUAL(4,p1.getnumbicicletasDisponiveis() );

	b = new Bicicleta(5);
	ASSERT_THROWS(p1.addBicicleta(b), NoSpace);

	ASSERT_THROWS(p1.rmBicicleta(5), Bicicleta_Inexistente);
	try
	{
		p1.rmBicicleta(5);
	}
	catch(Bicicleta_Inexistente &e)
	{
		ASSERT_EQUAL(e.id, 5);
		//cout << e.id << endl;
	}

	p1.rmBicicleta(1);

	ASSERT_EQUAL(3,p1.getnumbicicletasDisponiveis() );
}

void testSortByDistance()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(3,0)));
	c1.sortPointsByDistance(Coordenadas(4,0));
	ASSERT_EQUAL(c1.getPontos().size(), 4);

	ASSERT_EQUAL(Coordenadas(3,0), c1.getPontos().at(0).getCoord());
	ASSERT_EQUAL(Coordenadas(2,0), c1.getPontos().at(1).getCoord());
	ASSERT_EQUAL(Coordenadas(1,0), c1.getPontos().at(2).getCoord());
	ASSERT_EQUAL(Coordenadas(0,0), c1.getPontos().at(3).getCoord());

	ASSERT_EQUAL(1,c1.getPontos().at(0).getDistance());
	ASSERT_EQUAL(2,c1.getPontos().at(1).getDistance());
	ASSERT_EQUAL(3,c1.getPontos().at(2).getDistance());
	ASSERT_EQUAL(4,c1.getPontos().at(3).getDistance());

}

void testHoraSub()
{
	ASSERT_EQUAL(0.5, Hora(1,30) - Hora(1,0));
}

void testIsThereBicycle()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(3,0)));

	ASSERT_EQUAL(c1.getPontos().end(), c1.isThereBicycle("Corrida"));

	Corrida* bike = new Corrida(1);
	c1.getPontos().at(1).addBicicleta(bike);

	ASSERT_EQUAL(c1.getPontos().begin() + 1, c1.isThereBicycle("Corrida"));

	ASSERT_THROWS(c1.isThereBicycle("ABC"),NotAType);
}

void testClosestType()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 2", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 4, Coordenadas(3,0)));

	Corrida* bike = new Corrida(1);
	c1.getPontos().at(1).addBicicleta(bike);
	c1.getPontos().at(2).addBicicleta(bike);

	ASSERT_EQUAL(c1.closestType(Coordenadas(4,0), "Corrida")->getNome(), "Ponto 3");
}

void runSuite()
{
	cute::suite s;
	s.push_back(CUTE(testAddAndRmBicicletas));
	s.push_back(CUTE(testSortByDistance));
	s.push_back(CUTE(testHoraSub));
	s.push_back(CUTE(testIsThereBicycle));
	s.push_back(CUTE(testClosestType));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA Projeto Parte 1");
}


int main() {
	runSuite();
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
