#include <iostream>
#include <cassert>

#include "cache_t.h"

struct elem {
    int id;
    int frequency;
};

int main()
{
    int m, n, id;
    elem i_el;

    std::cin >> n >> m;
    cache <elem> mycache(m);
    for(int i = 0; i < n; i++) {
        std::cin >> id;
        i_el = {id, 0};
        std::cout << mycache.lookup(&i_el) << "\n";
    }
    return 0;
}
