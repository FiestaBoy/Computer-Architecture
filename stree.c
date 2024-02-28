#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
    struct TreeNode* left;
    struct TreeNode* right;
    int data;
}TreeNode_t;

TreeNode_t* newTreeNode(int data, TreeNode_t* left, TreeNode_t* right) {
    TreeNode_t* ret = malloc(sizeof(TreeNode_t));
    ret->left = left;
    ret->right = right;
    ret->data = data;
    return ret;
}

// Helper method, which recursively adds TreeNodes to the Tree by checking the data according to how the BST works
TreeNode_t* insertHelper(TreeNode_t* root, int data) {
    if (root == NULL) {
        // Create a new node if the current one is NULL
        return newTreeNode(data, NULL, NULL);
    } else if (data < root->data) {
        // Recursively insert into the left subtree
        root->left = insertHelper(root->left, data);
    } else {
        // Recursively insert into the right subtree
        root->right = insertHelper(root->right, data);
    }

    return root;
}

TreeNode_t* insert(TreeNode_t* root, char* arr) {
    // Used strtok to get every integer
    char* cur_token = strtok(arr, " ");

    while (cur_token != NULL) {
        // Convert string to int
        int data = atoi(cur_token);
        // Helper method call
        root = insertHelper(root, data);
        // Pass in NULL so it breaks out of the loop and continues with the rest of the string
        cur_token = strtok(NULL, " ");
    }

    return root;
}

// inOrder print 
void printTree(TreeNode_t* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

// Recurse through the tree and free the nodes
void freeBST(TreeNode_t* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main(int argc, char* argv[]) {

    // Error cases
    if (argc != 2) {
        puts("Two arguments expected.");
        perror("Error: ");
        return 1;
    }
    if (strlen(argv[1]) > 1000) {
        puts("String has to be no longer than 1000 characters");
        perror("Error: ");
        return 1;
    }
    
    TreeNode_t* root = NULL;
    root = insert(root, argv[1]);
    printTree(root);
    freeBST(root);
    
    return 0;
}