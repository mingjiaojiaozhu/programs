package sort.array;

public class MergeSort {
    public void sort(int[] nums) {
        int[] aux = nums.clone();
        sort(nums, aux, 0, nums.length - 1);
    }

    private void sort(int[] nums, int[] aux, int start, int end) {
        if (start >= end) {
            return;
        }

        int middle = start + ((end - start) >> 1);
        sort(aux, nums, start, middle);
        sort(aux, nums, middle + 1, end);

        if (aux[middle] > aux[middle + 1]) {
            merge(nums, aux, start, middle, end);
        } else {
            System.arraycopy(aux, start, nums, start, end - start + 1);
        }
    }

    private void merge(int[] nums, int[] aux, int start, int middle, int end) {
        int index = start;
        int left = start;
        int right = middle + 1;
        while (left <= middle && right <= end) {
            if (aux[left] > aux[right]) {
                nums[index] = aux[right];
                ++right;
            } else {
                nums[index] = aux[left];
                ++left;
            }
            ++index;
        }

        if (left <= middle) {
            System.arraycopy(aux, left, nums, index, middle - left + 1);
        }
        if (right <= end) {
            System.arraycopy(aux, right, nums, index, end - right + 1);
        }
    }
}
