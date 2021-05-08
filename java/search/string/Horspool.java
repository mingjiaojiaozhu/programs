package search.string;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Horspool {
    public int search(String text, String pattern) {
        List<Character> aux = Arrays.asList(text.chars().mapToObj(c -> (char) c).toArray(Character[]::new));
        int maxValue = Collections.max(aux);
        int minValue = Collections.min(aux);
        int[] next = getNext(pattern, maxValue - minValue + 1, minValue);

        int index = 0;
        while (index <= text.length() - pattern.length()) {
            int patternIndex = pattern.length() - 1;
            while (text.charAt(index + patternIndex) == pattern.charAt(patternIndex)) {
                --patternIndex;
                if (patternIndex < 0) {
                    return index;
                }
            }
            index += next[text.charAt(index + pattern.length() - 1) - minValue];
        }
        return -1;
    }

    private int[] getNext(String text, int nextSize, int minValue) {
        int[] next = new int[nextSize];
        Arrays.fill(next, text.length());
        for (int i = 0; i < text.length() - 1; ++i) {
            int index = text.charAt(i) - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = text.length() - i - 1;
            }
        }
        return next;
    }
}
