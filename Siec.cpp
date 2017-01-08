#include "Siec.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

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

	visited = new bool[wierzcholki.size()];
	for (int i = 0; i < wierzcholki.size(); i++) visited[i] = false;

}

Siec::~Siec(){}

bool Siec::sprawdzCzyWierzcholekIstnieje(Wierzcholek w) {

	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(w.getName()));
	
	return (it != wierzcholki.end()) ? true : false;
	
}

int Siec::getIndeksWierzcholka(Wierzcholek w) {
	auto it = find(wierzcholki.begin(), wierzcholki.end(), Wierzcholek(w.getName()));
	
	return distance(wierzcholki.begin(), it);
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
		k.setWierzcholekWychodzacy(wierzcholki[getIndeksWierzcholka(a)]);
		k.setWierzcholekWchodzacy(wierzcholki[getIndeksWierzcholka(b)]);
		k.setMaksymalnaPrzepustowosc(c);

		krawedzie.push_back(k);
	}
		
}

void Siec::wypisz() {
	
	for (size_t i = 0; i < krawedzie.size(); i++) 
		cout << krawedzie[i].toString();
	cout << endl;
	
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
	
	return wierzcholki[found];
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

	return wierzcholki[found];
}

void wypiszBoole(bool *visited, int n) {
	for (int i = 0; i < n; i++)
		if (visited[i]) cout <<i<< ". Odwiedzony" << endl;
		else
			cout <<i<< ". Nieodwiedzony"<<endl;
	cout << endl;
}

void wypiszKolejke(deque<Wierzcholek> &queue) {
	if (!queue.empty()) {
		for (int i = 0; i < queue.size(); i++)
			cout << queue.at(i).getName() << " ";
		cout << endl;
	}
	else
		cout << "Kolejka pusta" << endl;
	
}

Wierzcholek Siec::cechowanie(Wierzcholek temp) {
	
	Wierzcholek pom;
	queue<Wierzcholek> queue;
	for (int i = 0; i < wierzcholki.size(); i++) visited[i] = false;

	queue.push(temp);

	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		visited[getIndeksWierzcholka(temp.getName())] = true;

		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() == temp.getName() && sprawdzCzyMaGdzieIsc(temp) && !visited[getIndeksWierzcholka(krawedzie[i].getWchodzacy())] && krawedzie[i].getAktualnaPrzepustowosc() != krawedzie[i].getMaksymalnaPrzepustowosc()) {
				queue.push(krawedzie[i].getWchodzacy());
				visited[getIndeksWierzcholka(krawedzie[i].getWchodzacy())] = true;
				pom = krawedzie[i].getWchodzacy();
				pom.setCecha(krawedzie[i].getWychodzacy().getName());
				pom.setZnakCechy('+');
				pom.setWartoscCechy(min(krawedzie[i].getWychodzacy().getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
				krawedzie[i].setWierzcholekWchodzacy(pom);
				for (int k = 0; k < krawedzie.size(); k++) {
					if (krawedzie[k].getWchodzacy().getName() == pom.getName())
						krawedzie[k].setWierzcholekWchodzacy(pom);
					if (krawedzie[k].getWychodzacy().getName() == pom.getName())
						krawedzie[k].setWierzcholekWychodzacy(pom);
				}
			}
			else if (!sprawdzCzyMaGdzieIsc(temp) && temp.getName() != getUjscie().getName()) {
				for (int k = 0; k < krawedzie.size(); k++) {
					if (krawedzie[k].getWchodzacy().getName() == temp.getName() && krawedzie[k].getWychodzacy().getZnakCechy() == ' ') {
						
						queue.push(krawedzie[k].getWychodzacy());
						pom = krawedzie[k].getWychodzacy();
						visited[getIndeksWierzcholka(krawedzie[i].getWychodzacy())] = true;
						pom.setCecha(krawedzie[k].getWchodzacy().getName());
						pom.setZnakCechy('-');
						pom.setWartoscCechy(min(krawedzie[k].getWchodzacy().getWartoscCechy(), krawedzie[k].getAktualnaPrzepustowosc()));
						krawedzie[k].setWierzcholekWychodzacy(pom);
						for (int j = 0; j < krawedzie.size(); j++) {
							if (krawedzie[j].getWchodzacy().getName() == pom.getName())
								krawedzie[j].setWierzcholekWchodzacy(pom);
							if (krawedzie[j].getWychodzacy().getName() == pom.getName())
								krawedzie[j].setWierzcholekWychodzacy(pom);
						}
					}
				}

			}
		}

	}
	
	return pom;
}

void Siec::przeplyw(Wierzcholek temp) {
	
	if (temp.getName() == getUjscie().getName()) {
		int przep = temp.getWartoscCechy();
		while (temp.getName() != getZrodlo().getName()) {
			if (temp.getZnakCechy() == '+') {
				for (int i = 0; i < krawedzie.size(); i++) {
					if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
						krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() + przep);
						temp = krawedzie[i].getWychodzacy();
						krawedzie[i].setWierzcholekWychodzacy(temp);
					}
				}
			}
			else if (temp.getZnakCechy() == '-') {
				for (int i = 0; i < krawedzie.size(); i++) {
					if (krawedzie[i].getWychodzacy().getName() == temp.getName() && krawedzie[i].getWchodzacy() == temp.getCecha()) {
						temp = krawedzie[i].getWchodzacy();
						krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() - przep);
						krawedzie[i].setWierzcholekWchodzacy(temp);
					}
				}
			}
		}
	}
}

void Siec::minimalnyPrzekroj() {
	cout << "Minimalny przekroj:" << endl;
	cout << "{"<<endl;
	
	int przeplyw = 0;

	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getZnakCechy() != ' ' && krawedzie[i].getAktualnaPrzepustowosc() == krawedzie[i].getMaksymalnaPrzepustowosc()) {
			cout << "   (" << krawedzie[i].getWychodzacy().getName() << "," << krawedzie[i].getWchodzacy().getName() << ")" << endl;
			przeplyw += krawedzie[i].getAktualnaPrzepustowosc();
		}

	cout << "}"<<endl;
	
	cout << "Wartosc maksymalnego przeplyw: "<<przeplyw << endl;
}

void Siec::wyczyscKrawedzie() {
	Wierzcholek temp;

	for (int i = 0; i < krawedzie.size(); i++) {
		if (krawedzie[i].getWychodzacy().getName() != getZrodlo().getName()) {
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
			temp = krawedzie[i].getWychodzacy();
			krawedzie[i].setWierzcholekWychodzacy(temp);
		}

	}

}

bool Siec::sprawdzCzyMaGdzieIsc(Wierzcholek temp) {
	int l = 0, l2 = 0;

	//sprawdz ile jest krawedzi z wierzcholkiem wychodzacym temp
	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getName() == temp.getName())
			l++;

	for (int i = 0; i < krawedzie.size(); i++)
		if (krawedzie[i].getWychodzacy().getName() == temp.getName() && krawedzie[i].getAktualnaPrzepustowosc() == krawedzie[i].getMaksymalnaPrzepustowosc()) 
			l2++;

	return (l == l2) ? false : true;
		
}

void Siec::algorithm() {

	if (sprawdzCzyjestUjscie() && sprawdzCzyJestZrodlo()) {

		Wierzcholek beg = getZrodlo();
		Wierzcholek temp;

		beg.setWartoscCechy(1000);

		do {
			temp = cechowanie(beg);
			przeplyw(temp);
			wypisz();
			if(visited[getIndeksWierzcholka(getUjscie())])
				wyczyscKrawedzie();
		} while (visited[getIndeksWierzcholka(getUjscie())]);
		
		minimalnyPrzekroj();
	}

	else {
		cout << "Niepoprawna siec.";
		if (!sprawdzCzyjestUjscie())
			cout << " Nie ma jednego ujscia." << endl;
		if (!sprawdzCzyJestZrodlo())
			cout << " Nie ma jednego zrodla." << endl;
		//if (!sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem())
			//cout << " Nie ma drogi ze zrodla do ujscia." << endl;
	}

}

