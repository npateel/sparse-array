#ifndef SPARSE_ARRAY_H
#define SPARSE_ARRAY_H
#include "rank.h"
#include <string>
#include <vector>

template <class T>
class SparseArray {
    public:
        void create(uint64_t size);
        void append(T elem, uint64_t pos);
        bool get_at_rank(uint64_t r, T& elem);
        bool get_at_index(uint64_t index, T& elem);
        uint64_t num_elem_at(uint64_t r);
        uint64_t size();
        uint64_t num_elem();
        void save(string& fname);
        void load(string& fname);
    private:
        vector<T> elements;
        SelectBitset locations;

};

#endif

