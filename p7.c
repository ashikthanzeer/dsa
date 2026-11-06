#include <stdio.h>
#include <string.h>

#define MAX 100
#define URL_SIZE 200

char backStack[MAX][URL_SIZE];
char forwardStack[MAX][URL_SIZE];

int backTop = -1;
int forwardTop = -1;

char currentURL[URL_SIZE];

/* Push URL into Back Stack */
void pushBack(char url[]) {
    if (backTop < MAX - 1) {
        strcpy(backStack[++backTop], url);
    }
}

/* Push URL into Forward Stack */
void pushForward(char url[]) {
    if (forwardTop < MAX - 1) {
        strcpy(forwardStack[++forwardTop], url);
    }
}

/* Pop from Back Stack */
void popBack(char url[]) {
    strcpy(url, backStack[backTop--]);
}

/* Pop from Forward Stack */
void popForward(char url[]) {
    strcpy(url, forwardStack[forwardTop--]);
}

/* Clear Forward Stack */
void clearForward() {
    forwardTop = -1;
}

/* Visit a new URL */
void visitPage() {
    char newURL[URL_SIZE];

    printf("\nEnter URL: ");
    scanf(" %[^\n]", newURL);

    /* Current page goes to Back stack */
    if (strlen(currentURL) > 0) {
        pushBack(currentURL);
    }

    strcpy(currentURL, newURL);

    /* New navigation clears Forward history */
    clearForward();

    printf("Now visiting: %s\n", currentURL);
}

/* Go Back */
void goBack() {
    if (backTop == -1) {
        printf("\nNo previous page available.\n");
        return;
    }

    /* Current page goes to Forward stack */
    pushForward(currentURL);

    /* Top of Back stack becomes current */
    popBack(currentURL);

    printf("\nNavigated back to:\n%s\n", currentURL);
}

/* Go Forward */
void goForward() {
    if (forwardTop == -1) {
        printf("\nNo forward page available.\n");
        return;
    }

    /* Current page goes to Back stack */
    pushBack(currentURL);

    /* Top of Forward stack becomes current */
    popForward(currentURL);

    printf("\nNavigated forward to:\n%s\n", currentURL);
}

/* Display current page */
void displayCurrent() {
    printf("\nCurrent Page:\n%s\n", currentURL);
}

/* Display Back stack */
void displayBackStack() {
    if (backTop == -1) {
        printf("\nBack stack is empty.\n");
        return;
    }

    printf("\n===== BACK HISTORY =====\n");

    for (int i = backTop; i >= 0; i--) {
        printf("%s\n", backStack[i]);
    }
}

/* Display Forward stack */
void displayForwardStack() {
    if (forwardTop == -1) {
        printf("\nForward stack is empty.\n");
        return;
    }

    printf("\n===== FORWARD HISTORY =====\n");

    for (int i = forwardTop; i >= 0; i--) {
        printf("%s\n", forwardStack[i]);
    }
}

int main() {

    int choice;

    /* Initially no page */
    currentURL[0] = '\0';

    do {

        printf("\n========== BROWSER ==========\n");
        printf("1. Visit New Page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Display Current Page\n");
        printf("5. Display Back History\n");
        printf("6. Display Forward History\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                visitPage();
                break;

            case 2:
                goBack();
                break;

            case 3:
                goForward();
                break;

            case 4:
                displayCurrent();
                break;

            case 5:
                displayBackStack();
                break;

            case 6:
                displayForwardStack();
                break;

            case 7:
                printf("\nExiting browser...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}