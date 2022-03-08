#ifndef RANK_H
#define RANK_H
#include <vector>
#include <stdint.h>
#include <string>
#include <sdsl/int_vector.hpp>
#include <cmath>
#include <iostream>
#include <bit>
using namespace std;




class RankBitset
{
    public:
        RankBitset(sdsl::int_vector<1>& bits);
        uint64_t overhead();
        uint64_t rank1(uint64_t index);
        void save(string& fname);
        void save(ofstream& out);
        void load(string& fname);
        void load(ifstream& in);
        void set(uint64_t index);
        sdsl::int_vector<0> superRanks;
        sdsl::int_vector<0> ranks;
        sdsl::int_vector<0> subRanks;
        sdsl::int_vector<1> bits;
    private:
        // computes rank [start, end)
        uint32_t naiveRank(int64_t start, int64_t end);
        void buildIndex();
};

class SelectBitset : public RankBitset
{
    public:
        uint64_t select1(uint64_t index);
        SelectBitset() = default;
        SelectBitset(sdsl::int_vector<1>& bits) : RankBitset(bits){}
};
#endif
