
#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>
#include <functional>
#include <shared_mutex>

class BloomFilter {
    private:
        std::vector<uint8_t> counts;
        //std::vector<bool> bit_array;
        size_t size;
        int num_hashes;
        mutable std::shared_mutex mtx;

    public:
        BloomFilter(size_t s, int h);
        void add(const std::string& item);
        void remove(const std::string& item);
        bool contains(const std::string& item) const;

};

#endif