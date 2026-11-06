#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int main() {
    char document[MAX_WORDS][MAX_WORD_LEN];
    int num_words = 0;
    char key_term[MAX_WORD_LEN];
    char replacement_word[MAX_WORD_LEN];
    int replacements_made = 0;

    // 1. Initializing the document with a sample list of words
    printf("Enter the number of words in the document: ");
    scanf("%d", &num_words);

    printf("Enter the document text (word by word):\n");
    for (int i = 0; i < num_words; i++) {
        scanf("%s", document[i]);
    }

    // 2. Getting Find and Replace terms
    printf("\nEnter the word to find: ");
    scanf("%s", key_term);
   
    printf("Enter the replacement word: ");
    scanf("%s", replacement_word);

    // 3. (a) Replace occurrences and (b) Count them
    for (int i = 0; i < num_words; i++) {
        if (strcmp(document[i], key_term) == 0) {
            strcpy(document[i], replacement_word);
            replacements_made++;
        }
    }

    // (b) Display the number of replacements made
    printf("\nTotal replacements made: %d\n", replacements_made);

    // (c) Display the updated document
    printf("Updated Document:\n");
    for (int i = 0; i < num_words; i++) {
        printf("%s ", document[i]);
    }
    printf("\n");

    return 0;
}