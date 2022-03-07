#include "rank.h"

uint64_t SelectBitset::select1(uint64_t index) {
    int64_t start = 0;
    int64_t end = bits.size() - 1;
    int64_t mid = (start + end) / 2;
    int64_t result = -1;
    while (start <= end) {
        mid = (start + end) / 2;
        int64_t rank = rank1(mid);
        cout << "start: " << start << " end: " << end  << " mid: " << mid  << " rank: " << rank<< endl;
        if (rank >= index) {
            end = mid -1;
            result = mid;
        } else {
            start = mid + 1;
        }
    }
    return result;
}
