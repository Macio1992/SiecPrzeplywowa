#ifndef Siec_H
#define Siec_H

#include "Krawedz.h"
#include "Wierzcholek.h"
#include <vector>
#include <deque>

using namespace std;

class Siec
{
public:
	Siec();
	~Siec();
	void uzupelnijVector();
	bool sprawdzCzyWierzcholekIstnieje(Wierzcholek);
	void wypisz();
	int getIndeksWierzcholka(Wierzcholek w);
	bool sprawdzCzyjestUjscie();
	bool sprawdzCzyJestZrodlo();
	Wierzcholek getUjscie();
	Wierzcholek getZrodlo();
	void algorithm();
	Wierzcholek cechowanie(Wierzcholek);
	void przeplyw(Wierzcholek);
	void minimalnyPrzekroj();
	void wyczyscKrawedzie();
	bool sprawdzCzyMaGdzieIsc(Wierzcholek);

private:
	vector<Wierzcholek> wierzcholki;
	vector<Krawedz> krawedzie;
	char zrodlo;
	char ujscie;
	bool *visited;
};

#endif // !Siec_H
