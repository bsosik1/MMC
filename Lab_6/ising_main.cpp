#include <iostream>
#include "model_isinga.h"
#include <fstream>
#include <string>

using namespace std;

void symulacja_mikrokanoniczna(std::string f_name, int L, int e_start, int e_end, int inc) {
	std::ofstream file;
	file.open(f_name, std::ios::out | std::ios::app);
	file << "E,L,srednia_e_ukladu,srednia_magnetyzacja,srednia_e_duszka,temperatura" << std::endl;

	// Symulacja 
	for(int E=e_start; E<=e_end; E+=inc){
		ModelIsinga ising(L, E);
		ising.doprowadzenie_do_stanu_równowagi(1000);
		ising.zliczanie_średnich(1000);

		file << E << "," << L << "," << ising.podaj_średnią_energię_układu() << ",";
		file << ising.podaj_średnią_magnetyzację() << "," << ising.podaj_średnią_energię_duszka() << ",";
		file << ising.podaj_temperaturę() << std::endl;
	}
	file.close();
}

void symulacja_kanoniczna(std::string f_name, int L, int t_start, int t_end, float inc) {
	std::ofstream file;
	file.open(f_name, std::ios::out | std::ios::app);
	file << "temperatura,L,srednia_e_ukladu,srednia_magnetyzacja" << std::endl;

	// Symulacja 
	for(float T=1.0; T<=3.0; T+=inc/5.0){
		ModelIsinga ising(L, T);
		ising.doprowadzenie_do_stanu_równowagi(1000);
		ising.zliczanie_średnich(1000);
		file << T << "," << L << "," << ising.podaj_średnią_energię_układu() << ",";
		file << ising.podaj_średnią_magnetyzację() << std::endl;
	}
	for(float T=3.0; T<=t_end; T+=inc){
		ModelIsinga ising(L, T);
		ising.doprowadzenie_do_stanu_równowagi(1000);
		ising.zliczanie_średnich(1000);

		file << T << "," << L << "," << ising.podaj_średnią_energię_układu() << ",";
		file << ising.podaj_średnią_magnetyzację() << std::endl;
	}
	file.close();
}



int main(int argc, char *argv[])
{
	// "Symulacja modelu Isinga w Zespole Mikrokanonicznym"
	int L = 10;
	symulacja_mikrokanoniczna("mikro_l10.csv", L, -184, -24, 8);
	symulacja_kanoniczna("kanon_l10.csv", L, 1.0, 6.0, 0.1);
	L = 20;
	symulacja_mikrokanoniczna("mikro_l20.csv", L, -768, -32, 32);
	symulacja_kanoniczna("kanon_l20.csv", L, 1.0, 15.0, 0.1);
	L = 40;
	symulacja_mikrokanoniczna("mikro_l40.csv", L, -3072, -128, 128);
	symulacja_kanoniczna("kanon_l40.csv", L, 1.0, 20.0, 0.1);

	return 0;
}
