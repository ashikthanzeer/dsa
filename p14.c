#include <stdio.h>
#include <stdlib.h>

struct Customer {
    int token;
    int category;
};

/* Priority:
   1 - Differently Abled
   2 - Senior Citizen
   3 - Defence
   4 - Normal
*/

int main() {
    int n, i, j;
    
    printf("Enter number of customers: ");
    scanf("%d", &n);

    struct Customer c[n];

    // Input customers
    for (i = 0; i < n; i++) {
        c[i].token = i + 1;

        printf("\nCustomer %d\n", i + 1);
        printf("1. Differently Abled\n");
        printf("2. Senior Citizen\n");
        printf("3. Defence Personnel\n");
        printf("4. Normal Person\n");
        printf("Enter category: ");
        scanf("%d", &c[i].category);
    }

    // Sort according to priority
    // Stable sorting maintains arrival order within same category
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (c[j].category > c[j + 1].category) {
                struct Customer temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }

    // Serving customers
    printf("\n--- SERVICE ORDER ---\n");

    for (i = 0; i < n; i++) {
        printf("Token %d - ", c[i].token);

        switch (c[i].category) {
            case 1:
                printf("Differently Abled\n");
                break;
            case 2:
                printf("Senior Citizen\n");
                break;
            case 3:
                printf("Defence Personnel\n");
                break;
            case 4:
                printf("Normal Person\n");
                break;
        }
    }

    return 0;
}