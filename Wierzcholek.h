#ifndef Wierzcholek_H
#define Wierzcholek_H

#include <iostream>

using namespace std;

class Wierzcholek
{
public:
	Wierzcholek(char);
	Wierzcholek();
	~Wierzcholek();
	char getName();
	void setName(char);
	char getZnakCechy();
	void setZnakCechy(char);
	char getCecha();
	void setCecha(char);
	int getWartoscCechy();
	void setWartoscCechy(int);
	string toString();
	bool operator==(Wierzcholek);
	void setCzyJestNaSciezce(bool);
	bool getCzyJestNaSciezce();

private:
	char name;
	char cecha;
	char znak_cechy;
	int wartosc_cechy;
	bool czyJestNaSciezce;
};

#endif // !Wierzcholek_H