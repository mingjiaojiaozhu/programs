package search.array;

public class JumpSearch {
    public int search(int[] nums, int target) {
        int step = (int) Math.sqrt(nums.length);
        int border = step;
        while (border < nums.length && target > nums[border]) {
            border += step;
        }

        for (int i = border - step; i < Math.min(border + 1, nums.length); ++i) {
            if (target == nums[i]) {
                return i;
            }
        }
        return -1;
    }
}
