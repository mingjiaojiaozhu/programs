package classic.dynamic_programming;

import java.util.Arrays;

public class LongestCommonSubsequence {
    public int solution(String text1, String text2) {
        int[][] result = new int[text1.length() + 1][text2.length() + 1];
        for (int i = 0; i <= text1.length(); ++i) {
            Arrays.fill(result[i], 0);
        }
        for (int i = 1; i <= text1.length(); ++i) {
            for (int j = 1; j <= text2.length(); ++j) {
                result[i][j] = (text1.charAt(i - 1) == text2.charAt(j - 1)) ? result[i - 1][j - 1] + 1 : Math.max(result[i - 1][j], result[i][j - 1]);
            }
        }
        return result[result.length - 1][result[0].length - 1];
    }
}
