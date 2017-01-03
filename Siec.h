#ifndef Siec_H
#define Siec_H

#include "Krawedz.h"
#include "Wierzcholek.h"
#include <vector>

using namespace std;

class Siec
{
public:
	Siec();
	~Siec();
	void uzupelnijVector();
	bool sprawdzCzyWierzcholekIstnieje(Wierzcholek);
	void wypisz();
	Wierzcholek getWierzcholek(char);
	bool sprawdzCzyjestUjscie();
	bool sprawdzCzyJestZrodlo();
	Wierzcholek getUjscie();
	Wierzcholek getZrodlo();
	bool sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem();
	void algorithm();

private:
	vector<Wierzcholek> wierzcholki;
	vector<Krawedz> krawedzie;
	char zrodlo;
	char ujscie;
};

#endif // !Siec_H
