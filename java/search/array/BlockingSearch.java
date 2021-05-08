package search.array;

public class BlockingSearch {
    public int search(int[] nums, int[][] blocks, int target) {
        int start = 0;
        int end = blocks.length - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (target <= blocks[middle][2]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }

        if (start >= blocks.length) {
            return -1;
        }

        for (int i = blocks[start][0]; i <= blocks[start][1]; ++i) {
            if (target == nums[i]) {
                return i;
            }
        }
        return -1;
    }
}
