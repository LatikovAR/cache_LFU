#pragma once

#include <list>
#include <unordered_map>
#include <iterator>
#include <cassert>
#include <utility>
#include <iostream>

const int FREQ_SIZE = 1000;

template <typename T>
class cache {
private:
    int size;
    std :: list<T> c_list_ar[FREQ_SIZE];
    typedef typename std::list<T>::iterator ListIt;
    std :: unordered_map<int, ListIt> hash;
public:
    cache(int c_size);
    bool full();
    bool lookup(T *elem);
};

template <typename T>
bool cache<T>::lookup(T *elem) {
    int i;
    T *d_el;
    auto hit = hash.find(elem->id);
    //std::cout << "looking for elem id " << elem->id << "\n";
    if (hit == hash.end()) {
        //std::cout << "No element\n";
        if (cache<T>::full()) {
            //std::cout << "Deleting...\n";
            i = 0;
            while(c_list_ar[i].size() == 0) {
                //std::cout << "No elems in list " << i << "\n";
                i++;
                assert(i < FREQ_SIZE);
            }
            d_el = &(*(c_list_ar[i].rbegin()));
            //std::cout << "delete elem id " << d_el->id << " from list " << i << "\n";
            hash.erase(d_el->id);
            c_list_ar[i].pop_back();
        }
        elem->frequency = 0;
        //std::cout << "first elem id in list[0] " << c_list_ar[0].begin()->id << "\n";
        //std::cout << "last elem id in list[0] " << c_list_ar[0].rbegin()->id << "\n";
        //std::cout << "size list[0] " << c_list_ar[0].size() << "\n";
        c_list_ar[0].push_front(*elem);
        //std::cout << "first elem id in list[0] " << c_list_ar[0].begin()->id << "\n";
        //std::cout << "last elem id in list[0] " << c_list_ar[0].rbegin()->id << "\n";
        //std::cout << "size list[0] " << c_list_ar[0].size() << "\n";
        hash[elem->id] = c_list_ar[0].begin();
        //std::cout << "first elem id in list[0] " << c_list_ar[0].begin()->id << "\n";
        //std::cout << "last elem id in list[0] " << c_list_ar[0].rbegin()->id << "\n";
        return false;
    }
    //std::cout << "elem found\n";
    auto eltit = hit->second;
    int f = eltit->frequency;
    //std::cout << "his cur frequency " << f << "\n";
    int f_new = f;
    if(f + 1 < FREQ_SIZE){
        eltit->frequency++;
        f_new++;
    }
    //std::cout << "his new frequency " << f << "\n";
    //std::cout << "replacing element id " << eltit->id << "\n";
    c_list_ar[f_new].splice(c_list_ar[f_new].begin(), c_list_ar[f], eltit);
    //std::cout << "first elem id in list[0] " << c_list_ar[0].begin()->id << "\n";
    //std::cout << "last elem id in list[0] " << c_list_ar[0].rbegin()->id << "\n";
    return true;
}

template <typename T>
bool cache<T>::full() {
    assert(hash.size() <= (size_t) size);
    if(hash.size() == (size_t) size) {
        return true;
    }
    return false;
}

template <typename T>
cache<T>::cache(int c_size) {
    size = c_size;
}
