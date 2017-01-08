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
			if(krawedzie[i].getWychodzacy().getName() == tmp && krawedzie[i].getAktualnaPrzepustowosc() != krawedzie[i].getMaksymalnaPrzepustowosc())
				tmp = krawedzie[i].getWchodzacy().getName();
		}
		i++;
	}

	return (tmp == end) ? true : false;

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

Wierzcholek Siec::cechowanie(deque<Wierzcholek> &queue, Wierzcholek temp) {
	
	//cout << "temp: " << temp.getName() << endl;
	int j = 0;

	while (temp.getName() != getUjscie().getName()) {
		for (int i = 0; i < krawedzie.size(); i++) {
			if (krawedzie[i].getWychodzacy().getName() == queue.at(j).getName() && krawedzie[i].getAktualnaPrzepustowosc() != krawedzie[i].getMaksymalnaPrzepustowosc() && sprawdzCzyMaGdzieIsc(queue.at(j)) && krawedzie[i].getWchodzacy().getZnakCechy() == ' ') {
				//cout << "k: " << krawedzie[i].toString();
				temp = krawedzie[i].getWchodzacy();
				//if (find(queue.begin(), queue.end(), temp) == queue.end()) {
					queue.push_back(temp);
				//}
					
				temp.setCecha(krawedzie[i].getWychodzacy().getName());
				temp.setZnakCechy('+');
				temp.setWartoscCechy(min(krawedzie[i].getWychodzacy().getWartoscCechy(), (krawedzie[i].getMaksymalnaPrzepustowosc() - krawedzie[i].getAktualnaPrzepustowosc())));
				krawedzie[i].setWierzcholekWchodzacy(temp);
				for (int k = 0; k < krawedzie.size(); k++) {
					if (krawedzie[k].getWchodzacy().getName() == temp.getName()) {
						krawedzie[k].setWierzcholekWchodzacy(temp);
					}
					if (krawedzie[k].getWychodzacy().getName() == temp.getName()) {
						krawedzie[k].setWierzcholekWychodzacy(temp);
					}
				}
			}
			else if (!sprawdzCzyMaGdzieIsc(queue.at(j))) {
				cout << "nie ma wolnego przeplywu" << endl;
				cout << "q: " << queue.at(j).toString() << endl;
				for (int k = 0; k < krawedzie.size(); k++) {
					if (krawedzie[k].getWchodzacy().getName() == queue.at(j).getName() && krawedzie[k].getWychodzacy().getZnakCechy() == ' ') {
						temp = krawedzie[k].getWychodzacy();
						temp.setCecha(krawedzie[k].getWchodzacy().getName());
						temp.setZnakCechy('-');
						temp.setWartoscCechy(min(krawedzie[k].getWchodzacy().getWartoscCechy(), krawedzie[k].getAktualnaPrzepustowosc()));
						krawedzie[k].setWierzcholekWychodzacy(temp);
						for (int j = 0; j < krawedzie.size(); j++) {
							if (krawedzie[j].getWchodzacy().getName() == temp.getName())
								krawedzie[j].setWierzcholekWchodzacy(temp);
							if (krawedzie[j].getWychodzacy().getName() == temp.getName())
								krawedzie[j].setWierzcholekWychodzacy(temp);
						}
					}
				}
				i = krawedzie.size();
				temp = getUjscie();
			}
		}
		j++;
	}
	wypisz();
	wypiszKolejke(queue);

	return temp;
}

void Siec::przeplyw(Wierzcholek temp) {

	int przep = temp.getWartoscCechy();
	temp.setName(getUjscie().getName());
	while (temp.getName() != getZrodlo().getName()) {
		if (temp.getZnakCechy() == '+') {
			for (int i = 0; i < krawedzie.size(); i++) {
				if (krawedzie[i].getWychodzacy().getName() == temp.getCecha() && krawedzie[i].getWchodzacy().getName() == temp.getName()) {
					krawedzie[i].setAktualnaPrzepustowosc(krawedzie[i].getAktualnaPrzepustowosc() + przep);
					temp = krawedzie[i].getWychodzacy();
					temp.setCzyJestNaSciezce(true);
					krawedzie[i].setWierzcholekWychodzacy(temp);
				}
			}
		}
		else {
			cout << "minusowa!!" << endl;
			temp = getZrodlo();
		}
	}

}

void Siec::minimalnyPrzekroj() {
	cout << "Przekroj:" << endl;
	cout << "{"<<endl;
	for (int i = 0; i < krawedzie.size(); i++) 
		if (!krawedzie[i].getWychodzacy().getCzyJestNaSciezce()) 
			cout << "(" << krawedzie[i].getWychodzacy().getName() << "," << krawedzie[i].getWchodzacy().getName() << ")," << endl;
	cout << "}"<<endl;
}

void Siec::wyczyscKrawedzie() {
	Wierzcholek temp;

	for (int i = 0; i < krawedzie.size(); i++) {
		if (krawedzie[i].getWychodzacy().getName() != getZrodlo().getName()) {
			temp = krawedzie[i].getWchodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			temp.setCzyJestNaSciezce(false);
			krawedzie[i].setWierzcholekWchodzacy(temp);
			temp = krawedzie[i].getWychodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			temp.setCzyJestNaSciezce(false);
			krawedzie[i].setWierzcholekWychodzacy(temp);
		}
		else {
			temp = krawedzie[i].getWchodzacy();
			temp.setCecha(' ');
			temp.setZnakCechy(' ');
			temp.setWartoscCechy(0);
			temp.setCzyJestNaSciezce(false);
			krawedzie[i].setWierzcholekWchodzacy(temp);
			temp = krawedzie[i].getWychodzacy();
			temp.setCzyJestNaSciezce(false);
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

	if (sprawdzCzyjestUjscie() && sprawdzCzyJestZrodlo() && sprawdzCzyJestDrogaPomiedzyZrodlemAUjsciem()) {

		Wierzcholek beg = getZrodlo();
		Wierzcholek temp;

		deque<Wierzcholek> queue;

		beg.setWartoscCechy(1000);
		
		queue.push_back(beg);
		temp = cechowanie(queue, queue.back());
		przeplyw(temp);
		cout << "Pierwsza iteracja:" << endl;
		wypisz();
		wyczyscKrawedzie();
		queue.clear();

		queue.push_back(beg);
		temp = cechowanie(queue, queue.back());
		przeplyw(temp);
		cout << "Druga iteracja" << endl;
		wypisz();
		wyczyscKrawedzie();
		queue.clear();

		queue.push_back(beg);
		temp = cechowanie(queue, queue.back());
		przeplyw(temp);
		cout << "Trzecia iteracja" << endl;
		wypisz();
		wyczyscKrawedzie();
		queue.clear();

		queue.push_back(beg);
		temp = cechowanie(queue, queue.back());
		przeplyw(temp);
		cout << "Czwarta iteracja" << endl;
		wypisz();
		wyczyscKrawedzie();
		queue.clear();

		queue.push_back(beg);
		temp = cechowanie(queue, queue.back());
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

