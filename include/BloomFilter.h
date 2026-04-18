
#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>
#include <functional>

class BloomFilter {
    private:
        std::vector<bool> bit_array;
        size_t size;
        int num_hashes;

    public:
        BloomFilter(size_t s, int h);
        void add(const std::string& item);
        bool contains(const std::string& item) const;

};

#endif