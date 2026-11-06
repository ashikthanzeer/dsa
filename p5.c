#include <stdio.h>
#include <string.h>

#define MAX 100
#define SPEED 30.0

typedef struct {
    char teacher[50];
    char filename[100];
    int pages;
    double waitingTime;
} Document;

Document queue[MAX];
int front = 0;
int rear = -1;
int count = 0;

void addDocument() {
    if (count == MAX) {
        printf("Printer queue is full!\n");
        return;
    }

    printf("Enter teacher name: ");
    scanf(" %[^\n]", queue[rear + 1].teacher);

    printf("Enter PDF filename: ");
    scanf(" %[^\n]", queue[rear + 1].filename);

    printf("Enter number of pages: ");
    scanf("%d", &queue[rear + 1].pages);

    rear++;
    count++;

    printf("Document added to printer queue.\n");
}

void calculateWaitingTimes() {
    double totalTime = 0;

    for (int i = front; i <= rear; i++) {
        queue[i].waitingTime = totalTime;

        totalTime += queue[i].pages / SPEED;
    }
}

void displayCurrentDocument() {
    if (count == 0) {
        printf("No document is currently being printed.\n");
        return;
    }

    printf("\nCurrently being printed:\n");
    printf("Teacher : %s\n", queue[front].teacher);
    printf("PDF     : %s\n", queue[front].filename);
    printf("Pages   : %d\n", queue[front].pages);
}

void findWaitingTime() {
    char target[100];

    printf("Enter PDF filename: ");
    scanf(" %[^\n]", target);

    calculateWaitingTimes();

    for (int i = front; i <= rear; i++) {
        if (strcmp(queue[i].filename, target) == 0) {
            printf("\nPDF: %s\n", queue[i].filename);
            printf("Teacher: %s\n", queue[i].teacher);
            printf("Waiting time: %.2f minutes\n",
                   queue[i].waitingTime);
            return;
        }
    }

    printf("Document not found in the queue.\n");
}

void findMaximumWaiting() {
    if (count == 0) {
        printf("Printer queue is empty.\n");
        return;
    }

    calculateWaitingTimes();

    int maxIndex = front;

    for (int i = front + 1; i <= rear; i++) {
        if (queue[i].waitingTime > queue[maxIndex].waitingTime) {
            maxIndex = i;
        }
    }

    printf("\nTeacher who has to wait the most:\n");
    printf("Teacher : %s\n", queue[maxIndex].teacher);
    printf("PDF     : %s\n", queue[maxIndex].filename);
    printf("Waiting time : %.2f minutes\n",
           queue[maxIndex].waitingTime);
}

void printDocument() {
    if (count == 0) {
        printf("Printer queue is empty.\n");
        return;
    }

    printf("\nPrinting:\n");
    printf("Teacher : %s\n", queue[front].teacher);
    printf("PDF     : %s\n", queue[front].filename);

    front++;
    count--;

    if (count == 0) {
        front = 0;
        rear = -1;
    }
}

int main() {
    int choice;

    do {
        printf("\n===== PRINTER SPOOL =====\n");
        printf("1. Add PDF to printer queue\n");
        printf("2. Display currently printing teacher\n");
        printf("3. Find waiting time of a PDF\n");
        printf("4. Find teacher with maximum waiting time\n");
        printf("5. Print current document\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addDocument();
                break;

            case 2:
                displayCurrentDocument();
                break;

            case 3:
                findWaitingTime();
                break;

            case 4:
                findMaximumWaiting();
                break;

            case 5:
                printDocument();
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