#include "sparse-array.h"

SparseArray::SparseArray() = default;
SparseArray::SparseArray(uint64_t size) {
    sdsl::bit_vector ve(size);
    locations = SelectBitset(ve);
    elements = vector<string>(0);
}

void SparseArray::create(uint64_t size) {
    sdsl::bit_vector ve(size);
    locations = SelectBitset(ve);
}

void SparseArray::append(string elem, uint64_t pos) {
    locations.set(pos);
    
    elements.push_back(elem);
    
}

bool SparseArray::get_at_rank(uint64_t r, string& elem) {
    if (elements.size() < r || r == 0) {
        return false;
    }
    
    get_at_index(locations.select1(r), elem);
    return true;

}


bool SparseArray::get_at_index(uint64_t index, string& elem) {
    if (index > locations.bits.size() || !locations.bits[index]) {
        return false;
    }
    
    elem = elements[locations.rank1(index) -1];
    return true;

}

uint64_t SparseArray::num_elem_at(uint64_t index) {
    return locations.rank1(index);
}

uint64_t SparseArray::size() {
    return locations.bits.size();
}


uint64_t SparseArray::num_elem() {
    return elements.size();
}


void SparseArray::save(string& fname) {
    ofstream out;
    out.open(fname);
    out << elements.size() << endl;
    for (int i = 0; i < elements.size(); i++) {
        out << elements[i] << endl;
    }

    locations.save(out);
    out.close();
}

void SparseArray::load(string& fname) {
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


uint64_t SparseArray::size_bytes() {
    return locations.bits.bit_size() / 8 + 
            locations.ranks.bit_size() / 8 +
            locations.superRanks.bit_size() / 8 +
            sizeof(locations.bits) + sizeof(locations.ranks) + 
            sizeof(locations.superRanks)
            + sizeof(elements) + elements[0].size()*elements.size();
}


uint64_t SparseArray::overhead() {
    return locations.bits.bit_size() / 8 + 
            locations.ranks.bit_size() / 8 +
            locations.superRanks.bit_size() / 8 +
            sizeof(locations.bits) + sizeof(locations.ranks) + 
            sizeof(locations.superRanks);
}