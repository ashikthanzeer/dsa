#include <stdio.h>

#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} Element;

void readSparse(Element matrix[], int *count, int layer) {
    int rows, cols, nonZero;

    printf("\nEnter rows and columns for Layer %d: ", layer);
    scanf("%d %d", &rows, &cols);

    printf("Enter number of non-zero elements: ");
    scanf("%d", &nonZero);

    matrix[0].row = rows;
    matrix[0].col = cols;
    matrix[0].value = nonZero;

    *count = nonZero + 1;

    printf("Enter row, column and value for each element:\n");

    for (int i = 1; i <= nonZero; i++) {
        scanf("%d %d %d",
              &matrix[i].row,
              &matrix[i].col,
              &matrix[i].value);
    }
}

void displaySparse(Element matrix[], int count) {
    printf("\nRow\tCol\tValue\n");

    for (int i = 1; i < count; i++) {
        printf("%d\t%d\t%d\n",
               matrix[i].row,
               matrix[i].col,
               matrix[i].value);
    }
}

int addSparse(Element A[], Element B[], Element C[]) {
    int i = 1, j = 1, k = 1;

    C[0].row = A[0].row;
    C[0].col = A[0].col;

    while (i <= A[0].value && j <= B[0].value) {

        if (A[i].row < B[j].row ||
           (A[i].row == B[j].row && A[i].col < B[j].col)) {

            C[k++] = A[i++];

        }
        else if (A[i].row > B[j].row ||
                (A[i].row == B[j].row && A[i].col > B[j].col)) {

            C[k++] = B[j++];

        }
        else {
            int sum = A[i].value + B[j].value;

            if (sum != 0) {
                C[k].row = A[i].row;
                C[k].col = A[i].col;
                C[k].value = sum;
                k++;
            }

            i++;
            j++;
        }
    }

    while (i <= A[0].value)
        C[k++] = A[i++];

    while (j <= B[0].value)
        C[k++] = B[j++];

    C[0].value = k - 1;

    return k;
}

int transposeSparse(Element A[], Element T[]) {
    int k = 1;

    T[0].row = A[0].col;
    T[0].col = A[0].row;
    T[0].value = A[0].value;

    for (int col = 0; col < A[0].col; col++) {

        for (int i = 1; i <= A[0].value; i++) {

            if (A[i].col == col) {
                T[k].row = A[i].col;
                T[k].col = A[i].row;
                T[k].value = A[i].value;
                k++;
            }
        }
    }

    return k;
}

int main() {
    Element layer1[MAX], layer2[MAX], layer3[MAX];
    Element temp[MAX], final[MAX], transposed[MAX];

    int count1, count2, count3;
    int countTemp, countFinal, countTranspose;

    printf("=== Scene Update Input ===\n");

    readSparse(layer1, &count1, 1);
    readSparse(layer2, &count2, 2);
    readSparse(layer3, &count3, 3);

    /*
       Add Layer 1 + Layer 2
    */
    countTemp = addSparse(layer1, layer2, temp);

    /*
       Add result + Layer 3
    */
    countFinal = addSparse(temp, layer3, final);

    printf("\n=== Final Transformation Matrix ===");
    displaySparse(final, countFinal);

    /*
       Transpose final matrix before sending to GPU
    */
    countTranspose = transposeSparse(final, transposed);

    printf("\n=== Transposed Matrix for GPU ===");
    displaySparse(transposed, countTranspose);

    return 0;
}