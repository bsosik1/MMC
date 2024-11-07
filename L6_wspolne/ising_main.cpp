#include "model_isinga.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void symMikroKanoniczna(const std::string& filename, int L, int start, int koniec, int przyrost) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::app); // otwórz plik do zapisu, dodawanie na końcu pliku
    file << "E,L,srednia_energie_ukladu,srednia_magnetyzacje,srednia_energie_duszka,temperature" << std::endl;

    for (int E = start; E <= koniec; E += przyrost) {
        ModelIsinga ising(L, E);
        ising.doprowadzenie_do_stanu_rownowagi(1000);
        ising.zliczanie_srednich(1000);
        file << E << "," << L << "," << ising.podaj_srednia_energie_ukladu() << "," << ising.podaj_srednia_magnetyzacje() << "," << ising.podaj_srednia_energie_duszka() << "," << ising.podaj_temperature() <<std::endl;
    }

    file.close();
}


void symKanoniczna(const std::string& filename, int L, float start, float koniec, float przyrost) {
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::app); // otwórz plik do zapisu, dodawanie na końcu pliku
    file << "T,L,srednia_energie_ukladu,srednia_magnetyzacje" << std::endl;

	for (float T = 1.0; T <= 3.0; T += przyrost/10) {
        ModelIsinga ising(L, T);
        ising.doprowadzenie_do_stanu_rownowagi_kanoniczny(1000);
        ising.zliczanie_srednich_kanoniczny(1000);
        file << T << "," << L << "," << ising.podaj_srednia_energie_ukladu() << "," << ising.podaj_srednia_magnetyzacje() << std::endl;
    }
    for (float T = 3.0; T <= koniec; T += przyrost) {
        ModelIsinga ising(L, T);
        ising.doprowadzenie_do_stanu_rownowagi_kanoniczny(1000);
        ising.zliczanie_srednich_kanoniczny(1000);
        file << T << "," << L << "," << ising.podaj_srednia_energie_ukladu() << "," << ising.podaj_srednia_magnetyzacje() << std::endl;
    }
    file.close();
}


int main(int argc, char* argv[]) {
	int L = 10;
	symKanoniczna("KanL10.csv", L, 1.0, 6.0, 0.1);
	symMikroKanoniczna("MikroKanL10.csv", L, -184, -24, 8);
    L = 20;
	symKanoniczna("KanL20.csv", L, 1.0, 14.0, 0.1);
	symMikroKanoniczna("MikroKanL20.csv", L, -768, -32, 32);
	L = 40;
	symKanoniczna("KanL40.csv", L, 1.0, 20.0, 0.1);
	symMikroKanoniczna("MikroKanL40.csv", L, -3072, -128, 128);
    return 0;
}