#include <iostream>
#include <fstream>
#include "Siec.h"
#include <vector>

using namespace std;

int main() {

	Siec siec;
	siec.uzupelnijVector();
	siec.wypisz();

	siec.algorithm();

	system("PAUSE");
	return 0;
}