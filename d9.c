#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define a structure for tree nodes
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

// Stack structure for building the tree
typedef struct Stack {
    Node *treeNode;
    struct Stack *next;
} Stack;

// Function to create a new tree node
Node *createNode(char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Push operation for the stack
void push(Stack **top, Node *treeNode) {
    Stack *newStackNode = (Stack *)malloc(sizeof(Stack));
    newStackNode->treeNode = treeNode;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Pop operation for the stack
Node *pop(Stack **top) {
    if (*top == NULL) return NULL;
    Stack *temp = *top;
    Node *treeNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

// Function to build an expression tree from a postfix expression
Node *buildExpressionTree(char *postfix) {
    Stack *stack = NULL;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isalnum(ch)) { // Operand
            push(&stack, createNode(ch));
        } else { // Operator
            Node *operatorNode = createNode(ch);
            operatorNode->right = pop(&stack);
            operatorNode->left = pop(&stack);
            push(&stack, operatorNode);
        }
    }
    return pop(&stack);
}

// Recursive functions for tree traversals
void prefixTraversal(Node *root) {
    if (root) {
        printf("%c", root->data);
        prefixTraversal(root->left);
        prefixTraversal(root->right);
    }
}

void infixTraversal(Node *root) {
    if (root) {
        if (root->left && root->right) printf("(");
        infixTraversal(root->left);
        printf("%c", root->data);
        infixTraversal(root->right);
        if (root->left && root->right) printf(")");
    }
}

void postfixTraversal(Node *root) {
    if (root) {
        postfixTraversal(root->left);
        postfixTraversal(root->right);
        printf("%c", root->data);
    }
}

// Main function
int main() {
    char postfix[100];

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    Node *root = buildExpressionTree(postfix);

    printf("\nOriginal Postfix Expression: %s", postfix);

    printf("\nPrefix Expression: ");
    prefixTraversal(root);

    printf("\nInfix Expression: ");
    infixTraversal(root);

    printf("\nPostfix Expression: ");
    postfixTraversal(root);

    return 0;
}
