#include "rank.h"

using namespace std;


RankBitset::RankBitset(sdsl::int_vector<1>& bits) {
            this->bits = bits;
            uint64_t n = bits.size();
            uint32_t log = log2(n);
            uint32_t loglog = log2(log);
            uint32_t s = log * log  / 2;
            this->superRanks = sdsl::int_vector<0>(n / s, 0, log);
            for(int i = 0; i < (int64_t)(n/s); i++) {
                superRanks[i] = naiveRank((i - 1)* (int64_t)s,
                 i * (int64_t)s);
            }
            uint32_t b = log / 2;
            ranks = sdsl::int_vector<0>(n / b, 0, loglog);

            uint64_t sum = 0;
            for (int k = 0; k < (int64_t)(n / b); k++) {
                int64_t j = (int64_t)b*k / s;
                uint64_t slice = naiveRank((k-1) * (int64_t)b, (k) * (int64_t)b );
                ranks[k] = slice - superRanks[j] + sum;
                sum += slice;
            }



        }
uint64_t RankBitset::overhead() {
    return superRanks.bit_size() + ranks.bit_size() + subRanks.bit_size();
}
uint64_t RankBitset::rank1(uint64_t index) {
    uint32_t blockIndex = index / bits.size() * ranks.size();

    uint64_t rank = bits.get_int(blockIndex, index - blockIndex + 1);
    return superRanks[index / bits.size() * superRanks.size()] 
    + ranks[index / bits.size() * ranks.size() ] + 
    __popcount(rank);
}
uint32_t RankBitset::naiveRank(int64_t start, int64_t end) {

    if (start < 0) {
        start =0;
    }
    uint64_t *raw = bits.data();
    raw += (start / sizeof(uint64_t));
    uint64_t rank = 0;
    while (start < end - 64) {
        rank += __popcount(*(raw + start / 64));
        start += 64;
    }
    rank += __popcount( bits.get_int(start, end - start));
    return rank;
}