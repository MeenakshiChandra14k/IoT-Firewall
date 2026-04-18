#include "../include/BloomFilter.h"
#include <iostream>
#include <cassert>
#include <vector>

void test_accuracy() {
    BloomFilter bf(10000, 7);

    std::string ip = "1.2.3.4";
    bf.add(ip);
    assert(bf.contains(ip) == true);
    std::cout << "Test 1 Passed: Zero false negatives." << std::endl;

    int false_positives = 0;
    int test_count = 1000;

    for(int i=0; i < test_count; i++){
        std::string test_ip = "200.0.0." + std::to_string(i);
        if(bf.contains(test_ip)){
            false_positives++;
        }
    }

    double rate = (double)false_positives / test_count * 100 ;
    std::cout << "Test 2 : False Positives Rate is " << rate << "%" << std::endl;
    assert(rate < 5.0);

}

int main(){
    try {
        test_accuracy();
        std::cout << "\nALL TESTS PASSED SUCCESSFULY!" << std::endl;
    } catch(...) {
        std::cerr << "Tests failed!" << std::endl;
        return 1;
    }

    return 0;
}