public final class Solution {
    public int orangesRotting(int[][] grid) {
        if (grid.length == 0 || grid[0].length == 0) return 0;
        int rows = grid.length;
        int columns = grid[0].length;
        int[][] state = new int[rows][];
        int[] queue = new int[rows * columns];
        int head = 0;
        int tail = 0;
        int fresh = 0;
        for (int r = 0; r < rows; r++) {
            state[r] = grid[r].clone();
            for (int c = 0; c < columns; c++) {
                if (state[r][c] == 2) queue[tail++] = r * columns + c;
                if (state[r][c] == 1) fresh++;
            }
        }
        int minutes = 0;
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};
        while (head < tail && fresh > 0) {
            int layerEnd = tail; // Newly rotten cells spread only next minute.
            while (head < layerEnd) {
                int cell = queue[head++];
                for (int direction = 0; direction < 4; direction++) {
                    int nr = cell / columns + dr[direction];
                    int nc = cell % columns + dc[direction];
                    if (nr < 0 || nr >= rows || nc < 0 || nc >= columns) continue;
                    if (state[nr][nc] == 1) {
                        state[nr][nc] = 2;
                        fresh--;
                        queue[tail++] = nr * columns + nc;
                    }
                }
            }
            minutes++;
        }
        return fresh == 0 ? minutes : -1;
    }
}
