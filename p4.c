#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX 100

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

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^';
}

void infixToPostfix() {
    char infix[MAX], postfix[MAX], stack[MAX];
    int top = -1;
    int k = 0;

    printf("Enter the expression: ");
    getchar();              // consume newline left by scanf()
    fgets(infix, MAX, stdin);

    for (int i = 0; infix[i] != '\0'; i++) {

        char c = infix[i];

        if (c == ' ' || c == '\n')
            continue;

        // Operand
        if (isalnum(c)) {
            postfix[k++] = c;
        }

        // Opening parenthesis
        else if (c == '(') {
            stack[++top] = c;
        }

        // Closing parenthesis
        else if (c == ')') {

            while (top >= 0 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }

            if (top >= 0)
                top--;       // remove '('
        }

        // Operator
        else if (isOperator(c)) {

            while (top >= 0 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c)) {

                postfix[k++] = stack[top--];
            }

            stack[++top] = c;
        }
    }

    // Pop remaining operators
    while (top >= 0) {
        postfix[k++] = stack[top--];
    }

    postfix[k] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

int evaluatePostfix() {
    char postfix[MAX];
    int stack[MAX];
    int top = -1;

    printf("Enter postfix expression: ");
    getchar();
    fgets(postfix, MAX, stdin);

    for (int i = 0; postfix[i] != '\0'; i++) {

        char c = postfix[i];

        if (c == ' ' || c == '\n')
            continue;

        // Operand
        if (isdigit(c)) {
            stack[++top] = c - '0';
        }

        // Operator
        else if (isOperator(c)) {

            int b = stack[top--];
            int a = stack[top--];

            int result;

            switch (c) {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    result = a / b;
                    break;

                case '%':
                    result = a % b;
                    break;

                case '^':
                    result = (int)pow(a, b);
                    break;
            }

            stack[++top] = result;
        }
    }

    return stack[top];
}

int main() {

    int ch;

    do {

        printf("\nEnter your choice\n");
        printf("1. Infix-To-Postfix\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Exit\n");

        scanf("%d", &ch);

        switch (ch) {

            case 1:
                infixToPostfix();
                break;

            case 2:
                printf("Result = %d\n", evaluatePostfix());
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (ch != 3);

    return 0;
}