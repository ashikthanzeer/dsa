#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int listIndex;
    int elementIndex;
} Node;

Node heap[1000];
int heapSize = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(Node node) {
    int i = heapSize++;
    heap[i] = node;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].value <= heap[i].value)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

Node extractMin() {
    Node min = heap[0];
    heap[0] = heap[--heapSize];

    int i = 0;

    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heapSize &&
            heap[left].value < heap[smallest].value)
            smallest = left;

        if (right < heapSize &&
            heap[right].value < heap[smallest].value)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return min;
}

int main() {
    int k, size[100];

    printf("Enter number of sorted lists: ");
    scanf("%d", &k);

    int *lists[100];

    for (int i = 0; i < k; i++) {
        printf("Enter size of list %d: ", i + 1);
        scanf("%d", &size[i]);

        lists[i] = malloc(size[i] * sizeof(int));

        printf("Enter sorted elements: ");
        for (int j = 0; j < size[i]; j++)
            scanf("%d", &lists[i][j]);

        if (sizes[i] > 0) {
            Node node = {lists[i][0], i, 0};
            insert(node);
        }
    }

    printf("Merged sorted list: ");

    while (heapSize > 0) {
        Node min = extractMin();

        printf("%d ", min.value);

        int next = min.elementIndex + 1;
        int list = min.listIndex;

        if (next < size[list]) {
            Node node = {lists[list][next], list, next};
            insert(node);
        }
    }

    printf("\n");

    for (int i = 0; i < k; i++)
        free(lists[i]);

    return 0;
}