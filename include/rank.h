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

static inline uint32_t log2(const uint32_t x) {
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}


class RankBitset
{
    public:
        RankBitset(sdsl::int_vector<1>& bits);
        uint64_t overhead();
        uint64_t rank1(uint64_t index);
        void save(string& fname);
        void load(string& fname);
        sdsl::int_vector<0> superRanks;
        sdsl::int_vector<0> ranks;
        sdsl::int_vector<0> subRanks;
        sdsl::int_vector<1> bits;
    private:
        // computes rank [start, end)
        uint32_t naiveRank(int64_t start, int64_t end);
};

class SelectBitset
{
    public:
        SelectBitset(RankBitset& bits);
        uint64_t select1(uint64_t index);
        uint64_t overhead();
        void save(string& fname);
        void load(string& fname);
};
#endif
