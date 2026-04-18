#include "BloomFilter.h"
#include "MurmurHash3.h"
#include <cstdint>


BloomFilter::BloomFilter(size_t s, int h) : size(s), num_hashes(h) {
    bit_array.resize(size, false);
}

void BloomFilter:: add(const std::string& item) {
    uint64_t hash_out[2];

    MurmurHash3_x64_128(item.c_str(), (int)item.length(), 42, hash_out);

    uint64_t h1 = hash_out[0];
    uint64_t h2 = hash_out[1];

    for(int i=0; i<num_hashes; i++){
        size_t index = (h1 + i*h2) % size;
        bit_array[index] = true;
    }
}

bool BloomFilter::contains( const std::string& item) const {
    uint64_t hash_out[2];
    MurmurHash3_x64_128(item.c_str(), (int)item.length(), 42, hash_out);

    uint64_t h1 = hash_out[0];
    uint64_t h2 = hash_out[1];

    for(int i=0; i<num_hashes; i++){
        size_t index = (h1 + i * h2) % size;

        if(!bit_array[index]){
            return false;
        }
    }

    return true;
}

