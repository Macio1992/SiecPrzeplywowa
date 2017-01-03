#include "Siec.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

Siec::Siec(){
	
	uzupelnijVector();


	for (int i = 0; i < krawedzie.size(); i++) {
		if (krawedzie[i].getWychodzacy().getName() == getZrodlo().getName()) {
			Wierzcholek temp = krawedzie[i].getWychodzacy();
			temp.setCecha(krawedzie[i].getWychodzacy().getName());
			temp.setZnakCechy('-');
			temp.setWartoscCechy(1000);
			krawedzie[i].setWierzcholekWychodzacy(temp);
		}
	}

}

Siec::~Siec(){}

bool Siec::sprawdzCzyWierzcholekIstnieje(Wierzcholek w) {

	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(w.getName()));
	
	return (it != wierzcholki.end()) ? true : false;
	
}

Wierzcholek Siec::getWierzcholek(char c) {

	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(c));

	return *it;
}

void Siec::uzupelnijVector() {
	
	ifstream file("data.txt");

	if (!file) {
		cout << "Blad podczas otwierania pliku"<<endl;
		exit(0);
	}

	char a, b;
	int c;

	while (file >> a >> b >> c) {

		Wierzcholek w(a);
		
		if (!sprawdzCzyWierzcholekIstnieje(w))
			wierzcholki.push_back(w);
		
		w.setName(b);

		if (!sprawdzCzyWierzcholekIstnieje(w))
			wierzcholki.push_back(w);

		Krawedz k;
		k.setWierzcholekWychodzacy(getWierzcholek(a));
		k.setWierzcholekWchodzacy(getWierzcholek(b));
		k.setMaksymalnaPrzepustowosc(c);

		krawedzie.push_back(k);
	}
		

}

void Siec::wypisz() {
	
	cout << "Krawedzie:" << endl;
	for (size_t i = 0; i < krawedzie.size(); i++) {
		cout << krawedzie[i].toString();
	}
	
}

bool Siec::sprawdzCzyjestUjscie() {

	int l = 0, l2 = 0;

	for (int i = 0; i < wierzcholki.size(); i++){
		l = 0;
		for (int j = 0; j < krawedzie.size(); j++)
			if (krawedzie[j].getWychodzacy().getName() == wierzcholki[i].getName())
				l++;
		if (l == 0) l2++;
	}

	return (l2 == 1) ? true : false;
	
}

bool Siec::sprawdzCzyJestZrodlo() {

	int l = 0, l2 = 0;

	for (int i = 0; i < wierzcholki.size(); i++) {
		l = 0;
		for (int j = 0; j < krawedzie.size(); j++)
			if (krawedzie[j].getWchodzacy().getName() == wierzcholki[i].getName())
				l++;
		if (l == 0) l2++;
	}

	return (l2 == 1) ? true : false;

}

Wierzcholek Siec::getUjscie() {
	
	int l = 0, found = 0;
	for (int i = 0; i < wierzcholki.size(); i++) {
		l = 0;
		for (int j = 0; j < krawedzie.size(); j++)
			if (wierzcholki[i].getName() != krawedzie[j].getWychodzacy().getName())
				l++;
		if (l == krawedzie.size()) found = i;
	}
		
	return getWierzcholek(wierzcholki[found].getName());
}

Wierzcholek Siec::getZrodlo() {
	int l = 0, found = 0;
	for (int i = 0; i < wierzcholki.size(); i++) {
		l = 0;
		for (int j = 0; j < krawedzie.size(); j++)
			if (wierzcholki[i].getName() != krawedzie[j].getWchodzacy().getName())
				l++;
		if (l == krawedzie.size()) found = i;
	}

	return getWierzcholek(wierzcholki[found].getName());
}

bool Siec::sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem() {

	
	char beg = getZrodlo().getName();
	char end = getUjscie().getName();

	char tmp;

	for (int i = 0; i < krawedzie.size(); i++) 
		if (krawedzie[i].getWychodzacy().getName() == beg)
			tmp = krawedzie[i].getWchodzacy().getName();
	
	int i = 0;
	while (tmp != end && i < krawedzie.size()) {
		
		for (int i = 0; i < krawedzie.size(); i++) {
			if(krawedzie[i].getWychodzacy().getName() == tmp)
				tmp = krawedzie[i].getWchodzacy().getName();
		}
		i++;
	}

	return (tmp == end) ? true : false;

}

void Siec::algorithm() {

	//dlaczego nie dziala set na wierzcholek
	if (sprawdzCzyjestUjscie() && sprawdzCzyJestZrodlo() && sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem()) {

		Wierzcholek beg = getZrodlo();
		Wierzcholek end = getUjscie();
		Wierzcholek temp;

		beg.setWartoscCechy(1000);
		
			for (int i = 0; i < krawedzie.size(); i++) {
				if (krawedzie[i].getWychodzacy().getName() == beg.getName() && krawedzie[i].getWchodzacy().getZnakCechy() == ' ') {
					temp = krawedzie[i].getWchodzacy();
					temp.setCecha(beg.getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(beg.getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
					krawedzie[i].setWierzcholekWchodzacy(temp);
				}
			}

			beg = temp;
			
			wypisz();
			cout << "temp: " << temp.toString() << endl;

		/*
		Wierzcholek beg = getZrodlo();
		Wierzcholek end = getUjscie();
		Wierzcholek temp;

		
		beg.setWartoscCechy(1000);

		int licznik = 0;
		
		while (beg.getName() != end.getName()) {
			licznik = 0;
			for (int i = 0; i < krawedzie.size(); i++) {
				if (krawedzie[i].getWychodzacy().getName() == beg.getName()) {
					//licznik++;
					temp = krawedzie[i].getWchodzacy();
					temp.setCecha(beg.getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(beg.getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
					krawedzie[i].setWierzcholekWchodzacy(temp);
				}
			}


			beg = temp;

			//oznaczenie wszystkich wierzcholkow gdzie jest wychodzacy lub wchodzacy temp
			for (int i = 0; i < krawedzie.size(); i++)
				if (krawedzie[i].getWchodzacy().getName() == temp.getName())
					krawedzie[i].setWierzcholekWchodzacy(temp);
				else if (krawedzie[i].getWychodzacy().getName() == temp.getName())
					krawedzie[i].setWierzcholekWychodzacy(temp);
		}
		wypisz();
		
		beg = getZrodlo();

		while (end.getName() != beg.getName()) {
			for (int i = 0; i < krawedzie.size(); i++) {
				if (krawedzie[i].getWchodzacy().getName() == end.getName() && krawedzie[i].getWychodzacy().getZnakCechy() != ' ') {
					temp = krawedzie[i].getWychodzacy();
					krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getWchodzacy().getWartoscCechy());
				}
			}
			end = temp;
		}

		wypisz();
		
		for (int i = 0; i < krawedzie.size(); i++) {

			if (krawedzie[i].getWychodzacy().getName() != getZrodlo().getName()) {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setWartoscCechy(0);
				temp.setZnakCechy(' ');
				krawedzie[i].setWierzcholekWchodzacy(temp);
				temp = krawedzie[i].getWychodzacy();
				temp.setCecha(' ');
				temp.setWartoscCechy(0);
				temp.setZnakCechy(' ');
				krawedzie[i].setWierzcholekWychodzacy(temp);
			}
			else {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setWartoscCechy(0);
				temp.setZnakCechy(' ');
				krawedzie[i].setWierzcholekWchodzacy(temp);
			}
			
			
		}
		
		
		wypisz();
		
		end = getUjscie();

		cout << "beg: " << beg.toString() << endl;
		cout << "end: " << end.toString() << endl;

		while (beg.getName() != end.getName()) {
			licznik = 0;
			for (int i = 0; i < krawedzie.size(); i++) {
				if (krawedzie[i].getWychodzacy().getName() == beg.getName() && licznik < 1) {
					licznik++;
					temp = krawedzie[i].getWchodzacy();
					temp.setCecha(beg.getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(beg.getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
					krawedzie[i].setWierzcholekWchodzacy(temp);
				}
			}


			beg = temp;

			//oznaczenie wszystkich wierzcholkow gdzie jest wychodzacy lub wchodzacy temp
			for (int i = 0; i < krawedzie.size(); i++)
				if (krawedzie[i].getWchodzacy().getName() == temp.getName())
					krawedzie[i].setWierzcholekWchodzacy(temp);
				else if (krawedzie[i].getWychodzacy().getName() == temp.getName())
					krawedzie[i].setWierzcholekWychodzacy(temp);
		}*/

	}
	else {
		cout << "Niepoprawna siec.";
		if (!sprawdzCzyjestUjscie())
			cout << " Nie ma jednego ujscia." << endl;
		if (!sprawdzCzyJestZrodlo())
			cout << " Nie ma jednego zrodla." << endl;
		if (!sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem())
			cout << " Nie ma drogi ze zrodla do ujscia." << endl;
	}

}