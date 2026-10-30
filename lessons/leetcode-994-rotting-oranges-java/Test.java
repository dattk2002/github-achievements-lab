import java.util.Arrays;
import java.util.Random;

public final class Test {
    private static int[][] copy(int[][] grid) {
        return Arrays.stream(grid).map(int[]::clone).toArray(int[][]::new);
    }

    private static void check(int[][] grid, int expected) {
        int[][] before = copy(grid);
        int actual = new Solution().orangesRotting(grid);
        if (actual != expected || !Arrays.deepEquals(grid, before)) {
            throw new AssertionError("Expected " + expected + ", got " + actual
                    + " on " + Arrays.deepToString(before) + "; input must stay unchanged");
        }
    }

    // Independent oracle: update a whole copied grid synchronously each minute.
    private static int oracle(int[][] source) {
        int[][] grid = copy(source);
        for (int minute = 0; ; minute++) {
            boolean fresh = false;
            boolean changed = false;
            int[][] next = copy(grid);
            for (int r = 0; r < grid.length; r++) {
                for (int c = 0; c < grid[r].length; c++) {
                    if (grid[r][c] != 1) continue;
                    fresh = true;
                    if ((r > 0 && grid[r - 1][c] == 2)
                            || (r + 1 < grid.length && grid[r + 1][c] == 2)
                            || (c > 0 && grid[r][c - 1] == 2)
                            || (c + 1 < grid[r].length && grid[r][c + 1] == 2)) {
                        next[r][c] = 2;
                        changed = true;
                    }
                }
            }
            if (!fresh) return minute;
            if (!changed) return -1;
            grid = next;
        }
    }

    public static void main(String[] args) {
        check(new int[][] {{2, 1, 1, 1, 2}}, 2);
        check(new int[][] {{2, 1, 1, 1}}, 3);
        check(new int[][] {{2, 0}, {0, 1}}, -1);
        check(new int[][] {{1}}, -1);
        check(new int[][] {{2}}, 0);
        check(new int[][] {{0, 0}}, 0);
        check(new int[0][0], 0);
        check(new int[1][0], 0);
        check(new int[][] {{2}, {1}, {1}}, 2);
        Random random = new Random(994);
        for (int trial = 0; trial < 1000; trial++) {
            int[][] grid = new int[1 + random.nextInt(5)][1 + random.nextInt(5)];
            for (int[] row : grid) {
                for (int c = 0; c < row.length; c++) row[c] = random.nextInt(3);
            }
            check(grid, oracle(grid));
        }
        int[][] large = new int[10][10];
        for (int[] row : large) Arrays.fill(row, 1);
        large[0][0] = 2;
        check(large, 18);
        large[9][9] = 2;
        check(large, 9);
        System.out.println("rotting oranges: all cases passed (1000 random grids)");
    }
}
