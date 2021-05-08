package search.array;

public class BinarySearch {
    public int search(int[] nums, int target) {
        int start = 0;
        int end = nums.length - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (target == nums[middle]) {
                return middle;
            }

            if (target < nums[middle]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return -1;
    }
}
