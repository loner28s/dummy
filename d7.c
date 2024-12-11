#include <stdio.h>
#include <stdlib.h>

// Define the structure for each node of the polynomial linked list
struct Node {
    int coeff;  // Coefficient
    int exp;    // Exponent
    struct Node* next;
};

// Function to create a new node in the linked list
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the polynomial
void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d*x^%d", temp->coeff, temp->exp);
        if (temp->next != NULL) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp1 = poly1;
    struct Node* temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp > temp2->exp) {
            insertEnd(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            insertEnd(&result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {
                insertEnd(&result, sumCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    // Add remaining terms of poly1
    while (temp1 != NULL) {
        insertEnd(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    // Add remaining terms of poly2
    while (temp2 != NULL) {
        insertEnd(&result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

// Main function to demonstrate polynomial addition
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Creating the first polynomial: 5x^3 + 4x^2 + 2x^1
    insertEnd(&poly1, 9, 5);
    insertEnd(&poly1, 6, 3);
    insertEnd(&poly1, 3, 1);

    // Creating the second polynomial: 3x^3 + 1x^1 + 2x^0
    insertEnd(&poly2, 3, 3);
    insertEnd(&poly2, 6, 1);
    insertEnd(&poly2, 9, 0);

    // Print the input polynomials
    printf("First Polynomial: ");
    printPolynomial(poly1);

    printf("Second Polynomial: ");
    printPolynomial(poly2);

    // Add the two polynomials
    struct Node* result = addPolynomials(poly1, poly2);

    // Print the result
    printf("Sum of Polynomials: ");
    printPolynomial(result);

    return 0;
}
