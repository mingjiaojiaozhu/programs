package other;

import java.util.Arrays;

public class Manacher {
    public String search(String text) {
        StringBuffer aux = new StringBuffer("|");
        for (char value : text.toCharArray()) {
            aux.append(value).append("|");
        }

        int border = 0;
        int middle = 0;
        int center = 0;
        int maxLength = 0;
        int[] buckets = new int[(text.length() << 1) + 1];
        Arrays.fill(buckets, 0);
        for (int i = 0; i < buckets.length; ++i) {
            if (i < border) {
                int index = (middle << 1) - i;
                buckets[i] = Math.min(buckets[index], border - i);
                if (i + buckets[index] < border) {
                    continue;
                }
            }

            int left = i - buckets[i] - 1;
            int right = i + buckets[i] + 1;
            while (left >= 0 && right < buckets.length) {
                if (aux.charAt(left) != aux.charAt(right)) {
                    break;
                }
                ++buckets[i];

                --left;
                ++right;
            }

            border = buckets[i] + i;
            middle = i;
            if (maxLength < buckets[i]) {
                maxLength = buckets[i];
                center = i;
            }
        }

        StringBuffer result = new StringBuffer();
        for (int i = center - maxLength; i <= center + maxLength; ++i) {
            char value = aux.charAt(i);
            if ('|' != value) {
                result.append(value);
            }
        }
        return result.toString();
    }
}
