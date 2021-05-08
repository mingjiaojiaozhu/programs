package sort.string;

import java.util.Arrays;

public class LSDRadixSort {
    public void sort(String[] texts) {
        String[] aux = new String[texts.length];
        Arrays.fill(aux, "");
        for (int i = texts[0].length() - 1; i >= 0; --i) {
            int maxValue = texts[0].charAt(i);
            int minValue = texts[0].charAt(i);
            for (int j = 1; j < texts.length; ++j) {
                int value = texts[j].charAt(i);
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
            int[] buckets = new int[size];
            Arrays.fill(buckets, 0);
            for (String value : texts) {
                ++buckets[value.charAt(i) - minValue];
            }
            for (int j = 1; j < size; ++j) {
                buckets[j] += buckets[j - 1];
            }

            for (int j = texts.length - 1; j >= 0; --j) {
                int index = texts[j].charAt(i) - minValue;
                aux[buckets[index] - 1] = texts[j];
                --buckets[index];
            }
            System.arraycopy(aux, 0, texts, 0, texts.length);
        }
    }
}
