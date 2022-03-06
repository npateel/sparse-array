#include <iostream>
#include "rank.h"
#include <sdsl/bit_vectors.hpp>
using namespace std;

int main() {
	sdsl::bit_vector v(16, 0);
	v[0] = 1;
	v[3] = 1;
	v[5] = 1;
	v[6] = 1;

	v[7] = 1;
	v[9] = 1;
	v[12] = 1;
	v[14] = 1;

	RankBitset r(v);
	cout << "Value is " << v.get_int(0,16) << endl;

	for (int i = 0; i < 16; i++) {
		cout << "Rank at " << i << " is " << r.rank1(i) << endl;
	}
	cout << r.ranks << endl;

}

