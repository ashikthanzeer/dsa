#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list {
    char app[25];
    struct list *prev;
    struct list *next;
} node;


/* Open an app / move existing app to front */
void insert(char *app, node *head) {

    node *p = head;

    /* Check whether app already exists */
    while (p->next != NULL) {

        if (strcmp(p->next->app, app) == 0) {

            node *temp = p->next;

            /* Remove from current position */
            p->next = temp->next;

            if (temp->next != NULL)
                temp->next->prev = p;

            /* Insert at front */
            temp->prev = head;
            temp->next = head->next;

            if (head->next != NULL)
                head->next->prev = temp;

            head->next = temp;

            return;
        }

        p = p->next;
    }

    /* App doesn't exist -> create new node */
    node *app_node = malloc(sizeof(node));

    if (app_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(app_node->app, app);

    /* Insert at front */
    app_node->prev = head;
    app_node->next = head->next;

    if (head->next != NULL)
        head->next->prev = app_node;

    head->next = app_node;
}


/* Remove most recently opened app */
bool removeLatest(node *head) {

    if (head->next == NULL)
        return false;

    node *temp = head->next;

    head->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = head;

    free(temp);

    return true;
}


/* Display apps from recent to oldest */
void display(node *head) {

    node *p = head->next;

    if (p == NULL) {
        printf("No app found\n");
        return;
    }

    printf("\nApps (Recent -> Oldest):\n");

    while (p != NULL) {
        printf("%s\n", p->app);
        p = p->next;
    }
}


/* Display most recently opened app */
void recent(node *head) {

    if (head->next == NULL) {
        printf("No apps\n");
        return;
    }

    printf("Recent app: %s\n", head->next->app);
}


/* Search for an app */
void locate(char *app, node *head) {

    node *p = head->next;

    while (p != NULL) {

        if (strcmp(p->app, app) == 0) {
            printf("App exists.\n");
            return;
        }

        p = p->next;
    }

    printf("App doesn't exist.\n");
}


/* Free entire linked list */
void freeList(node *head) {

    node *p = head->next;

    while (p != NULL) {
        node *temp = p;
        p = p->next;
        free(temp);
    }

    free(head);
}


int main() {

    /* Dummy head node */
    node *head = malloc(sizeof(node));

    if (head == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    head->prev = NULL;
    head->next = NULL;

    int ch;

    do {

        printf("\n----- MENU -----\n");
        printf("1. Open an app\n");
        printf("2. Remove latest app\n");
        printf("3. Show list of apps\n");
        printf("4. Locate an app\n");
        printf("5. Show recent app\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {

            case 1: {
                char app[25];

                printf("Enter app name: ");
                scanf("%24s", app);

                insert(app, head);
                break;
            }

            case 2:

                if (removeLatest(head))
                    printf("Recent app removed\n");
                else
                    printf("App list is empty\n");

                break;

            case 3:

                display(head);
                break;

            case 4: {
                char app[25];

                printf("Enter app name: ");
                scanf("%24s", app);

                locate(app, head);
                break;
            }

            case 5:

                recent(head);
                break;

            case 6:

                printf("Exiting...\n");
                break;

            default:

                printf("Invalid input\n");
        }

    } while (ch != 6);

    freeList(head);

    return 0;
}