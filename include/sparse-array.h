#ifndef SPARSE_ARRAY_H
#define SPARSE_ARRAY_H
#include "rank.h"
#include <string>
#include <vector>

class SparseArray {
    public:
        SparseArray(sdsl::bit_vector& v);
        void create(uint64_t size);
        void append(string elem, uint64_t pos);
        bool get_at_rank(uint64_t r, string& elem);
        bool get_at_index(uint64_t index, string& elem);
        uint64_t num_elem_at(uint64_t r);
        uint64_t size();
        uint64_t size_bytes();
        uint64_t overhead();
        uint64_t num_elem();
        void build_index();
        void save(string& fname);
        void load(string& fname);
        SelectBitset locations;
    private:
        vector<string> elements;

};

#endif

