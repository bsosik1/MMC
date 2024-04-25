#include <iostream>
#include <fstream>
#include <random>
#include <string>

int main()
{
    // Inicjalizacja 
    int count=1000000; // Liczebność próby losowej
    std::fstream File;
    std::string f_name = "Z2_count_" + std::to_string(count) + ".csv";
    File.open(f_name, std::ios::out|std::ios::binary);
    File << "Minstd_rand;Ranlux48_base\n";  
    
    // "Zły" generator - minstd_rand
    std::random_device seed_1;
    std::minstd_rand bad_gen(seed_1());

    // "Dobry" generator - Ranlux48
    std::random_device seed_2;
    std::ranlux48_base good_gen(seed_2());

    // Rozkład równomierny na przedziale [0, 10)
    std::uniform_real_distribution<double> uni_dist(0, 10);

    // Wygeneruj i zapisz do pliku
    for (int i=0; i<count; i++)
    {
        File << uni_dist(bad_gen) << ";";
        File << uni_dist(good_gen) << std::endl;
    }
    return 0;
}
