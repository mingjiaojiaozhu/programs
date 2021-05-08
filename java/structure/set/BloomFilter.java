package structure.set;

import java.util.Arrays;

public class BloomFilter {
    private static final int[] _seeds = {2, 3, 5};
    private char[] _hash = new char[65536];

    public BloomFilter() {
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

    public void add(String text) {
        for (int seed : _seeds) {
            int value = getHashCode(text, seed);
            int index = value >> 3;
            if (index >= 0 && index < 65536) {
                _hash[index] |= 1 << (value & 7);
            }
        }
    }

    public boolean contains(String text) {
        for (int seed : _seeds) {
            int value = getHashCode(text, seed);
            int index = value >> 3;
            if (index < 0 || index >= 65536 || 0 == (_hash[index] & (1 << (value & 7)))) {
                return false;
            }
        }
        return true;
    }

    public void clear() {
        Arrays.fill(_hash, '\0');
    }

    private int getHashCode(String text, int seed) {
        int code = 0;
        for (char value : text.toCharArray()) {
            code = seed * code + value - 'a';
        }
        return code;
    }
}
