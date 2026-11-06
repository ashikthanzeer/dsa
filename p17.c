#include <stdio.h>
#include <stdbool.h>

#define MAX 1000

typedef struct {
    int a, b, c, parent;
} State;

State q[MAX];
bool visited[11][8][5];

int main() {
    int front = 0, rear = 0, goal = -1;

    q[rear++] = (State){0, 7, 4, -1};
    visited[0][7][4] = true;

    while (front < rear) {
        int idx = front++;
        State s = q[idx];

        if (s.b == 2 || s.c == 2) {
            goal = idx;
            break;
        }

        int v[3] = {s.a, s.b, s.c};
        int cap[3] = {10, 7, 4};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j || v[i] == 0 || v[j] == cap[j])
                    continue;

                int n[3] = {v[0], v[1], v[2]};
                int pour = n[i] < cap[j] - n[j]
                           ? n[i] : cap[j] - n[j];

                n[i] -= pour;
                n[j] += pour;

                if (!visited[n[0]][n[1]][n[2]]) {
                    visited[n[0]][n[1]][n[2]] = true;
                    q[rear++] = (State){
                        n[0], n[1], n[2], idx
                    };
                }
            }
        }
    }

    if (goal == -1) {
        printf("No solution exists.\n");
        return 0;
    }

    int path[MAX], count = 0;

    while (goal != -1) {
        path[count++] = goal;
        goal = q[goal].parent;
    }

    printf("Sequence of states (10L, 7L, 4L):\n");

    for (int i = count - 1; i >= 0; i--)
        printf("(%d, %d, %d)\n",
               q[path[i]].a, q[path[i]].b, q[path[i]].c);

    return 0;
}