package structure.set;

import java.util.Arrays;

public class BitMap {
    private char[] _hash = new char[65536];

    public BitMap() {
        Arrays.fill(_hash, '\0');
    }

    public boolean isEmpty() {
        for (char value : _hash) {
            if ('\0' != value) {
                return false;
            }
        }
        return true;
    }

    public void add(int value) {
        int index = value >> 3;
        if (index >= 0 && index < 65536) {
            _hash[index] |= 1 << (value & 7);
        }
    }

    public void erase(int value) {
        int index = value >> 3;
        if (index >= 0 && index < 65536) {
            _hash[index] &= ~(1 << (value & 7));
        }
    }

    public boolean contains(int value) {
        int index = value >> 3;
        if (index >= 0 && index < 65536) {
            return 0 != (_hash[index] & (1 << (value & 7)));
        }
        return false;
    }

    public void clear() {
        Arrays.fill(_hash, '\0');
    }
}
