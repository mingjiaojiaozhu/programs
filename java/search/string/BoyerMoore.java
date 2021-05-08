package search.string;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class BoyerMoore {
    public int search(String text, String pattern) {
        List<Character> aux = Arrays.asList(text.chars().mapToObj(c -> (char) c).toArray(Character[]::new));
        int maxValue = Collections.max(aux);
        int minValue = Collections.min(aux);
        int[] nextBadChar = getNextBadChar(pattern, maxValue - minValue + 1, minValue);
        int[] nextGoodSuffix = getNextGoodSuffix(pattern);

        int index = 0;
        while (index <= text.length() - pattern.length()) {
            int patternIndex = pattern.length() - 1;
            while (text.charAt(index + patternIndex) == pattern.charAt(patternIndex)) {
                --patternIndex;
                if (patternIndex < 0) {
                    return index;
                }
            }
            index += Math.max(patternIndex - nextBadChar[text.charAt(index + patternIndex) - minValue], nextGoodSuffix[patternIndex]);
        }
        return -1;
    }

    private int[] getNextBadChar(String text, int nextSize, int minValue) {
        int[] next = new int[nextSize];
        Arrays.fill(next, 0);
        for (int i = 0; i < text.length(); ++i) {
            int index = text.charAt(i) - minValue;
            if (index >= 0 && index < nextSize) {
                next[index] = i;
            }
        }
        return next;
    }

    private int[] getNextGoodSuffix(String text) {
        int[] aux = new int[text.length()];
        Arrays.fill(aux, 0);
        aux[text.length() - 1] = text.length();

        int start = 0;
        int end = text.length() - 1;
        for (int i = text.length() - 2; i >= 0; --i) {
            if (i > end && aux[i + text.length() - 1 - start] < i - end) {
                aux[i] = aux[i + text.length() - 1 - start];
                continue;
            }

            if (i < end) {
                end = i;
            }
            start = i;
            while (end >= 0 && text.charAt(end) == text.charAt(end + text.length() - 1 - start)) {
                --end;
                aux[i] = start - end;
            }
        }

        int[] next = new int[text.length()];
        Arrays.fill(next, text.length());
        for (int i = text.length() - 1; i >= 0; --i) {
            if (aux[i] != i + 1) {
                continue;
            }

            for (int j = 0; j < text.length() - i; ++j) {
                if (next[j] == text.length()) {
                    next[j] = text.length() - i - 1;
                }
            }
        }

        for (int i = 0; i < text.length() - 1; ++i) {
            next[text.length() - 1 - aux[i]] = text.length() - i - 1;
        }
        return next;
    }
}
