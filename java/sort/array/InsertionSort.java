package sort.array;

public class InsertionSort {
    public void sort(int[] nums) {
        for (int i = 1; i < nums.length; ++i) {
            int pivot = nums[i];
            if (pivot >= nums[i - 1]) {
                continue;
            }

            int start = 0;
            int end = i - 1;
            while (start <= end) {
                int middle = start + ((end - start) >> 1);
                if (pivot < nums[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            }

            for (int j = i - 1; j >= start; --j) {
                nums[j + 1] = nums[j];
            }
            nums[start] = pivot;
        }
    }
}
