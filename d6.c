#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int item;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->item = item;
    newNode->next = NULL;
    return newNode;
}

// Function to insert an item into the linked list in ascending order
struct Node* insert(struct Node* head, int item) {
    struct Node* newNode = createNode(item);
    if (head == NULL || item < head->item) {
        newNode->next = head;
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL && current->next->item < item) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to display the items in the linked list
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->item);
        current = current->next;
    }
    printf("\n");
}

// Function to search for an item in the linked list
struct Node* search(struct Node* head, int item) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->item == item) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main() {
    struct Node* head = NULL;
    int choice, item;

    printf("Warehouse Management System\n");
    printf("1. Insert item\n");
    printf("2. Display items (Ascending Order)\n");
    printf("3. Search for an item\n");
    printf("4. Exit\n");

    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &item);
                head = insert(head, item);
                break;
            case 2:
                printf("Items in ascending order: ");
                display(head);
                break;
            case 3:
                printf("Enter item to search: ");
                scanf("%d", &item);
                if (search(head, item) != NULL) {
                    printf("Item %d found in the warehouse.\n", item);
                } else {
                    printf("Item %d not found in the warehouse.\n", item);
                }
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
