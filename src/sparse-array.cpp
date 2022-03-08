#include "sparse-array.h"

template <class T>
void SparseArray<T>::create(uint64_t size) {
    sdsl::bit_vector bits(size);
    locations(r);
}

template <class T>
void SparseArray<T>::append(T elem, uint64_t pos) {
    locations.set(pos);
    
    elements.push_back(elem);
    
}

template <class T>
bool SparseArray<T>::get_at_rank(uint64_t r, T& elem) {
    if (elements.size() < r || r == 0) {
        return false;
    }
    
    get_at_index(locations.select1(r), elem);
    return true;

}

template <class T>
bool SparseArray<T>::get_at_index(uint64_t index, T& elem) {
    if (index > locations.bits.size() || !locations.bits[index]) {
        return false;
    }
    
    elem = elements[locations.rank1(index) -1];
    return true;

}
template <class T>
uint64_t SparseArray<T>::num_elem_at(uint64_t index) {
    return locations.rank1(index);
}
template <class T>
inline uint64_t SparseArray<T>::size() {
    return locations.bits.size();
}

template <class T>
inline uint64_t SparseArray<T>::num_elem() {
    return elements.size();
}

template <class T>
inline void SparseArray<T>::save(string& fname) {
    ofstream out;
    out.open(fname);
    out << elements.size() << endl;
    for (int i = 0; i < elements.size(); i++) {
        out << elements[i] << endl;
    }

    locations.save(out);
    out.close();
}

inline void SparseArray<string>::load(string& fname) {
    ifstream in;
    in.open(fname);
    string line;
    getline(in, line);
    uint64_t size = std::stoull(line);
    elements.resize(size);
    for (int i = 0; i < (int64_t)size; i++) {
        getline(in, line);
        elements[i] = line;
    }
    locations.load(in);
    in.close();
}

template <class T>
uint64_t SparseArray<T>::size_bytes() {
    return locations.bits.bit_size / 8 + 
            locations.ranks.bit_size / 8 +
            locations.superRanks.bit_size / 8 +
            sizeof(locations.bits) + sizeof(locations.ranks) + 
            sizeof(locations.superRanks)
            + sizeof(elements) + elements[0].size()*elements.size();
}

template <class T>
uint64_t SparseArray<T>::overhead() {
    return locations.bits.bit_size / 8 + 
            locations.ranks.bit_size / 8 +
            locations.superRanks.bit_size / 8 +
            sizeof(locations.bits) + sizeof(locations.ranks) + 
            sizeof(locations.superRanks);
}