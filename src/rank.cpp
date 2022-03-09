#include "rank.h"

using namespace std;

RankBitset::RankBitset(sdsl::int_vector<1>& bits) {
  this->bits = bits;
  buildIndex();
  
}
void RankBitset::set(uint64_t index) {
  bits[index] = 1;
  valid_index = false;
}

void RankBitset::buildIndex() {
  uint64_t n = bits.size();
  uint32_t log = ceil(log2(n));
  uint32_t loglog = log2(log);
  uint32_t s = log * log;
  this->superRanks = sdsl::int_vector<0>(ceil(n / (double)s), 0, log *2);
  uint64_t sum = 0;
  for (int i = 0; i < ceil(n / (float)s); i++) {
    uint64_t slice =naiveRank((i - 1) * (int64_t)s, i * (int64_t)s);
    superRanks[i] = naiveRank((i - 1) * (int64_t)s, i * (int64_t)s) + sum;
    sum += slice;
  }
  uint32_t b = log;
  ranks = sdsl::int_vector<0>(superRanks.size() * b, 0, loglog *2);

  sum = 0;
  for (int k = 0; k < (long)ranks.size(); k++) {
    int64_t j = k / b;
    uint64_t slice = naiveRank((k - 1) * (int64_t)b, (k) * (int64_t)b);
    ranks[k] = slice - superRanks[j] + sum;
    sum += slice;
  }
  valid_index = true;
}

uint64_t RankBitset::overhead() {
  return superRanks.bit_size() + ranks.bit_size() 
  + sizeof(ranks) + sizeof(superRanks) + sizeof(this);
}
uint64_t RankBitset::rank1(uint64_t index) {
  if (!valid_index) {
    buildIndex();
  }  


  uint32_t b = ceil(log2(bits.size()));
  uint32_t blockIndex = index / b * b;

  uint64_t rank = 0;
  if (blockIndex >= 0 && index < bits.size()) {
    rank = bits.get_int(blockIndex, index - blockIndex + 1);
  }
  return superRanks[index / b / b] + ranks[index / b] + __popcount(rank);
}

// gets rank of [start, end)
uint32_t RankBitset::naiveRank(int64_t start, int64_t end) {
  if (start < 0) {
    return 0;
  }
  if (end >= (long)bits.size()) {
    return 0;
  }

  uint64_t rank = 0;
  while (start < end -64) {
    uint64_t val = bits.get_int(start, 64);
    rank += __popcount(val);
    start += 64;
  }
  rank += __popcount(bits.get_int(start, end - start));
  return rank;
}

void RankBitset::load(string& filename) {

  ifstream in;
  in.open(filename);
  load(in);
  in.close();
}

void RankBitset::load(ifstream& in) {
  bits.load(in);
  superRanks.load(in);
  ranks.load(in);
}

void RankBitset::save(string& filename) {
  ofstream out;
  out.open(filename);
  save(out);
  out.close();
}

void RankBitset::save(ofstream& out) {
if (!valid_index) {
    buildIndex();
  }
  bits.serialize(out);
  superRanks.serialize(out);
  ranks.serialize(out); 
}
