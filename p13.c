#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    char meaning[100];
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(char word[], char meaning[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a word-meaning pair
struct Node* insert(struct Node* root, char word[], char meaning[]) {
    if (root == NULL)
        return createNode(word, meaning);

    int cmp = strcmp(word, root->word);

    if (cmp < 0)
        root->left = insert(root->left, word, meaning);

    else if (cmp > 0)
        root->right = insert(root->right, word, meaning);

    else
        printf("Word already exists!\n");

    return root;
}

// Search for a word
struct Node* search(struct Node* root, char word[]) {
    if (root == NULL || strcmp(word, root->word) == 0)
        return root;

    if (strcmp(word, root->word) < 0)
        return search(root->left, word);

    return search(root->right, word);
}

// Find the minimum node
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Delete a word
struct Node* deleteNode(struct Node* root, char word[]) {
    if (root == NULL)
        return NULL;

    int cmp = strcmp(word, root->word);

    if (cmp < 0) {
        root->left = deleteNode(root->left, word);
    }
    else if (cmp > 0) {
        root->right = deleteNode(root->right, word);
    }
    else {
        // No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Only right child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        // Only left child
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        else {
            struct Node* temp = findMin(root->right);

            strcpy(root->word, temp->word);
            strcpy(root->meaning, temp->meaning);

            root->right = deleteNode(root->right, temp->word);
        }
    }

    return root;
}

// Display dictionary in alphabetical order
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%-15s : %s\n", root->word, root->meaning);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice;
    char word[50], meaning[100];

    while (1) {
        printf("\n========== DICTIONARY ==========\n");
        printf("1. Find meaning\n");
        printf("2. Insert word\n");
        printf("3. Remove word\n");
        printf("4. Display dictionary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter word to search: ");
            scanf("%s", word);

            struct Node* result;
            result = search(root, word);

            if (result != NULL)
                printf("Meaning: %s\n", result->meaning);
            else
                printf("Word not found!\n");

            break;

        case 2:
            printf("Enter word: ");
            scanf("%s", word);

            printf("Enter meaning: ");
            scanf(" %[^\n]", meaning);

            root = insert(root, word, meaning);

            printf("Word inserted successfully.\n");
            break;

        case 3:
            printf("Enter word to remove: ");
            scanf("%s", word);

            if (search(root, word) == NULL) {
                printf("Word not found!\n");
            } else {
                root = deleteNode(root, word);
                printf("Word removed successfully.\n");
            }

            break;

        case 4:
            printf("\n------- Dictionary -------\n");

            if (root == NULL)
                printf("Dictionary is empty.\n");
            else
                inorder(root);

            break;

        case 5:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}