package structure.tree;

public class SegmentTree {
    private TreeNode[] _nodes = null;
    private int _length = 0;

    public SegmentTree(int[] nums) {
        _nodes = new TreeNode[nums.length << 2];
        for (int i = 0; i < (nums.length << 2); ++i) {
            _nodes[i] = new TreeNode();
        }
        _length = nums.length;
        createNode(nums, 0, nums.length - 1, 0);
    }

    public void set(int index, int value) {
        if (index >= 0 && index < _length) {
            setNode(index, value, 0);
        }
    }

    public void setInterval(int start, int end, int value) {
        if (start >= 0 && start < _length && end >= 0 && end < _length) {
            setNodes(start, end, value, 0);
        }
    }

    public int get(int index) {
        if (index >= 0 && index < _length) {
            return getNodes(index, index, 0);
        }
        return Integer.MIN_VALUE;
    }

    public int getInterval(int start, int end) {
        if (start >= 0 && start < _length && end >= 0 && end < _length) {
            return getNodes(start, end, 0);
        }
        return Integer.MIN_VALUE;
    }

    private void createNode(int[] nums, int start, int end, int parent) {
        _nodes[parent].start = start;
        _nodes[parent].end = end;
        if (start == end) {
            _nodes[parent].value = nums[start];
            return;
        }

        int middle = start + ((end - start) >> 1);
        int child = (parent << 1) + 1;
        createNode(nums, start, middle, child);
        createNode(nums, middle + 1, end, child + 1);
        _nodes[parent].value = _nodes[child].value + _nodes[child + 1].value;
    }

    private void setNode(int index, int value, int parent) {
        if (_nodes[parent].start == _nodes[parent].end) {
            _nodes[parent].value = value;
            return;
        }

        int middle = _nodes[parent].start + ((_nodes[parent].end - _nodes[parent].start) >> 1);
        int child = (parent << 1) + 1;
        if (index <= middle) {
            setNode(index, value, child);
        } else {
            setNode(index, value, child + 1);
        }
        _nodes[parent].value = _nodes[child].value + _nodes[child + 1].value;
    }

    private void setNodes(int start, int end, int value, int parent) {
        if (start == _nodes[parent].start && end == _nodes[parent].end) {
            _nodes[parent].value += (end - start + 1) * value;
            _nodes[parent].covered += value;
            return;
        }

        int middle = _nodes[parent].start + ((_nodes[parent].end - _nodes[parent].start) >> 1);
        int child = (parent << 1) + 1;
        if (end <= middle) {
            setNodes(start, end, value, child);
        } else if (start > middle) {
            setNodes(start, end, value, child + 1);
        } else {
            setNodes(start, middle, value, child);
            setNodes(middle + 1, end, value, child + 1);
        }
        _nodes[parent].value = _nodes[child].value + _nodes[child + 1].value;
    }

    private int getNodes(int start, int end, int parent) {
        if (0 != _nodes[parent].covered) {
            if (_nodes[parent].start != _nodes[parent].end) {
                int child = (parent << 1) + 1;
                int covered = _nodes[parent].covered;
                _nodes[child].covered += covered;
                _nodes[child + 1].covered += covered;
                if (0 != covered) {
                    _nodes[child].value += (_nodes[child].end - _nodes[child].start + 1) * covered;
                    _nodes[child + 1].value += (_nodes[child + 1].end - _nodes[child + 1].start + 1) * covered;
                }
            }
            _nodes[parent].covered = 0;
        }

        if (start == _nodes[parent].start && end == _nodes[parent].end) {
            return _nodes[parent].value;
        }

        int middle = _nodes[parent].start + ((_nodes[parent].end - _nodes[parent].start) >> 1);
        int child = (parent << 1) + 1;
        if (end <= middle) {
            return getNodes(start, end, child);
        }
        if (start > middle) {
            return getNodes(start, end, child + 1);
        }
        return getNodes(start, middle, child) + getNodes(middle + 1, end, child + 1);
    }

    private class TreeNode {
        public int start = 0;
        public int end = 0;
        public int value = 0;
        public int covered = 0;
    }
}
