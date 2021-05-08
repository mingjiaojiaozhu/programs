package classic.dynamic_programming;

import java.util.Arrays;

public class LongestPalindromicSubstring {
    public String solution(String text) {
        boolean[][] aux = new boolean[text.length()][text.length()];
        for (int i = 0; i < text.length(); ++i) {
            Arrays.fill(aux[i], false);
            aux[i][i] = true;
        }

        int start = 0;
        int size = 1;
        for (int i = 1; i < text.length(); ++i) {
            for (int j = 0; j < text.length() - i; ++j) {
                int index = i + j;
                aux[j][index] = (1 == i) ? (text.charAt(j) == text.charAt(index)) : (text.charAt(j) == text.charAt(index) && aux[j + 1][index - 1]);
                if (aux[j][index] && size < i + 1) {
                    start = j;
                    size = i + 1;
                }
            }
        }
        return text.substring(start, start + size);
    }
}
