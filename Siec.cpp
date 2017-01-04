#include "Siec.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>

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

		deque<Wierzcholek> queue;

		beg.setWartoscCechy(1000);
		queue.push_back(beg);
		
		int i = 0;
		while (temp.getName() != end.getName()) {
			for (int j = 0; j < krawedzie.size(); j++) {
				if (krawedzie[j].getWychodzacy().getName() == queue.at(i).getName() && krawedzie[j].getWchodzacy().getZnakCechy() == ' '&& krawedzie[j].getMaksymalnaPrzepustowosc() != krawedzie[j].getAktualnaPrzepustowosc()) {
					temp = krawedzie[j].getWchodzacy();
					queue.push_back(temp);
					temp.setCecha(queue.at(i).getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(krawedzie[j].getWychodzacy().getWartoscCechy(), (krawedzie[j].getMaksymalnaPrzepustowosc() - krawedzie[j].getAktualnaPrzepustowosc())));
					krawedzie[j].setWierzcholekWchodzacy(temp);
					for (int k = 0; k < krawedzie.size(); k++) {
						if (krawedzie[k].getWychodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWychodzacy(temp);
						if (krawedzie[k].getWchodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWchodzacy(temp);
					}

				}
			}
			i++;
		}

		int przep = temp.getWartoscCechy();
		while (temp.getName() != beg.getName()) {
			for (int i = 0; i < krawedzie.size(); i++)
				if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
					krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() + przep);
					temp = krawedzie[i].getWychodzacy();
				}
		}
		
		cout << "Pierwsza iteracja: " << endl;
		wypisz();
		cout << endl;

		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() != beg.getName()) {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
				temp = krawedzie[i].getWychodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWychodzacy(temp);
			}
			else {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
			}
			
		}

		queue.clear();

		//////////////////////// druga runda

		queue.push_back(beg);
		
		i = 0;
		while (temp.getName() != end.getName()) {
			for (int j = 0; j < krawedzie.size(); j++) {
				if (krawedzie[j].getWychodzacy().getName() == queue.at(i).getName() && krawedzie[j].getWchodzacy().getZnakCechy() == ' '&& krawedzie[j].getMaksymalnaPrzepustowosc() != krawedzie[j].getAktualnaPrzepustowosc()) {
					temp = krawedzie[j].getWchodzacy();
					queue.push_back(temp);
					temp.setCecha(queue.at(i).getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(krawedzie[j].getWychodzacy().getWartoscCechy(), (krawedzie[j].getMaksymalnaPrzepustowosc() - krawedzie[j].getAktualnaPrzepustowosc())));
					krawedzie[j].setWierzcholekWchodzacy(temp);
					for (int k = 0; k < krawedzie.size(); k++) {
						if (krawedzie[k].getWychodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWychodzacy(temp);
						if (krawedzie[k].getWchodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWchodzacy(temp);
					}

				}
			}
			i++;
		}

		przep = temp.getWartoscCechy();
		while (temp.getName() != beg.getName()) {
			for (int i = 0; i < krawedzie.size(); i++)
				if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
					krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc()+przep);
					temp = krawedzie[i].getWychodzacy();
				}
		}

		cout << "Druga iteracja: " << endl;
		wypisz();
		cout << endl;

		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() != beg.getName()) {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
				temp = krawedzie[i].getWychodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWychodzacy(temp);
			}
			else {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
			}

		}

		queue.clear();

		//////////////////////// trzecia runda
		queue.push_back(beg);
		
		i = 0;
		while (temp.getName() != end.getName()) {
			for (int j = 0; j < krawedzie.size(); j++) {
				if (krawedzie[j].getWychodzacy().getName() == queue.at(i).getName() && krawedzie[j].getWchodzacy().getZnakCechy() == ' '&& krawedzie[j].getMaksymalnaPrzepustowosc() != krawedzie[j].getAktualnaPrzepustowosc()) {
					temp = krawedzie[j].getWchodzacy();
					queue.push_back(temp);
					temp.setCecha(queue.at(i).getName());
					temp.setZnakCechy('+');
					temp.setWartoscCechy(min(krawedzie[j].getWychodzacy().getWartoscCechy(), (krawedzie[j].getMaksymalnaPrzepustowosc() - krawedzie[j].getAktualnaPrzepustowosc())));
					krawedzie[j].setWierzcholekWchodzacy(temp);
					for (int k = 0; k < krawedzie.size(); k++) {
						if (krawedzie[k].getWychodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWychodzacy(temp);
						if (krawedzie[k].getWchodzacy().getName() == temp.getName())
							krawedzie[k].setWierzcholekWchodzacy(temp);
					}

				}
			}
			i++;
		}

		przep = temp.getWartoscCechy();
		while (temp.getName() != beg.getName()) {
			for (int i = 0; i < krawedzie.size(); i++)
				if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
					krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() + przep);
					temp = krawedzie[i].getWychodzacy();
				}
		}

		cout << "Trzecia iteracja: " << endl;
		wypisz();
		cout << endl;

		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() != beg.getName()) {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
				temp = krawedzie[i].getWychodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWychodzacy(temp);
			}
			else {
				temp = krawedzie[i].getWchodzacy();
				temp.setCecha(' ');
				temp.setZnakCechy(' ');
				temp.setWartoscCechy(0);
				krawedzie[i].setWierzcholekWchodzacy(temp);
			}

		}

		queue.clear();

		wypisz();
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