#include "BloomFilter.h"
#include "MurmurHash3.h"
#include <cstdint>
#include <mutex>


BloomFilter::BloomFilter(size_t s, int h) : size(s), num_hashes(h) {
    counts.resize(size,0);
    //bit_array.resize(size, false);
}

void BloomFilter:: add(const std::string& item) {
    std::unique_lock lock(mtx);
    uint64_t hash_out[2];

    MurmurHash3_x64_128(item.c_str(), (int)item.length(), 42, hash_out);

    uint64_t h1 = hash_out[0];
    uint64_t h2 = hash_out[1];

    for(int i=0; i<num_hashes; i++){
        size_t index = (h1 + i*h2) % size;
        if(counts[index]<255) counts[index]++;
        //bit_array[index] = true;
    }
}

void BloomFilter:: remove(const std:: string& item){
    std::unique_lock lock(mtx);
    uint64_t hash_out[2];

    MurmurHash3_x64_128(item.c_str(), (int)item.length(), 42, hash_out);

    uint64_t h1 = hash_out[0];
    uint64_t h2 = hash_out[1];

    for(int i=0; i<num_hashes; i++){
        size_t index = (h1 + i*h2) % size;
        if(counts[index] > 0) counts[index]--;
    }
}



bool BloomFilter::contains( const std::string& item) const {
    std::shared_lock lock(mtx);
    uint64_t hash_out[2];
    MurmurHash3_x64_128(item.c_str(), (int)item.length(), 42, hash_out);

    uint64_t h1 = hash_out[0];
    uint64_t h2 = hash_out[1];

    for(int i=0; i<num_hashes; i++){
        size_t index = (h1 + i * h2) % size;

        // if(!bit_array[index]){
        //     return false;
        // }
        if(counts[index]==0) return false;
    }

    return true;
}

