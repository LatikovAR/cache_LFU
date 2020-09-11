#include <iostream>
#include <cassert>
#include <ctime>

#include "cache_t.h"

struct elem {
    int id;
    int frequency;
};

const unsigned long long DISTANCE = 1000000;

double random_test(int m);
double const_test(int m);
double small_range_test(int m);
double search_in_locality_test(int m, unsigned long long T_move, int loc_size);

int main()
{
    int m;

    srand(unsigned (time(nullptr)));
    std::cout << "Input cache size: ";
    std::cin >> m;
    std::cout << "const test: " << const_test(m) << "\n";
    std::cout << "random test: " << random_test(m) << "\n";
    std::cout << "small range test: " << small_range_test(m) << "\n";
    std::cout << "Locality tests:\n";
    std::cout << "T = 100, locality = 10: " << search_in_locality_test(m, 100, 10) << "\n";
    std::cout << "T = 1000, locality = 10: " << search_in_locality_test(m, 1000, 10) << "\n";
    std::cout << "T = 10000, locality = 10: " << search_in_locality_test(m, 10000, 10) << "\n";
    std::cout << "T = 100000, locality = 10: " << search_in_locality_test(m, 100000, 10) << "\n";
    std::cout << "T = 1000, locality = 100: " << search_in_locality_test(m, 1000, 100) << "\n";
    std::cout << "T = 10000, locality = 100: " << search_in_locality_test(m, 10000, 100) << "\n";
    std::cout << "T = 100000, locality = 100: " << search_in_locality_test(m, 100000, 100) << "\n";
    std::cout << "T = 1000, locality = 1000: " << search_in_locality_test(m, 1000, 1000) << "\n";
    std::cout << "T = 10000, locality = 1000: " << search_in_locality_test(m, 10000, 1000) << "\n";
    std::cout << "T = 100000, locality = 1000: " << search_in_locality_test(m, 100000, 1000) << "\n";
    std::cout << "T = 1000, locality = 10000: " << search_in_locality_test(m, 1000, 10000) << "\n";
    std::cout << "T = 10000, locality = 10000: " << search_in_locality_test(m, 10000, 10000) << "\n";
    std::cout << "T = 100000, locality = 10000: " << search_in_locality_test(m, 100000, 10000) << "\n";
    return 0;
}

double random_test(int m) {
    elem i_el;
    int id;
    unsigned long long hit_num = 0;
    cache <elem> mycache(m);
    for(unsigned long long i = 0; i < DISTANCE; i++) {
        id = rand();
        i_el = {id, 0};
        if(mycache.lookup(&i_el)) hit_num++;
    }
    return double(hit_num) / double(DISTANCE);
}

double const_test(int m) {
    elem i_el;
    int id;
    unsigned long long hit_num = 0;
    cache <elem> mycache(m);
    for(unsigned long long i = 0; i < DISTANCE; i++) {
        id = 10;
        i_el = {id, 0};
        if(mycache.lookup(&i_el)) hit_num++;
    }
    return double(hit_num) / double(DISTANCE);
}

double small_range_test(int m) {
    elem i_el;
    int id;
    unsigned long long hit_num = 0;
    cache <elem> mycache(m);
    for(unsigned long long i = 0; i < DISTANCE; i++) {
        id = rand() % 1000;
        i_el = {id, 0};
        if(mycache.lookup(&i_el)) hit_num++;
    }
    return double(hit_num) / double(DISTANCE);
}

double search_in_locality_test(int m, unsigned long long t_move, int loc_size) {
    elem i_el;
    int id;
    unsigned long long counter = 0;
    int anchor = rand();
    unsigned long long hit_num = 0;
    cache <elem> mycache(m);
    for(unsigned long long i = 0; i < DISTANCE; i++) {
        if(counter >= t_move) {
            anchor = rand();
            counter = 0;
        }
        id = (rand() % loc_size) + anchor;
        i_el = {id, 0};
        if(mycache.lookup(&i_el)) hit_num++;
        counter++;
    }
    return double(hit_num) / double(DISTANCE);
}
