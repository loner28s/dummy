#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to check if a character is an operand
int isOperand(char c) {
    return isalpha(c); // Assuming single-letter operands
}

// Function to check if the parentheses are balanced
int areParenthesesBalanced(const char* expression) {
    int stack[MAX], top = -1;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            stack[++top] = '(';
        } else if (expression[i] == ')') {
            if (top == -1) {
                return 0; // Unbalanced: no matching '('
            }
            top--; // Pop the matching '('
        }
    }
    return (top == -1); // Stack should be empty if balanced
}

// Function to convert infix expression to postfix
void infixToPostfix(const char* infix, char* postfix) {
    int top = -1;
    char stack[MAX];
    int j = 0; // Index for the postfix expression

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if (top != -1) top--; // Pop the '(' from the stack
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        }
    }

    // Pop all the remaining operators in the stack
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0'; // Null-terminate the postfix expression
}

int main() {
    char infix[MAX];
    char postfix[MAX];

    // Input the infix expression
    printf("Enter a parenthesized arithmetic expression: ");
    scanf("%s", infix);

    // Check if the parentheses are balanced
    if (areParenthesesBalanced(infix)) {
        printf("The expression has balanced parentheses.\n");

        // Convert the infix to postfix
        infixToPostfix(infix, postfix);
        printf("Postfix expression: %s\n", postfix);
    } else {
        printf("The expression has unbalanced parentheses.\n");
    }

    return 0;
}
