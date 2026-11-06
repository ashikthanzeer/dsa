#include <stdio.h>
#include <limits.h>

#define MAX 100

int dist[MAX][MAX], visited[MAX][MAX];
int parentX[MAX][MAX], parentY[MAX][MAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    int r, c, sx, sy, dxn, dyn;
    char grid[MAX][MAX];

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter grid (S=start, D=destination, #=wall, .=free):\n");

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &grid[i][j]);

            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }

            if (grid[i][j] == 'D') {
                dxn = i;
                dyn = j;
            }

            dist[i][j] = INT_MAX;
            visited[i][j] = 0;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }
    }

    dist[sx][sy] = 0;

    while (1) {
        int x = -1, y = -1, min = INT_MAX;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (!visited[i][j] && dist[i][j] < min) {
                    min = dist[i][j];
                    x = i;
                    y = j;
                }
            }
        }

        if (x == -1)
            break;

        if (x == dxn && y == dyn)
            break;

        visited[x][y] = 1;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < r && ny >= 0 && ny < c &&
                grid[nx][ny] != '#' && !visited[nx][ny]) {

                if (dist[x][y] + 1 < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    parentX[nx][ny] = x;
                    parentY[nx][ny] = y;
                }
            }
        }
    }

    if (dist[dxn][dyn] == INT_MAX) {
        printf("No path exists!\n");
    } else {
        printf("Minimum distance: %d units\n",
               dist[dxn][dyn]);

        int x = dxn, y = dyn;

        while (x != sx || y != sy) {
            if (grid[x][y] == '.')
                grid[x][y] = '*';

            int px = parentX[x][y];
            int py = parentY[x][y];

            x = px;
            y = py;
        }

        printf("Shortest path (*):\n");

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                printf("%c ", grid[i][j]);
            printf("\n");
        }
    }

    return 0;
}