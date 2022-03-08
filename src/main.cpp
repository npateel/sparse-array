#include "rank.h"
#include <iostream>
#include <stdlib.h>
#include "sparse-array.h"
#include <vector>
#include <sdsl/bit_vectors.hpp>
#include <chrono>
using namespace std;



sdsl::bit_vector create_random_bitvector(uint64_t size, uint64_t num_set) {
  sdsl::bit_vector ret(size, 0);
  srand(0);

  for (int i = 0; i < num_set; i++) {
    int index = rand() % size;
    ret[index] = 1;
  }
  return ret;
}

sdsl::bit_vector create_random_bitvector(uint64_t size) {
  sdsl::bit_vector ret(size, 0);
  srand(0);

  for (int i = 0; i < size; i++) {
    if (rand() % 2 == 1) {
      ret[i] = 1;
    }

  }
  return ret;
}


double test_rank(SelectBitset& bitset, uint64_t queries) {
  auto t1 = chrono::high_resolution_clock::now();
  for (uint64_t i = 0; i < queries; i++) {
    bitset.rank1(rand() % bitset.bits.size());
  }
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> ms_double = t2 - t1;
  return ms_double.count();
}

double test_select(SelectBitset& bitset, uint64_t queries) {
  auto t1 = chrono::high_resolution_clock::now();
  for (uint64_t i = 0; i < queries; i++) {
    bitset.select1(rand() % bitset.bits.size());
  }
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> ms_double = t2 - t1;
  return ms_double.count();
}
void test_vectors() {
  ofstream out;
  out.open("rank_simple.csv");

  out << "n,rank_time,select_time,overhead" << endl;

//  vector<uint64_t> sizes{100, 500, 2500, 12500, 62500, 312500, 1562500, 7812500, 39062500 };
	vector<uint64_t> sizes(0);
	uint64_t startingSize = 100; // a couple of bytes
	uint64_t endingSize = 1e11;  // 1.25 GB

	while (startingSize < endingSize) {
		sizes.push_back(startingSize);
		startingSize *= 5;
	}

  for (uint64_t size : sizes) {
    //sdsl::bit_vector vector = create_random_bitvector(size);
	sdsl::bit_vector vector(size);

    SelectBitset bits(vector);
    double rank_time = test_rank(bits, 100);
    double select_time = test_select(bits, 100);
    uint64_t overhead = bits.overhead();

    out << size << "," << rank_time << "," << select_time << "," << overhead
        << endl;
  }
  out.close();
}

void populate_sparse_array(SparseArray& arr, double sparsity) {
  uint64_t size = arr.size();
  vector<int> locations;
  for (uint i = 0; i < sparsity * size; i++) {
    locations.push_back(rand() % size);
  }

  sort(locations.begin(), locations.end());

  for (uint i = 0; i < locations.size(); i++) {
    arr.append(to_string(i % 10), locations[i]);
  }
}

double test_get_at_rank(SparseArray& arr, uint32_t queries) {
  uint elements = arr.num_elem();
  string elem;
  auto t1 = chrono::high_resolution_clock::now();

  for (uint i = 0; i < queries; i++) {
    arr.get_at_rank(rand() % elements + 1, elem);
  }
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> ms_double = t2 - t1;
  return ms_double.count();
}

double test_get_at_index(SparseArray& arr, uint32_t queries) {
  uint elements = arr.size();
  string elem;
  auto t1 = chrono::high_resolution_clock::now();

  for (uint i = 0; i < queries; i++) {
    arr.get_at_index(rand() % elements + 1, elem);
  }
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> ms_double = t2 - t1;
  return ms_double.count();
}

double test_num_elem_at(SparseArray& arr, uint32_t queries) {
  uint elements = arr.size();
  string elem;
  auto t1 = chrono::high_resolution_clock::now();

  for (uint i = 0; i < queries; i++) {
    arr.num_elem_at(rand() % elements);
  }
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> ms_double = t2 - t1;
  return ms_double.count();
}

void test_sparse_array() {
  vector<uint64_t> sizes {1000, 10000, 100000, 1000000};
  vector<double> sparsities {1.0/100, 5.0/100, 10.0/100};

  ofstream out;
  out.open("array.csv");

  out << "size,sparsity,get_at_rank_time,get_at_index_time,num_elem_at_time,size_bytes,overhead" << endl;

  for (uint64_t size: sizes) {
    for (double sparsity: sparsities) {
      SparseArray arr;
	  arr.create(size);
      populate_sparse_array(arr, sparsity);
      double rank_time = test_get_at_rank(arr, 100);
      double index_time = test_get_at_index(arr, 100);
      double elem_at_time = test_num_elem_at(arr, 100);
      uint64_t size = arr.size_bytes();
      uint64_t overhead = arr.overhead();
      out << size << "," << sparsity << ","
       << rank_time << "," << index_time << ","
       << elem_at_time << "," << size << "," << overhead << endl;
    }
    out.close();
  }

}

int main() {
  sdsl::bit_vector v(10000000, 0);
  cout << "here" << endl;
  v[0] = 1;
  v[3] = 1;
  v[5] = 1;
  v[6] = 1;

  v[7] = 1;
  v[9] = 1;
  v[12] = 1;
  v[14] = 1;
  v[250] = 1;
  v[270] = 1;
  v[510] = 1;

  SelectBitset r(v);

  // for (int i = 0; i < 512; i++) {
  // 	uint64_t rank = r.rank1(i);
  // 	cout << "Rank at " << i << " is " << rank << endl;
  // }

  // cout << r.superRanks << endl;
  // cout << r.ranks << endl;
  cout << "Overhead: " << r.overhead() << endl;
  cout << r.select1(0) << endl;

  test_vectors();
}

