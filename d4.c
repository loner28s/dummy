#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5 // Maximum number of messages that the queue can hold

// Structure to represent the message queue
typedef struct {
    char messages[MAX][256]; // Array to hold messages (each up to 255 characters)
    int front;
    int rear;
    int size;
} MessageQueue;

// Function to initialize the message queue
void initializeQueue(MessageQueue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

// Function to check if the queue is full
int isQueueFull(MessageQueue* queue) {
    return queue->size == MAX;
}

// Function to check if the queue is empty
int isQueueEmpty(MessageQueue* queue) {
    return queue->size == 0;
}

// Function to add a message to the queue
void sendMessage(MessageQueue* queue, const char* message) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot send the message.\n");
        return;
    }

    // Add the new message at the rear of the queue
    queue->rear = (queue->rear + 1) % MAX;
    strcpy(queue->messages[queue->rear], message);
    queue->size++;
    printf("Message sent: %s\n", message);
}

// Function to receive and remove a message from the queue
void receiveMessage(MessageQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. No messages to receive.\n");
        return;
    }

    // Remove the message from the front of the queue
    printf("Message received: %s\n", queue->messages[queue->front]);
    queue->front = (queue->front + 1) % MAX;
    queue->size--;
}

// Function to display the contents of the queue
void displayQueue(MessageQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. No messages to display.\n");
        return;
    }

    printf("Messages in the queue:\n");
    int i = queue->front;
    int count = 0;
    while (count < queue->size) {
        printf("%s\n", queue->messages[i]);
        i = (i + 1) % MAX;
        count++;
    }
}

int main() {
    MessageQueue queue;
    initializeQueue(&queue);

    int choice;
    char message[256];

    do {
        printf("\nMessaging System Menu:\n");
        printf("1. Send a message\n");
        printf("2. Receive a message\n");
        printf("3. Display messages in the queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter your message: ");
                fgets(message, sizeof(message), stdin);
                // Remove the newline character at the end if present
                if (message[strlen(message) - 1] == '\n') {
                    message[strlen(message) - 1] = '\0';
                }
                sendMessage(&queue, message);
                break;

            case 2:
                receiveMessage(&queue);
                break;

            case 3:
                displayQueue(&queue);
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
