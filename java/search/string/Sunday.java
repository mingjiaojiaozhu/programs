package search.string;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Sunday {
    public int search(String text, String pattern) {
        List<Character> aux = Arrays.asList(text.chars().mapToObj(c -> (char) c).toArray(Character[]::new));
        int maxValue = Collections.max(aux);
        int minValue = Collections.min(aux);
        int[] next = getNext(pattern, maxValue - minValue + 1, minValue);

        int index = 0;
        while (index <= text.length() - pattern.length()) {
            int patternIndex = 0;
            while (text.charAt(index + patternIndex) == pattern.charAt(patternIndex)) {
                ++patternIndex;
                if (patternIndex == pattern.length()) {
                    return index;
                }
            }

            if (index == text.length() - pattern.length()) {
                return -1;
            }
            index += next[text.charAt(index + pattern.length()) - minValue];
        }
        return -1;
    }

    private int[] getNext(String text, int nextSize, int minValue) {
        int[] next = new int[nextSize];
        Arrays.fill(next, text.length() + 1);
        for (int i = 0; i < text.length(); ++i) {
            int index = text.charAt(i) - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = text.length() - i;
            }
        }
        return next;
    }
}
