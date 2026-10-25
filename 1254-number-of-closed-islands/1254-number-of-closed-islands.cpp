class Solution {
public:
    void dfs(int r, int c, vector<vector<int>>& grid, int& closed) {
        int n = grid.size();
        int m = grid[0].size();

        if (r < 0 || c < 0 || r >= n || c >= m) {
            closed = 0;
            return;
        }

        if (grid[r][c] == 1) return;

        grid[r][c] = 1;

        dfs(r - 1, c, grid, closed);
        dfs(r + 1, c, grid, closed);
        dfs(r, c - 1, grid, closed);
        dfs(r, c + 1, grid, closed);
    }

    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    int closed = 1;
                    dfs(i, j, grid, closed);

                    if (closed == 1) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};