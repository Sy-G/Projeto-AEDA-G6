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
	bike = new Corrida(2);
	c1.getPontos().at(2).addBicicleta(bike);

	ASSERT_EQUAL(c1.closestType(Coordenadas(4,0), "Corrida")->getNome(), "Ponto 3");
}

void testIsThereSpace()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 1, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 1", 0, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 1", 1, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 1", 0, Coordenadas(3,0)));

	ASSERT_EQUAL(c1.getPontos().begin(), c1.isThereSpace());
	Corrida* bike = new Corrida(0);
	c1.getPontos().at(0).addBicicleta(bike);

	ASSERT_EQUAL(c1.getPontos().begin() + 2, c1.isThereSpace());
	bike = new Corrida(2);
	c1.getPontos().at(2).addBicicleta(bike);

	ASSERT_THROWS(c1.isThereSpace(), NoSpace);
}

void testClosestSpace()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 1, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 2", 0, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 1, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 0, Coordenadas(3,0)));

	ASSERT_EQUAL("Ponto 3", c1.closestSpace(Coordenadas(4,0))->getNome());
	Corrida* bike = new Corrida(0);
	c1.getPontos().at(1).addBicicleta(bike);

	ASSERT_EQUAL("Ponto 1", c1.closestSpace(Coordenadas(4,0))->getNome());
	bike = new Corrida(2);
	c1.getPontos().at(3).addBicicleta(bike);

	ASSERT_THROWS(c1.closestSpace(Coordenadas(4,0)), NoSpace);
}

void testlevantaBicicleta()
{
	Cidade c1;
	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	Ponto p2("Ponto 2", 5, Coordenadas(0,1));
	Utente *j1 = new Regulares("Jo�o",2,1,-4);
	Utente *r1 = new Socio("Rui",3,10,-2);
	Utente *l1 = new Regulares("Louren�o",4,13,-7);
	Bicicleta* b = new Infantil(1);
	Bicicleta* a = new Corrida(1);
	Bicicleta* c = new Urbana(1);

	c1.addUtente(j1);
	c1.addUtente(r1);
	c1.addUtente(l1);
	c1.addPoint(p1);
	c1.addPoint(p2);
	p1.addBicicleta(b);
	p1.addBicicleta(a);
	p2.addBicicleta(c);

	ASSERT_EQUAL(2, p1.getnumbicicletasDisponiveis());
	j1->levantaBicicleta(&p1); //asert throws n�o existe bicicleta
	//Vamos dizer que ele quer especificamente uma Corrida.
	ASSERT_EQUAL("Corrida", j1->getBicicleta()->getTipo());
	//Vamos dizer que ele entra �s 8:44
	ASSERT_EQUAL(8, j1->getHoraInicial().hora);
	ASSERT_EQUAL(44, j1->getHoraInicial().minutos);

	r1->levantaBicicleta(&p2); //asert throws n�o existe bicicleta
	//Vamos dizer que ele quer especificamente uma Urbana.
	ASSERT_EQUAL("Corrida", r1->getBicicleta()->getTipo());
	//Vamos dizer que ele entra �s 18:34
	ASSERT_EQUAL(18, r1->getHoraInicial().hora);
	ASSERT_EQUAL(34, r1->getHoraInicial().minutos);
}

void testdevolveBicicletaRegulares()
{
	Cidade c1;
	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	Ponto p2("Ponto 2", 5, Coordenadas(0,1));
	Utente *j1 = new Regulares("Jo�o",2,1,-4);
	Utente *l1 = new Regulares("Louren�o",4,13,-7);

	Bicicleta* b = new Infantil(1);
	Bicicleta* a = new Corrida(1);
	Bicicleta* c = new Urbana(1);

	c1.addUtente(j1);
	c1.addUtente(l1);
	c1.addUtente(l1);
	c1.addPoint(p1);
	c1.addPoint(p2);
	p1.addBicicleta(b);
	p1.addBicicleta(a);
	p2.addBicicleta(c); //no elemento 0 do vetor de bicicletas do ponto est� uma urbana.

	//o joao vai levantar especificamente uma bicicleta de corrida �s 11:30, que � o elemento 1 do vetor de bicicletas do ponto p1.
	j1->levantaBicicleta(&p1);

	//agora ele vai devolv�-la noutro s�tio
	j1->devolveBicicleta(&p2);

	//j� n�o deve de ter bicicleta.
	ASSERT_EQUAL(NULL, j1->getBicicleta());

	//se devolveu corretamente, o segundo elemento (indice i) do ponto p2 das bicicletas devia de ser a bicicleta de corrida que ele devolve.
	ASSERT_EQUAL("Corrida", p2.getBicicletas().at(1)->getTipo());

	//vamos dizer que ele devolveu �s 13:00
	ASSERT_EQUAL(13, j1->getHoraFinal().hora);
	ASSERT_EQUAL(00, j1->getHoraFinal().minutos);

	//usou uma hora e meia uma bicicleta corrida cujo pre�o por hora � 0.80, logo pagamento = 1.5*0.80 = 1.2
	ASSERT_EQUAL(1.2, j1->getPagamento());
}

void runSuite()
{
	cute::suite s;
	s.push_back(CUTE(testAddAndRmBicicletas));
	s.push_back(CUTE(testSortByDistance));
	s.push_back(CUTE(testHoraSub));
	s.push_back(CUTE(testIsThereBicycle));
	s.push_back(CUTE(testClosestType));
	s.push_back(CUTE(testIsThereSpace));
	s.push_back(CUTE(testClosestSpace));
	s.push_back(CUTE(testlevantaBicicleta));
	s.push_back(CUTE(testdevolveBicicletaRegulares));
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

	PONTO INEXISTENTE.
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

	EXE��O DE PONTO INEXISTENTE.
	==================================================================
	 */

	return 0;
}
