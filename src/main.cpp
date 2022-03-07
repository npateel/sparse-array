#include <iostream>
#include "rank.h"
#include <sdsl/bit_vectors.hpp>
using namespace std;

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

}

