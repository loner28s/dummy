#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure to hold customer information
typedef struct {
    int custid;
    char custname[50];
    char custphno[15];
} Customer;

// Hash table to store customer records
Customer* hashTable[TABLE_SIZE];

// Hash function
int hash(int custid) {
    return custid % TABLE_SIZE;
}

// Function to insert a new customer record
void insertCustomer(int custid, const char* custname, const char* custphno) {
    int index = hash(custid);
    
    // Linear probing to handle collisions
    while (hashTable[index] != NULL) {
        // If the same customer ID exists, update it (optional)
        if (hashTable[index]->custid == custid) {
            printf("Customer ID %d already exists. Updating record.\n", custid);
            hashTable[index]->custid = custid;
            strcpy(hashTable[index]->custname, custname);
            strcpy(hashTable[index]->custphno, custphno);
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Move to next index
    }

    // Create new customer and insert
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->custid = custid;
    strcpy(newCustomer->custname, custname);
    strcpy(newCustomer->custphno, custphno);
    hashTable[index] = newCustomer;
    printf("Inserted Customer ID %d: %s, %s\n", custid, custname, custphno);
}

// Function to search for customer information by customer ID
Customer* searchCustomer(int custid) {
    int index = hash(custid);
    
    while (hashTable[index] != NULL) {
        if (hashTable[index]->custid == custid) {
            return hashTable[index]; // Customer found
        }
        index = (index + 1) % TABLE_SIZE; // Move to next index
    }
    
    return NULL; // Customer not found
}

// Function to display all customer records
void displayCustomers() {
    printf("\nCustomer Records:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("Index %d: ID: %d, Name: %s, Phone: %s\n", 
                   i, hashTable[i]->custid, hashTable[i]->custname, hashTable[i]->custphno);
        }
    }
}

int main() {
    int choice, custid;
    char custname[50], custphno[15];
    
    while (1) {
        printf("\n1. Insert Customer\n2. Search Customer\n3. Display Customers\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter Customer ID: ");
                scanf("%d", &custid);
                printf("Enter Customer Name: ");
                scanf(" %[^\n]", custname); // Read string with spaces
                printf("Enter Customer Phone: ");
                scanf(" %[^\n]", custphno);
                insertCustomer(custid, custname, custphno);
                break;
                
            case 2:
                printf("Enter Customer ID to search: ");
                scanf("%d", &custid);
                Customer* customer = searchCustomer(custid);
                if (customer) {
                    printf("Customer found: ID: %d, Name: %s, Phone: %s\n", 
                           customer->custid, customer->custname, customer->custphno);
                } else {
                    printf("Customer ID %d not found.\n", custid);
                }
                break;
                
            case 3:
                displayCustomers();
                break;

            case 4:
                // Free allocated memory before exiting
                for (int i = 0; i < TABLE_SIZE; i++) {
                    if (hashTable[i] != NULL) {
                        free(hashTable[i]);
                    }
                }
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
