package structure.set.hash;

public class HashOfChainAddress {
    private HashNode[] _hash = new HashNode[64];

    public HashOfChainAddress() {
        for (int i = 0; i < 64; ++i) {
            _hash[i] = new HashNode(0, 0);
        }
    }

    public boolean isEmpty() {
        for (HashNode node : _hash) {
            if (null != node.next) {
                return false;
            }
        }
        return true;
    }

    public void add(int key, int value) {
        HashNode current = _hash[key % 64];
        while (null != current.next) {
            current = current.next;
            if (key == current.key) {
                current.value = value;
                return;
            }
        }
        current.next = new HashNode(key, value);
    }

    public void erase(int key) {
        HashNode current = _hash[key % 64];
        while (null != current.next) {
            if (key == current.next.key) {
                current.next = current.next.next;
                return;
            }
            current = current.next;
        }
    }

    public void set(int key, int value) {
        HashNode current = _hash[key % 64].next;
        while (null != current && key != current.key) {
            current = current.next;
        }

        if (null != current) {
            current.value = value;
        }
    }

    public int get(int key) {
        HashNode current = _hash[key % 64].next;
        while (null != current && key != current.key) {
            current = current.next;
        }

        if (null != current) {
            return current.value;
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        for (HashNode node : _hash) {
            node.next = null;
        }
    }

    private class HashNode {
        public int key = 0;
        public int value = 0;
        public HashNode next = null;

        public HashNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
