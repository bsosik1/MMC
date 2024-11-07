#ifndef MODEL_ISINGA_H
#define MODEL_ISINGA_H

#include "rng.h"

/**
   @author Marek Niewiński <niewinski@linuxHP6715b>
   @author Dominik Kasprowicz
        @version 2.1
   @file
*/
class ModelIsinga {
    const int L;
    int** siatka;

    int energia_docelowa_ukladu;
    int energia_poczatkowa_ukladu;
    float temperatura_docelowa_ukladu;
    float temperatura_poczatkowa_ukladu;

    int energia_duszka;

    int magnetyzacja;
    float srednia_energia_ukladu, srednia_energia_duszka, srednia_magnetyzacja,
        temperatura, aktualna_temperatura;

    RNG generator;

    void ustaw_same_jedynki();

    void sprobuj_odwrocic_spin_losowego_atomu();
    void sprobuj_odwrocic_spin_losowego_atomu_kanoniczny();

    int deltaE(int x, int y);

  public:
    ModelIsinga(int rozmiar, int energia);
    ModelIsinga(int rozmiar, float temperatura);

    ~ModelIsinga();

    void doprowadzenie_do_stanu_rownowagi(int liczba_krokow);
    void doprowadzenie_do_stanu_rownowagi_kanoniczny(int liczba_krokow);

    void zliczanie_srednich(int liczba_krokow);
    void zliczanie_srednich_kanoniczny(int liczba_krokow);

    float podaj_srednia_energie_duszka();
    float podaj_srednia_energie_ukladu();
    float podaj_srednia_magnetyzacje();
    float podaj_temperature();
};

#endif // MODEL_ISINGA_H