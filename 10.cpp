#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        height = 1;
        left = right = nullptr;
    }
};

int height(Node* root) {
    if (!root)
        return 0;
    return root->height;
}

int getBalance(Node* root) {
    if (!root)
        return 0;
    return height(root->left) - height(root->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

Node* insert(Node* root, int key) {
    // Perform the normal BST insertion
    if (!root)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else // Equal keys not allowed in BST
        return root;

    // Update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor
    int balance = getBalance(root);

    // If node becomes unbalanced, then 4 cases

    // Left Left Case
    if (balance > 1 && key < root->left->data)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return unchanged node pointer
    return root;
}

// Utility to print InOrder Traversal
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Sample insertions
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "InOrder Traversal of the constructed AVL Tree is:\n";
    inOrder(root);
    cout << endl;

    return 0;
}
