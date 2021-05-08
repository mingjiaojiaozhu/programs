package sort.string;

public class QuickSort {
    public void sort(String[] texts) {
        sort(texts, 0, texts.length - 1, 0);
    }

    private void sort(String[] texts, int start, int end, int digit) {
        if (start >= end) {
            return;
        }

        int pivot = getChar(texts[start], digit);
        int left = start;
        int right = end;
        int index = start + 1;
        while (index <= right) {
            int value = getChar(texts[index], digit);
            if (pivot == value) {
                ++index;
                continue;
            }

            if (value < pivot) {
                swap(texts, index, left);

                ++index;
                ++left;
            } else {
                swap(texts, index, right);
                --right;
            }
        }

        sort(texts, start, left - 1, digit);
        if (0 != ~pivot) {
            sort(texts, left, right, digit + 1);
        }
        sort(texts, right + 1, end, digit);
    }

    private int getChar(String text, int digit) {
        if (text.length() <= digit) {
            return -1;
        }
        return text.charAt(digit);
    }

    private void swap(String[] texts, int i, int j) {
        String aux = texts[i];
        texts[i] = texts[j];
        texts[j] = aux;
    }
}
