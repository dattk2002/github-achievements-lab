import java.util.Arrays;
import java.util.Random;

public final class Test {
    private static void check(char[][] grid, int expected) {
        char[][] before = Arrays.stream(grid).map(char[]::clone).toArray(char[][]::new);
        int actual = new Solution().numIslands(grid);
        if (actual != expected) {
            throw new AssertionError("Expected " + expected + ", got " + actual
                    + " for " + Arrays.deepToString(grid));
        }
        if (!Arrays.deepEquals(grid, before)) {
            throw new AssertionError("Input grid was modified");
        }
    }

    private static char[][] rows(String... values) {
        return Arrays.stream(values).map(String::toCharArray).toArray(char[][]::new);
    }

    // Independent oracle: merge component labels, without a traversal queue.
    private static int oracle(char[][] grid) {
        if (grid.length == 0) return 0;
        int columns = grid[0].length;
        int[] label = new int[grid.length * columns];
        Arrays.fill(label, -1);
        int count = 0;
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < columns; c++) {
                if (grid[r][c] != '1') continue;
                int index = r * columns + c;
                label[index] = index;
                count++;
                int[] neighbors = {r > 0 ? index - columns : -1, c > 0 ? index - 1 : -1};
                for (int neighbor : neighbors) {
                    if (neighbor < 0 || label[neighbor] < 0) continue;
                    int from = label[index];
                    int to = label[neighbor];
                    if (from == to) continue;
                    for (int i = 0; i <= index; i++) {
                        if (label[i] == from) label[i] = to;
                    }
                    count--;
                }
            }
        }
        return count;
    }

    public static void main(String[] args) {
        check(rows(), 0);
        check(rows(""), 0);
        check(rows("0"), 0);
        check(rows("1"), 1);
        check(rows("101", "010", "101"), 5); // Diagonals do not connect.
        check(rows("11001", "01001", "00110"), 3);
        check(rows("10101"), 3);
        check(rows("1", "0", "1"), 2);
        Random random = new Random(200);
        for (int trial = 0; trial < 1000; trial++) {
            char[][] grid = new char[1 + random.nextInt(8)][1 + random.nextInt(8)];
            for (char[] row : grid) {
                for (int c = 0; c < row.length; c++) row[c] = random.nextBoolean() ? '1' : '0';
            }
            check(grid, oracle(grid));
        }
        char[][] large = new char[300][300];
        for (char[] row : large) Arrays.fill(row, '1');
        check(large, 1); // Recursive flood fill risks overflowing the call stack.
        for (int r = 0; r < 300; r++) {
            for (int c = 0; c < 300; c++) large[r][c] = (r + c) % 2 == 0 ? '1' : '0';
        }
        check(large, 45_000);
        System.out.println("number of islands: all cases passed (including 1000 randomized grids)");
    }
}
