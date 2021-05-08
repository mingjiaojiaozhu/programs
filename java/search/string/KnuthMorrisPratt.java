package search.string;

import java.util.Arrays;

public class KnuthMorrisPratt {
    public int search(String text, String pattern) {
        int[] next = getNext(pattern);

        int index = 0;
        int patternIndex = 0;
        while (index < text.length()) {
            if (patternIndex > 0 && text.charAt(index) != pattern.charAt(patternIndex)) {
                ++index;
                patternIndex = next[patternIndex - 1];
                continue;
            }

            if (patternIndex == pattern.length() - 1) {
                return index - patternIndex;
            }
            ++index;
            ++patternIndex;
        }
        return -1;
    }

    private int[] getNext(String text) {
        int[] next = new int[text.length()];
        Arrays.fill(next, 0);

        int fast = 1;
        int slow = 0;
        while (fast < text.length()) {
            if (0 != slow && text.charAt(fast) != text.charAt(slow)) {
                slow = next[slow - 1];
                continue;
            }

            if (text.charAt(fast) == text.charAt(slow)) {
                ++slow;
            }
            next[fast] = slow;
            ++fast;
        }
        return next;
    }
}
