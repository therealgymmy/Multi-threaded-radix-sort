#include <iostream>
#include <cstdlib>
#include <ctime>

#include "radix.hpp"

int main ()
{
    std::srand( std::time(NULL) );

    j::List list;
    for (int i = 0; i < 29999; ++i) {
        int random = (rand() % 10000);
        list.push_back(random);
    }
    for (int i = 0; i < 29999; ++i) {
        int random = (rand() % 10000) + 10000;
        list.push_back(random);
    }
    for (int i = 0; i < 29999; ++i) {
        int random = (rand() % 10000) + 20000;
        list.push_back(random);
    }
    for (int i = 0; i < 29999; ++i) {
        int random = (rand() % 10000) + 30000;
        list.push_back(random);
    }
    for (int i = 0; i < 29999; ++i) {
        int random = (rand() % 10000) + 40000;
        list.push_back(random);
    }





    j::rSort(list);

    //for (unsigned i = 0; i < list.size(); ++i) {
        //std::cout << list[i] << " ";
    //}
    //std::cout << std::endl;

    return 0;
}
