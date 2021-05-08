package structure.set;

import java.util.HashMap;
import java.util.Map;

public class LRUCache {
    private Map<Integer, HashNode> _hash = new HashMap<>();
    private HashNode _head = new HashNode(0, 0);
    private HashNode _tail = new HashNode(0, 0);

    public LRUCache() {
        _head.next = _tail;
        _tail.prev = _head;
    }

    public boolean isEmpty() {
        return _hash.isEmpty();
    }

    public void set(int key, int value) {
        if (_hash.containsKey(key)) {
            erase(_hash.get(key));
            _hash.put(key, new HashNode(key, value));
            add(_hash.get(key));
            return;
        }

        if (_hash.size() >= 64) {
            HashNode node = _head.next;
            erase(node);
            _hash.remove(node.key);
        }

        HashNode node = new HashNode(key, value);
        _hash.put(key, node);
        add(node);
    }

    public int get(int key) {
        if (_hash.containsKey(key)) {
            HashNode node = _hash.get(key);
            erase(node);
            add(node);
            return node.value;
        }
        return Integer.MIN_VALUE;
    }

    public void clear() {
        _hash.clear();
        _head.next = _tail;
        _tail.prev = _head;
    }

    private void add(HashNode node) {
        HashNode prev = _tail.prev;
        node.prev = prev;
        node.next = _tail;
        prev.next = node;
        _tail.prev = node;
    }

    private void erase(HashNode node) {
        HashNode prev = node.prev;
        HashNode next = node.next;
        prev.next = next;
        next.prev = prev;
    }

    private class HashNode {
        public int key = 0;
        public int value = 0;
        public HashNode prev = null;
        public HashNode next = null;

        public HashNode(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }
}
