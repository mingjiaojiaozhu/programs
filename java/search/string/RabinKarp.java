package search.string;

public class RabinKarp {
    public int search(String text, String pattern) {
        int code = getHashCode(text, pattern.length());
        int patternCode = getHashCode(pattern, pattern.length());
        for (int i = 0; i <= text.length() - pattern.length(); ++i) {
            if (code == patternCode) {
                int index = i;
                int patternIndex = 0;
                while (index < text.length()) {
                    if (text.charAt(index) != pattern.charAt(patternIndex)) {
                        break;
                    }

                    if (patternIndex == pattern.length() - 1) {
                        return index - patternIndex;
                    }
                    ++index;
                    ++patternIndex;
                }
            }

            if (i < text.length() - pattern.length()) {
                code += text.charAt(i + pattern.length()) - text.charAt(i);
            }
        }
        return -1;
    }

    private int getHashCode(String text, int length) {
        int code = 0;
        for (int i = 0; i < length; ++i) {
            code += text.charAt(i) - 'a';
        }
        return code;
    }
}
