#include <stdio.h>

int canAllocate(int pages[], int n, int s, int maxPages) {
    int students = 1;
    int currentPages = 0;

    for (int i = 0; i < n; i++) {
        if (currentPages + pages[i] <= maxPages) {
            currentPages += pages[i];
        } else {
            students++;
            currentPages = pages[i];--

            if (students > s)
                return 0;
        }
    }

    return 1;
}

void printAllocation(int pages[], int n, int s, int maxPages) {
    int student = 1;
    int currentPages = 0;

    printf("\nOptimal Allocation:\n");

    printf("Student %d: [", student);

    for (int i = 0; i < n; i++) {

        if (currentPages + pages[i] <= maxPages) {

            if (currentPages != 0)
                printf(", ");

            printf("%d", pages[i]);
            currentPages += pages[i];

        } else {

            printf("] -> %d pages\n", currentPages);

            student++;
            currentPages = pages[i];

            printf("Student %d: [%d", student, pages[i]);
        }
    }

    printf("] -> %d pages\n", currentPages);
}

int main() {
    int n, s;

    printf("Enter number of books: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter pages in each book (sorted):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of students: ");
    scanf("%d", &s);

    if (s > n) {
        printf("Number of students cannot be greater than number of books.\n");
        return 0;
    }

    int low = pages[n - 1];
    int high = 0;

    // Calculate total number of pages
    for (int i = 0; i < n; i++) {
        high += pages[i];
    }

    int answer = high;

    // Binary search for minimum possible maximum
    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (canAllocate(pages, n, s, mid)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("\nMinimum possible maximum pages = %d\n", answer);

    printAllocation(pages, n, s, answer);

    return 0;
}