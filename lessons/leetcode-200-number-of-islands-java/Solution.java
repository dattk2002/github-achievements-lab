public final class Solution {
    public int numIslands(char[][] grid) {
        if (grid.length == 0 || grid[0].length == 0) return 0;
        int rows = grid.length;
        int columns = grid[0].length;
        boolean[] visited = new boolean[rows * columns];
        int[] queue = new int[rows * columns];
        int islands = 0;
        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                int start = r * columns + c;
                if (grid[r][c] != '1' || visited[start]) continue;
                islands++;
                int head = 0;
                int tail = 0;
                queue[tail++] = start;
                visited[start] = true;
                while (head < tail) {
                    int cell = queue[head++];
                    for (int direction = 0; direction < 4; direction++) {
                        int nr = cell / columns + dr[direction];
                        int nc = cell % columns + dc[direction];
                        if (nr < 0 || nr >= rows || nc < 0 || nc >= columns) continue;
                        int next = nr * columns + nc;
                        if (grid[nr][nc] == '1' && !visited[next]) {
                            visited[next] = true; // Mark on enqueue, not dequeue.
                            queue[tail++] = next;
                        }
                    }
                }
            }
        }
        return islands;
    }
}
