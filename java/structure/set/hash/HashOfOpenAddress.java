package structure.set.hash;

public class HashOfOpenAddress {
    private HashNode[] _hash = new HashNode[256];

    public HashOfOpenAddress() {
        for (int i = 0; i < 256; ++i) {
            _hash[i] = new HashNode(0, 0);
        }
    }

    public boolean isEmpty() {
        for (HashNode node : _hash) {
            if (node.used) {
                return false;
            }
        }
        return true;
    }

    public void add(int key, int value) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode current = _hash[index];
            if (current.used && key == current.key) {
                current.value = value;
                return;
            }

            if (!current.used) {
                current.key = key;
                current.value = value;
                current.used = true;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    public void erase(int key) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode current = _hash[index];
            if (current.used && key == current.key) {
                current.key = 0;
                current.value = 0;
                current.used = false;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    public void set(int key, int value) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode current = _hash[index];
            if (current.used && key == current.key) {
                current.value = value;
                return;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
    }

    public int get(int key) {
        int index = key % 256;
        for (int i = 0; i < 256; ++i) {
            HashNode current = _hash[index];
            if (current.used && key == current.key) {
                return current.value;
            }

            ++index;
            if (index >= 256) {
                index = 0;
            }
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        for (HashNode node : _hash) {
            node.key = 0;
            node.value = 0;
            node.used = false;
        }
    }

    private class HashNode {
        public int key = 0;
        public int value = 0;
        public boolean used = false;

        public HashNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
