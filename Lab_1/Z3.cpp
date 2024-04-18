#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

// Zegar i funkcje czasu
typedef std::chrono::steady_clock::time_point moment;

moment current_moment()
{
    return std::chrono::steady_clock::now();
};

long how_long(moment from, moment to)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(to-from).count();
};


int main()
{
    // Generować będziemy 10 milionów liczb
    int how_many = 10000000;
    std::fstream MyFile;
    MyFile.open("Z3_times.txt", std::ios::out|std::ios::binary);

    // Rozkład jednostajny dla liczb zmiennoprzecinowych podwójnej precyzji
    // z zakresu [0, 10)
    std::uniform_real_distribution<double> uni_dist(0, 10);

    // Minstd_rand
    std::random_device seed_1; // Seed
    std::minstd_rand gen_1(seed_1()); // Załadowanie generatora seedem
    moment gen_1_from = current_moment(); // Rozpoczynamy pomiar czasu
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_1); // Rozkład jednostajny z generatora 
    }
    moment gen_1_to = current_moment(); // Koniec pomiaru czasu
    long time_gen_1 = how_long(gen_1_from, gen_1_to); // Kalkulacja czasu
    std::cout << "Minstd_rand: " << time_gen_1 << std::endl; 
    MyFile << time_gen_1 << std::endl; // Zapis czasu do pliku

    // Mt19937
    std::random_device seed_2;
    std::mt19937 gen_2(seed_2());
    moment gen_2_from = current_moment();
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_2);
    }
    moment gen_2_to = current_moment();
    long time_gen_2 = how_long(gen_2_from, gen_2_to);
    std::cout << "Mt19937: " << time_gen_2 << std::endl;
    MyFile << time_gen_2 << std::endl;

    // Mt19937_64
    std::random_device seed_3;
    std::mt19937_64 gen_3(seed_3());
    moment gen_3_from = current_moment();
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_3);
    }
    moment gen_3_to = current_moment();
    long time_gen_3 = how_long(gen_3_from, gen_3_to);
    std::cout << "Mt19937_64: " << time_gen_3 << std::endl;
    MyFile << time_gen_3 << std::endl;

    // Ranlux48_base
    std::random_device seed_4;
    std::ranlux48_base gen_4(seed_4());
    moment gen_4_from = current_moment();
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_4);
    }
    moment gen_4_to = current_moment();
    long time_gen_4 = how_long(gen_4_from, gen_4_to);
    std::cout << "Ranlux48_base: " << time_gen_4 << std::endl;
    MyFile << time_gen_4 << std::endl;

    // Ranlux48
    std::random_device seed_5;
    std::ranlux48 gen_5(seed_5());
    moment gen_5_from = current_moment();
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_5);
    }
    moment gen_5_to = current_moment();
    long time_gen_5 = how_long(gen_5_from, gen_5_to);
    std::cout << "Ranlux48: " << time_gen_5 << std::endl;
    MyFile << time_gen_5 << std::endl;

    // Knuth_b
    std::random_device seed_6;
    std::knuth_b gen_6(seed_6());
    moment gen_6_from = current_moment();
    for (int i=0; i < how_many; i++)
    {
        uni_dist(gen_6);
    }
    moment gen_6_to = current_moment();
    long time_gen_6 = how_long(gen_6_from, gen_6_to);
    std::cout << "Knuth_b: " << time_gen_6 << std::endl << std::endl;
    MyFile << time_gen_6 << std::endl;

    MyFile.close();

}