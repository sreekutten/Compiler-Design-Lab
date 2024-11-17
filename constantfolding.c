#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Function declarations
void input();
void output();
void change(int p, char *res);
void constant();

// Structure to store expressions
struct expr {
    char op[2], op1[5], op2[5], res[5];
} arr[10];

int n; // Number of expressions

void main() {
    input();       // Read input
    constant();    // Perform constant folding optimization
    output();      // Display optimized output
}

void input() {
    int i;
    printf("\nEnter the maximum number of expressions: ");
    scanf("%d", &n);
    printf("\nEnter the input (op op1 op2 res): \n");
    for (i = 0; i < n; i++) {
        scanf("%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}

void constant() {
    int i;
    int op1, op2, res;
    char op, res1[5];

    for (i = 0; i < n; i++) {
        // Check for assignment operator `=`
        if (strcmp(arr[i].op, "=") == 0) {
            // If op2 is "_", treat it as an empty operand
            if (strcmp(arr[i].op2, "_") == 0) {
                strcpy(arr[i].op2, "_");
            }
            // Propagate the value of op1 to res
            change(i, arr[i].op1);
            strcpy(arr[i].res, arr[i].op1);
        }
        // Check if both operands are constants
        else if (isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) {
            // Convert operands to integers
            op1 = atoi(arr[i].op1);
            op2 = atoi(arr[i].op2);
            op = arr[i].op[0];

            // Perform the operation
            switch (op) {
                case '+':
                    res = op1 + op2;
                    break;
                case '-':
                    res = op1 - op2;
                    break;
                case '*':
                    res = op1 * op2;
                    break;
                case '/':
                    if (op2 != 0)
                        res = op1 / op2;
                    else {
                        printf("Error: Division by zero in expression %d\n", i + 1);
                        exit(1);
                    }
                    break;
                default:
                    printf("Error: Unknown operator '%c' in expression %d\n", op, i + 1);
                    exit(1);
            }

            // Update result and propagate the changes
            sprintf(res1, "%d", res);
            change(i, res1);
            strcpy(arr[i].res, res1);
        }
    }
}

void output() {
    int i;
    printf("\nOptimized code is:\n");
    for (i = 0; i < n; i++) {
        printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}

void change(int p, char *res) {
    int i;
    for (i = p + 1; i < n; i++) {
        // Propagate the new value to op1 and op2 if they match the result of the previous expression
        if (strcmp(arr[p].res, arr[i].op1) == 0) {
            strcpy(arr[i].op1, res);
        }
        if (strcmp(arr[p].res, arr[i].op2) == 0) {
            strcpy(arr[i].op2, res);
        }
    }
}

