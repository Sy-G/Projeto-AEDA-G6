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
/*
void testAddAndRmBicicletas()
{
	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	ASSERT_EQUAL(0,p1.getnumbicicletasDisponiveis() );
	ASSERT_EQUAL(4, p1.getCapacidade());

	Bicicleta* b = new Bicicleta;
	p1.addBicicleta(b);
	b = new Bicicleta;
	p1.addBicicleta(b);
	b = new Bicicleta;
	p1.addBicicleta(b);

	ASSERT_EQUAL(3,p1.getnumbicicletasDisponiveis() );

	b = new Bicicleta;
	ASSERT_EQUAL(3,p1.getnumbicicletasDisponiveis() );

	p1.addBicicleta(b);

	ASSERT_EQUAL(4,p1.getnumbicicletasDisponiveis() );

	b = new Bicicleta;
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
	c1.addPoint(Ponto("Ponto 2", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 4, Coordenadas(3,0)));
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
	c1.addPoint(Ponto("Ponto 2", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 4, Coordenadas(3,0)));

	ASSERT_EQUAL(c1.getPontos().end(), c1.isThereBicycle("Corrida"));

	Corrida* bike = new Corrida;
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

	Corrida* bike = new Corrida;
	c1.getPontos().at(1).addBicicleta(bike);
	bike = new Corrida;
	c1.getPontos().at(2).addBicicleta(bike);

	ASSERT_EQUAL(c1.closestType(Coordenadas(4,0), "Corrida")->getNome(), "Ponto 3");
}

void testIsThereSpace()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 1, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 2", 0, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 1, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 0, Coordenadas(3,0)));

	ASSERT_EQUAL(c1.getPontos().begin(), c1.isThereSpace());
	Corrida* bike = new Corrida;
	c1.getPontos().at(0).addBicicleta(bike);

	ASSERT_EQUAL(c1.getPontos().begin() + 2, c1.isThereSpace());
	bike = new Corrida;
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
	Corrida* bike = new Corrida;
	c1.getPontos().at(1).addBicicleta(bike);

	ASSERT_EQUAL("Ponto 1", c1.closestSpace(Coordenadas(4,0))->getNome());
	bike = new Corrida;
	c1.getPontos().at(3).addBicicleta(bike);

	ASSERT_THROWS(c1.closestSpace(Coordenadas(4,0)), NoSpace);
}

void testlevantaBicicleta()
{
	//	Cidade c1;
	//	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	//	Ponto p2("Ponto 2", 5, Coordenadas(0,1));
	//	Utente *j1 = new Regulares("João",2,1,-4);
	//	Utente *r1 = new Socio("Rui",3,10,-2);
	//	Utente *l1 = new Regulares("Lourenço",4,13,-7);
	//	Bicicleta* b = new Infantil;
	//	Bicicleta* a = new Corrida;
	//	Bicicleta* c = new Urbana;
	//
	//	c1.addUtente(j1);
	//	c1.addUtente(r1);
	//	c1.addUtente(l1);
	//	c1.addPoint(p1);
	//	c1.addPoint(p2);
	//	p1.addBicicleta(b);
	//	p1.addBicicleta(a);
	//	p2.addBicicleta(c);
	//
	//	ASSERT_EQUAL(2, p1.getnumbicicletasDisponiveis());
	//	j1->levantaBicicleta(&p1); //asert throws não existe bicicleta
	//	//Vamos dizer que ele quer especificamente uma Corrida.
	//	ASSERT_EQUAL("Corrida", j1->getBicicleta()->getTipo());
	//	//Vamos dizer que ele entra às 8:44
	//	ASSERT_EQUAL(8, j1->getHoraInicial().hora);
	//	ASSERT_EQUAL(44, j1->getHoraInicial().minutos);
	//
	//	r1->levantaBicicleta(&p2); //asert throws não existe bicicleta
	//	//Vamos dizer que ele quer especificamente uma Urbana.
	//	ASSERT_EQUAL("Corrida", r1->getBicicleta()->getTipo());
	//	//Vamos dizer que ele entra às 18:34
	//	ASSERT_EQUAL(18, r1->getHoraInicial().hora);
	//	ASSERT_EQUAL(34, r1->getHoraInicial().minutos);
}

void testdevolveBicicletaRegulares()
{
	//	Cidade c1;
	//	Ponto p1("Ponto 1", 4, Coordenadas(0,0));
	//	Ponto p2("Ponto 2", 5, Coordenadas(0,1));
	//	Utente *j1 = new Regulares("João",2,1,-4);
	//	Utente *l1 = new Regulares("Lourenço",4,13,-7);
	//
	//	Bicicleta* b = new Infantil;
	//	Bicicleta* a = new Corrida;
	//	Bicicleta* c = new Urbana;
	//
	//	c1.addUtente(j1);
	//	c1.addUtente(l1);
	//	c1.addUtente(l1);
	//	c1.addPoint(p1);
	//	c1.addPoint(p2);
	//	p1.addBicicleta(b);
	//	p1.addBicicleta(a);
	//	p2.addBicicleta(c); //no elemento 0 do vetor de bicicletas do ponto está uma urbana.
	//
	//	//o joao vai levantar especificamente uma bicicleta de corrida às 11:30, que é o elemento 1 do vetor de bicicletas do ponto p1.
	//	j1->levantaBicicleta(&p1);
	//
	//	//agora ele vai devolvê-la noutro sítio
	//	j1->devolveBicicleta(&p2);
	//
	//	//já não deve de ter bicicleta.
	//	//ASSERT_EQUAL(NULL, j1->getBicicleta());
	//
	//	//se devolveu corretamente, o segundo elemento (indice i) do ponto p2 das bicicletas devia de ser a bicicleta de corrida que ele devolve.
	//	ASSERT_EQUAL("Corrida", p2.getBicicletas().at(1)->getTipo());
	//
	//	//vamos dizer que ele devolveu às 13:00
	//	ASSERT_EQUAL(13, j1->getHoraFinal().hora);
	//	ASSERT_EQUAL(00, j1->getHoraFinal().minutos);
	//
	//	//usou uma hora e meia uma bicicleta corrida cujo preço por hora é 0.80, logo pagamento = 1.5*0.80 = 1.2
	//	ASSERT_EQUAL(1.2, j1->getPagamento());
}

void testRedistribution()
{
	Cidade c1;
	c1.addPoint(Ponto("Ponto 1", 4, Coordenadas(0,0)));
	c1.addPoint(Ponto("Ponto 2", 4, Coordenadas(1,0)));
	c1.addPoint(Ponto("Ponto 3", 4, Coordenadas(2,0)));
	c1.addPoint(Ponto("Ponto 4", 4, Coordenadas(3,0)));

	for(size_t i = 0; i < 4; i++)
		c1.getPontos().at(1).addBicicleta(new Corrida);
	for(size_t i = 0; i < 3; i++)
		c1.getPontos().at(0).addBicicleta(new Infantil);

	for(size_t i = 0; i < 3; i++)
		c1.getPontos().at(2).addBicicleta(new Infantil);

	c1.testOccupation();

	for(size_t i = 0; i < c1.getPontos().size(); i++)
	{
		cout << c1.getPontos().at(i).getBicicletas().size() << endl;
	}
	ASSERT_THROWS(c1.testOccupation(),NoRedistributionNeeded);
}

void testPrintPoints()
{
	Ponto p1("Ponto 1", 4, Coordenadas(3,5));
	p1.addBicicleta(new Corrida);
	p1.addBicicleta(new Infantil);
	p1.addBicicleta(new Urbana);
	p1.addBicicleta(new Urbana_Simples);

	cout << p1 << endl;
}

void testCreatePoint()
{
	try
	{
		cout << Ponto("Trindade 1","20 5-6 C C C U S S I I") << endl;
	}
	catch(...)
	{
		cout << "caught\n";
	}

	try
	{
		cout << Ponto("Trindade 1","20 5-6") << endl;
	}
	catch(...)
	{
		cout << "caught\n";
	}


	ASSERT_THROWS(Ponto("Trindade 1","20 5 6 C C C U S S I I"), InvalidPoint);

	ASSERT_THROWS(Ponto("Trindade 1","20 5-6 C C C A S S I I"), InvalidPoint);

	ASSERT_THROWS(Ponto("Trindade 1","20"), InvalidPoint);

}

void testReadWritePointsToFile()
{
	Cidade c1;
	c1.readPoints("points1.txt");
	cout << "READ DONE\n";
	c1.printPointsFile("points2.txt");
}*/

void testReadUsersFromFileAndPrintThem()
{
	Cidade c1;
	c1.readUsers("utentes1.txt");
	cout << "READ DONE\n";
	c1.printUserstoFile("utentes2.txt");
}

void testPrintUsers()
{
	Cidade c1;
	Utente *j1 = new Regulares("João",2,1);
	Utente *r1 = new Socio("Rui",3,10);
	Utente *l1 = new Regulares("Lourenço",4,13);
	c1.addUtente(j1);
	c1.addUtente(r1);
	c1.addUtente(l1);

	c1.printUsers();
}


void runSuite()
{
	cute::suite s;
	s.push_back(CUTE(testReadUsersFromFileAndPrintThem));
	s.push_back(CUTE(testPrintUsers));
	cute::ide_listener<> lis;
	cute::makeRunner(lis)(s, "AEDA Projeto Parte 1");
}


int main() {
	runSuite();
	/*Cidade c1;
	Utente *a1 = new Regular("Joï¿½o",&c1,1,-4);
	Utente *b1 = new Socio("Rui",&c1,10,-2);
	Utente *c1 = new Regular("Lourenï¿½o",&c1,13,-7);
	(...)

	c1.addUtente(a1);
	c1.addUtente(b1);
	(...) e o mesmo para os pontos e bicicletas!

	menu Utente:
	==================================================================
	string nomeutente;
	Utente *u1; <- este ï¿½ o utente que estï¿½ a ser tratado de momento.

	u1 = NULL <- inicializado com nada;

	cout << "qual o nome do utente?"
	cin >> nomeutente;

	for(unsigned int i = 0; i < c1.utentes.size(); i++){
		if(c1.utentes.at(i)->getNome() == nomeutente){
			u1 = c1.utentes.at(i);
		}
	}

	if(*u1 == NULL){
	se ainda nï¿½o tem nada depois do for, nï¿½o foi encontrado, nï¿½o existe! EXEï¿½ï¿½O UTENE Nï¿½O EXISTENTE
	}

	se foi encontrado continua sem problemas ...

	- levanta bicicleta.
	- devolve bicicleta (pagamento imediato no caso de ser regular, accumulaï¿½ï¿½o/checkout no caso de sï¿½cio).
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
	cout << "qual o nome do ponto de devolução?"
	cin >> nomepontodev;

	for(unsigned int i = 0; i < c1.pontos.size(); i++){
		if(c1.pontos.at(i)->getNome() == nomepontodev){
			u1.devolveBicicleta(c1.pontos.at(i)); <- passa o apontador
		}
	}

	EXEÇÃO DE PONTO INEXISTENTE.
	==================================================================
	 */

	return 0;
}
