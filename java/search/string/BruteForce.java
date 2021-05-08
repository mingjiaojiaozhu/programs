package search.string;

public class BruteForce {
    public int search(String text, String pattern) {
        int index = 0;
        int patternIndex = 0;
        while (index < text.length()) {
            if (text.charAt(index) != pattern.charAt(patternIndex)) {
                index += 1 - patternIndex;
                patternIndex = 0;
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
}
