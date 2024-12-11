#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to count total nodes
int countTotalNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countTotalNodes(root->left) + countTotalNodes(root->right);
}

// Function to count terminal (leaf) nodes
int countTerminalNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    // A terminal node is a leaf node
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countTerminalNodes(root->left) + countTerminalNodes(root->right);
}

// Function to count non-terminal nodes
int countNonTerminalNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    // Non-terminal nodes are those with at least one child
    int count = (root->left != NULL || root->right != NULL) ? 1 : 0;
    return count + countNonTerminalNodes(root->left) + countNonTerminalNodes(root->right);
}

// Function to count nodes with degree 2
int countNodesWithDegreeTwo(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    // Degree 2 means the node has both left and right children
    int count = (root->left != NULL && root->right != NULL) ? 1 : 0;
    return count + countNodesWithDegreeTwo(root->left) + countNodesWithDegreeTwo(root->right);
}

// Main function to demonstrate the BST operations
int main() {
    struct Node* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    // Insert values into the BST
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Total number of nodes: %d\n", countTotalNodes(root));
    printf("Number of terminal (leaf) nodes: %d\n", countTerminalNodes(root));
    printf("Number of non-terminal nodes: %d\n", countNonTerminalNodes(root));
    printf("Number of nodes with degree 2: %d\n", countNodesWithDegreeTwo(root));
    return 0;
}