package sort.string;

import java.util.Arrays;

public class MSDRadixSort {
    public void sort(String[] texts) {
        String[] aux = new String[texts.length];
        Arrays.fill(aux, "");
        sort(texts, aux, 0, texts.length - 1, 0);
    }

    private void sort(String[] texts, String[] aux, int start, int end, int digit) {
        if (start >= end) {
            return;
        }

        int maxValue = getChar(texts[start], digit);
        int minValue = getChar(texts[start], digit);
        for (int i = start + 1; i <= end; ++i) {
            int value = getChar(texts[i], digit);
            if (0 == ~value) {
                continue;
            }

            if (maxValue < value) {
                maxValue = value;
            }
            if (0 == ~minValue || minValue > value) {
                minValue = value;
            }
        }

        int size = maxValue - minValue + 1;
        int[] buckets = new int[size + 2];
        Arrays.fill(buckets, 0);
        for (int i = start; i <= end; ++i) {
            int value = getChar(texts[i], digit);
            ++buckets[(0 == ~value) ? 1 : value - minValue + 2];
        }
        for (int i = 1; i < size + 2; ++i) {
            buckets[i] += buckets[i - 1];
        }

        for (int i = start; i <= end; ++i) {
            int value = getChar(texts[i], digit);
            int index = (0 == ~value) ? 0 : value - minValue + 1;
            aux[buckets[index]] = texts[i];
            ++buckets[index];
        }
        System.arraycopy(aux, 0, texts, start, end - start + 1);

        for (int i = 0; i < size; ++i) {
            sort(texts, aux, start + buckets[i], start + buckets[i + 1] - 1, digit + 1);
        }
    }

    private int getChar(String text, int digit) {
        if (text.length() <= digit) {
            return -1;
        }
        return text.charAt(digit);
    }
}
