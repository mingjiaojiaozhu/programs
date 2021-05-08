#include <iostream>
#include <vector>
using namespace std;

class BitMap {
public:
    BitMap() : hash(vector<char>(65536, 0x00)) {}

    bool isEmpty() {
        for (char value : hash) {
            if (value) {
                return false;
            }
        }
        return true;
    }

    void add(int value) {
        int index = value >> 3;
        if (index >=0 && index < 65536) {
            hash[index] |= 1 << (value & 7);
        }
    }

    void erase(int value) {
        int index = value >> 3;
        if (index >=0 && index < 65536) {
            hash[index] &= ~(1 << (value & 7));
        }
    }

    bool contains(int value) {
        int index = value >> 3;
        if (index >=0 && index < 65536) {
            return 0 != (hash[index] & (1 << (value & 7)));
        }
        return false;
    }

    void clear() {
        hash.assign(65536, 0x00);
    }

private:
    vector<char> hash;
};
