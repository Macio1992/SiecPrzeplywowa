#include "Wierzcholek.h"
#include <iostream>
#include <sstream>

using namespace std;

Wierzcholek::Wierzcholek(char n) {
	name = n;
	cecha = ' ';
	znak_cechy = ' ';
	wartosc_cechy = 0;
	czyJestNaSciezce = false;
}

Wierzcholek::Wierzcholek() {}

Wierzcholek::~Wierzcholek() {}

char Wierzcholek::getName() {
	return name;
}

void Wierzcholek::setName(char c) {
	name = c;
}

char Wierzcholek::getZnakCechy() {
	return this->znak_cechy;
}

void Wierzcholek::setZnakCechy(char z){
	this->znak_cechy = z;
}

char Wierzcholek::getCecha() {
	return cecha;
}

void Wierzcholek::setCecha(char c) {
	cecha = c;
}

int Wierzcholek::getWartoscCechy() {
	return wartosc_cechy;
}

void Wierzcholek::setWartoscCechy(int w) {
	wartosc_cechy = w;
}

bool Wierzcholek::operator==(Wierzcholek obj2) {
	return (name == obj2.name);
}

string Wierzcholek::toString() {
	stringstream stm;
	string s;

	if (czyJestNaSciezce) s = "S->>";

	stm << name << "(" << cecha << znak_cechy << "," << wartosc_cechy<<")"<<s;
	return stm.str();
}


bool Wierzcholek::getCzyJestNaSciezce() {
	return czyJestNaSciezce;
}

void Wierzcholek::setCzyJestNaSciezce(bool c) {
	czyJestNaSciezce = c;
}