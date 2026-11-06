#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;


/* Create a new tree node */
Node* createNode(char data) {

    Node *newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* Operator precedence */
int precedence(char op) {

    switch (op) {

        case '^':
            return 3;

        case '*':
        case '/':
        case '%':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}


/* Check whether character is an operator */
int isOperator(char c) {

    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '%' ||
           c == '^';
}


/* Construct subtree */
void buildSubtree(char operatorStack[],
                  int *opTop,
                  Node *nodeStack[],
                  int *nodeTop) {

    char op = operatorStack[(*opTop)--];

    Node *right = nodeStack[(*nodeTop)--];
    Node *left = nodeStack[(*nodeTop)--];

    Node *root = createNode(op);

    root->left = left;
    root->right = right;

    nodeStack[++(*nodeTop)] = root;
}


/* Construct expression tree */
Node* constructTree(char expression[]) {

    char operatorStack[MAX];
    Node *nodeStack[MAX];

    int opTop = -1;
    int nodeTop = -1;

    for (int i = 0; expression[i] != '\0'; i++) {

        char c = expression[i];

        if (c == ' ' || c == '\n')
            continue;

        /* Operand */
        if (isalnum(c)) {

            nodeStack[++nodeTop] = createNode(c);
        }

        /* Opening parenthesis */
        else if (c == '(') {

            operatorStack[++opTop] = c;
        }

        /* Closing parenthesis */
        else if (c == ')') {

            while (opTop >= 0 &&
                   operatorStack[opTop] != '(') {

                buildSubtree(operatorStack,
                             &opTop,
                             nodeStack,
                             &nodeTop);
            }

            if (opTop >= 0)
                opTop--;       // remove '('
        }

        /* Operator */
        else if (isOperator(c)) {

            while (opTop >= 0 &&
                   operatorStack[opTop] != '(' &&
                   precedence(operatorStack[opTop])
                   >= precedence(c)) {

                buildSubtree(operatorStack,
                             &opTop,
                             nodeStack,
                             &nodeTop);
            }

            operatorStack[++opTop] = c;
        }
    }

    /* Process remaining operators */
    while (opTop >= 0) {

        buildSubtree(operatorStack,
                     &opTop,
                     nodeStack,
                     &nodeTop);
    }

    return nodeStack[nodeTop];
}


/* Prefix traversal */
void prefix(Node *root) {

    if (root == NULL)
        return;

    printf("%c ", root->data);

    prefix(root->left);
    prefix(root->right);
}


/* Postfix traversal */
void postfix(Node *root) {

    if (root == NULL)
        return;

    postfix(root->left);
    postfix(root->right);

    printf("%c ", root->data);
}


/* Inorder traversal */
void inorder(Node *root) {

    if (root == NULL)
        return;

    if (isOperator(root->data))
        printf("(");

    inorder(root->left);

    printf("%c", root->data);

    inorder(root->right);

    if (isOperator(root->data))
        printf(")");
}


/* Free tree */
void freeTree(Node *root) {

    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


int main() {

    char expression[MAX];

    printf("Enter infix expression: ");
    fgets(expression, MAX, stdin);

    Node *root = constructTree(expression);

    printf("\nExpression Tree Inorder: ");
    inorder(root);

    printf("\nPrefix Expression: ");
    prefix(root);

    printf("\nPostfix Expression: ");
    postfix(root);

    printf("\n");

    freeTree(root);

    return 0;
}