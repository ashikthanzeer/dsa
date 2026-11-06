#include <stdio.h>
#include <string.h>

#define MAX 30

typedef struct {
    int start;
    int size;
    int free;
    char name[10];
} Block;

Block initial[MAX];
int initialCount;

void initialize() {
    initialCount = 0;

    Block b[] = {
        {0,    10, 0, "P5"},
        {10,  300, 1, "FREE"},
        {310,  90, 0, "P6"},
        {400, 600, 1, "FREE"},
        {1000,500, 0, "P1"},
        {1500,350, 1, "FREE"},
        {1850,150, 0, "P2"},
        {2000,200, 1, "FREE"},
        {2200,100, 0, "P4"},
        {2300,850, 1, "FREE"},
        {3150,350, 0, "P3"},
        {3500,499, 1, "FREE"}
    };

    initialCount = sizeof(b) / sizeof(b[0]);

    for (int i = 0; i < initialCount; i++)
        initial[i] = b[i];
}

void reset(Block mem[], int *n) {
    *n = initialCount;

    for (int i = 0; i < *n; i++)
        mem[i] = initial[i];
}

void mergeFree(Block mem[], int *n) {
    for (int i = 0; i < *n - 1; i++) {

        if (mem[i].free && mem[i + 1].free) {

            mem[i].size += mem[i + 1].size;

            for (int j = i + 1; j < *n - 1; j++)
                mem[j] = mem[j + 1];

            (*n)--;
            i--;
        }
    }
}

int allocate(Block mem[], int *n, char name[],
             int size, int strategy) {

    int selected = -1;

    for (int i = 0; i < *n; i++) {

        if (!mem[i].free || mem[i].size < size)
            continue;

        if (strategy == 1) {          // First Fit
            selected = i;
            break;
        }

        if (strategy == 2) {          // Best Fit
            if (selected == -1 ||
                mem[i].size < mem[selected].size)
                selected = i;
        }

        if (strategy == 3) {          // Worst Fit
            if (selected == -1 ||
                mem[i].size > mem[selected].size)
                selected = i;
        }
    }

    if (selected == -1)
        return 0;

    int remaining = mem[selected].size - size;

    strcpy(mem[selected].name, name);
    mem[selected].free = 0;
    mem[selected].size = size;

    if (remaining > 0) {

        for (int i = *n; i > selected + 1; i--)
            mem[i] = mem[i - 1];

        mem[selected + 1].start =
            mem[selected].start + size;

        mem[selected + 1].size = remaining;
        mem[selected + 1].free = 1;
        strcpy(mem[selected + 1].name, "FREE");

        (*n)++;
    }

    return 1;
}

void release(Block mem[], int *n, char name[]) {

    for (int i = 0; i < *n; i++) {

        if (!mem[i].free &&
            strcmp(mem[i].name, name) == 0) {

            mem[i].free = 1;
            strcpy(mem[i].name, "FREE");

            mergeFree(mem, n);
            return;
        }
    }
}

void display(Block mem[], int n) {

    printf("\nStart\tEnd\tSize\tStatus\n");
    printf("--------------------------------\n");

    int largest = 0;

    for (int i = 0; i < n; i++) {

        printf("%d\t%d\t%d\t%s\n",
               mem[i].start,
               mem[i].start + mem[i].size,
               mem[i].size,
               mem[i].name);

        if (mem[i].free && mem[i].size > largest)
            largest = mem[i].size;
    }

    printf("Largest free block = %d KB\n", largest);
}

void simulate(int strategy, char strategyName[]) {

    Block mem[MAX];
    int n;

    reset(mem, &n);

    printf("\n================================\n");
    printf("%s\n", strategyName);
    printf("================================\n");

    /* Requests */
    if (allocate(mem, &n, "P7", 115, strategy))
        printf("P7 allocated\n");

    if (allocate(mem, &n, "P10", 650, strategy))
        printf("P10 allocated\n");

    /* Completions */
    release(mem, &n, "P3");
    release(mem, &n, "P1");
    release(mem, &n, "P6");

    if (allocate(mem, &n, "P8", 200, strategy))
        printf("P8 allocated\n");

    release(mem, &n, "P5");
    release(mem, &n, "P2");

    if (allocate(mem, &n, "P9", 37, strategy))
        printf("P9 allocated\n");

    release(mem, &n, "P10");
    release(mem, &n, "P9");
    release(mem, &n, "P4");

    display(mem, n);
}

int main() {

    initialize();

    simulate(1, "FIRST FIT");
    simulate(2, "BEST FIT");
    simulate(3, "WORST FIT");

    return 0;
}