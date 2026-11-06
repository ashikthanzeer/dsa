#include <stdio.h>

#define MAX 100

typedef struct {
    int token;
    int forms;
} Customer;

Customer queue[MAX];

int front = 0;
int rear = -1;
int count = 0;

void addCustomer() {
    if (count == MAX) {
        printf("Queue is full!\n");
        return;
    }

    Customer c;

    printf("Enter number of tickets to book: ");
    scanf("%d", &c.forms);

    if (c.forms <= 0) {
        printf("Invalid number of tickets.\n");
        return;
    }

    c.token = (rear + 2);   // token numbers start from 1

    if (count == 0)
        c.token = 1;
    else {
        // Find next token number
        int last = (rear >= front) ? queue[rear].token : queue[rear].token;
        c.token = last + 1;
    }

    rear = (rear + 1) % MAX;
    queue[rear] = c;
    count++;

    printf("Token issued: %d\n", c.token);
}

void serveCustomer() {
    if (count == 0) {
        printf("No customers waiting.\n");
        return;
    }

    Customer c = queue[front];

    printf("\nServing Customer with Token %d\n", c.token);
    printf("Forms remaining before booking: %d\n", c.forms);

    // One ticket/form is booked
    c.forms--;

    // Remove current customer
    front = (front + 1) % MAX;
    count--;

    // If more tickets remain, send customer to rear
    if (c.forms > 0) {
        rear = (rear + 1) % MAX;
        queue[rear] = c;
        count++;

        printf("Customer has %d forms remaining.\n", c.forms);
        printf("Customer moved to the rear of the queue.\n");
    } else {
        printf("Customer has completed all bookings.\n");
    }
}

void displayCurrent() {
    if (count == 0) {
        printf("No customer is currently waiting.\n");
        return;
    }

    printf("\nCurrent customer being served:\n");
    printf("Token number : %d\n", queue[front].token);
    printf("Forms        : %d\n", queue[front].forms);
}

void displayWaitingCount() {
    printf("\nNumber of customers waiting: %d\n", count);
}

void displayQueue() {
    if (count == 0) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\n===== CUSTOMER QUEUE =====\n");
    printf("Token\tForms\n");
    printf("-------------------------\n");

    int i = front;

    for (int j = 0; j < count; j++) {
        printf("%d\t%d\n", queue[i].token, queue[i].forms);
        i = (i + 1) % MAX;
    }
}

int main() {
    int choice;

    do {
        printf("\n===== RAILWAY RESERVATION =====\n");
        printf("1. Take Token\n");
        printf("2. Serve Customer\n");
        printf("3. Display Current Customer\n");
        printf("4. Display Number of Customers Waiting\n");
        printf("5. Display All Customers\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addCustomer();
                break;

            case 2:
                serveCustomer();
                break;

            case 3:
                displayCurrent();
                break;

            case 4:
                displayWaitingCount();
                break;

            case 5:
                displayQueue();
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}