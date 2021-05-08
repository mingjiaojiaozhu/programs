#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BloomFilter {
public:
    BloomFilter() : hash(vector<char>(65536, 0x00)) {
        int aux[3] = {2, 3, 5};
        seeds.assign(aux, aux + 3);
    }

    bool isEmpty() {
        for (char value : hash) {
            if (value) {
                return false;
            }
        }
        return true;
    }

    void add(string text) {
        for (int seed : seeds) {
            int value = getHashCode(text, seed);
            int index = value >> 3;
            if (index >= 0 && index < 65536) {
                hash[index] |= 1 << (value & 7);
            }
        }
    }

    bool contains(string text) {
        for (int seed : seeds) {
            int value = getHashCode(text, seed);
            int index = value >> 3;
            if (index < 0 || index >= 65536 || !(hash[index] & (1 << (value & 7)))) {
                return false;
            }
        }
        return true;
    }

    void clear() {
        hash.assign(65536, 0x00);
    }

private:
    vector<int> seeds;
    vector<char> hash;

    int getHashCode(string text, int seed) {
        int code = 0;
        for (char value : text) {
            code = seed * code + value - 'a';
        }
        return code;
    }
};
