#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

long long steps;

/* Bubble Sort */
void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            steps++;
            if (a[j] < a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

/* Insertion Sort */
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;

        while (j >= 0) {
            steps++;
            if (a[j] < key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}

/* Radix Sort: non-negative integers only */
void radixSort(int a[], int n) {
    int output[MAX], max = a[0];

    for (int i = 1; i < n; i++) {
        steps++;
        if (a[i] > max)
            max = a[i];
    }

    for (int exp = 1; max / exp > 0; ) {
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(a[i] / exp) % 10]++;
            steps++;
        }

        for (int i = 8; i >= 0; i--)
            count[i] += count[i + 1];

        for (int i = n - 1; i >= 0; i--) {
            int d = (a[i] / exp) % 10;
            output[--count[d]] = a[i];
        }

        for (int i = 0; i < n; i++)
            a[i] = output[i];

        if (exp > max / 10)
            break;
        exp *= 10;
    }
}

/* Merge Sort */
void merge(int a[], int l, int m, int r) {
    int temp[MAX];
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        steps++;
        if (a[i] >= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++)
        a[i] = temp[k++];
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

/* Quick Sort */
int partition(int a[], int low, int high) {
    int pivot = a[high], i = low - 1;

    for (int j = low; j < high; j++) {
        steps++;
        if (a[j] > pivot) {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    int t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;

    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

/* Read data from file */
int readFile(int a[]) {
    FILE *fp = fopen("numbers.txt", "r");

    if (fp == NULL) {
        printf("Cannot open numbers.txt\n");
        return -1;
    }

    int n = 0;

    while (n < MAX && fscanf(fp, "%d", &a[n]) == 1)
        n++;

    fclose(fp);
    return n;
}

/* Print array */
void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int choice, a[MAX], n;

    do {
        printf("\n1. Bubble Sort");
        printf("\n2. Insertion Sort");
        printf("\n3. Radix Sort");
        printf("\n4. Merge Sort");
        printf("\n5. Quick Sort");
        printf("\n6. Compare all methods");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 0)
            break;

        if (choice < 1 || choice > 6) {
            printf("Invalid choice!\n");
            continue;
        }

        int first = (choice == 6) ? 1 : choice;
        int last = (choice == 6) ? 5 : choice;

        for (int method = first; method <= last; method++) {
            n = readFile(a);

            if (n <= 0) {
                printf("File is empty or unavailable.\n");
                break;
            }

            steps = 0;

            switch (method) {
                case 1: bubbleSort(a, n); break;
                case 2: insertionSort(a, n); break;
                case 3:
                    if (a[0] < 0) {
                        printf("Radix sort requires non-negative numbers.\n");
                        continue;
                    }
                    radixSort(a, n);
                    break;
                case 4: mergeSort(a, 0, n - 1); break;
                case 5: quickSort(a, 0, n - 1); break;
            }

            printf("\nMethod %d\n", method);
            printf("Sorted data: ");
            display(a, n);
            printf("Steps: %lld\n", steps);
        }

    } while (choice != 0);

    return 0;
}