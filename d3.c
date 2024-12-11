#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100 // Maximum size for the stack

// Function to evaluate a postfix expression
int evaluatePostfix(const char* postfix) {
    int stack[MAX];
    int top = -1; // Initialize the top of the stack

    for (int i = 0; postfix[i] != '\0'; i++) {
        // If the character is an operand (a single digit)
        if (isdigit(postfix[i])) {
            // Convert character to integer and push onto the stack
            stack[++top] = postfix[i] - '0'; // Convert from char to int
        } 
        // If the character is an operator (+, -, *, /)
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            // Pop the top two elements from the stack
            if (top < 1) {
                printf("Invalid postfix expression.\n");
                exit(1); // Exit the program if there are not enough operands
            }

            int operand2 = stack[top--]; // Second operand
            int operand1 = stack[top--]; // First operand

            // Perform the operation and push the result onto the stack
            switch (postfix[i]) {
                case '+':
                    stack[++top] = operand1 + operand2;
                    break;
                case '-':
                    stack[++top] = operand1 - operand2;
                    break;
                case '*':
                    stack[++top] = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero error.\n");
                        exit(1);
                    }
                    stack[++top] = operand1 / operand2;
                    break;
            }
        }
    }

    // The result should be the only element left on the stack
    if (top != 0) {
        printf("Invalid postfix expression.\n");
        exit(1);
    }

    return stack[top]; // Return the final result
}

int main() {
    char postfix[MAX];

    // Input the postfix expression
    printf("Enter a valid postfix expression: ");
    scanf("%s", postfix);

    // Evaluate the postfix expression and print the result
    int result = evaluatePostfix(postfix);
    printf("The result of the postfix expression is: %d\n", result);

    return 0;
}
