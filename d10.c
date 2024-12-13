#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Function to display the linked list
void Display(struct node *head) {
    struct node *temp = head;
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to add a value in a sorted manner
struct node* Add(struct node *head, int value) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Error: Could not allocate memory.\n");
        return head;
    }
    newnode->data = value;
    newnode->next = NULL;

    if (head == NULL || newnode->data < head->data) {
        newnode->next = head;
        head = newnode;
    } else {
        struct node *curr = head, *prev = NULL;
        while (curr != NULL && newnode->data > curr->data) {
            prev = curr;
            curr = curr->next;
        }
        newnode->next = curr;
        if (prev != NULL) prev->next = newnode;
    }
    return head;
}

// Function to search for an element
int searchElement(struct node *head, int item) {
    struct node *curr = head; // Initialize current pointer
    int index = 0;

    // Traverse the linked list
    while (curr != NULL) {
        if (curr->data == item) {
            return index; // Return index if item is found
        }
        curr = curr->next;
        index++;
    }
    return -1; // Return -1 if item not found
}

int main() {
    int choice, value, item, index;
    struct node *head = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to add: ");
            scanf("%d", &value);
            head = Add(head, value);
            printf("Value added successfully.\n");
            break;
        case 2:
            printf("Linked List: ");
            Display(head);
            break;
        case 3:
            printf("Enter the element to search: ");
            scanf("%d", &item);
            index = searchElement(head, item);
            if (index == -1)
                printf("Item not found.\n");
            else
                printf("Item found at position: %d\n", index + 1);
            break;
        case 4:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
