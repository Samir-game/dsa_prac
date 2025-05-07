#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node *left, *right;
    bool lf, rf; // lf = left is thread, rf = right is thread

    Node(int x) {
        val = x;
        left = right = nullptr;
        lf = rf = true;
    }
};

// Helper to find the leftmost node in the TBST
Node* leftMost(Node* node, Node* dummy) {
    if (!node) return nullptr;
    while (!node->lf && node->left != dummy)
        node = node->left;
    return node;
}

// Inorder traversal of the threaded BST
void inorderTraversal(Node* root) {
    Node* curr = leftMost(root->left, root);
    while (curr != root) {
        cout << curr->val << " ";
        if (curr->rf)
            curr = curr->right;
        else
            curr = leftMost(curr->right, root);
    }
    cout << endl;
}

// Insert a new node into the threaded BST
void insertIntoTBST(Node*& root, int key) {
    Node* newNode = new Node(key);
    if (root->left == nullptr) {
        root->left = newNode;
        newNode->left = root;
        newNode->right = root;
        return;
    }

    Node* curr = root->left;
    while (true) {
        if (key < curr->val) {
            if (curr->lf) {
                newNode->left = curr->left;
                newNode->right = curr;
                curr->left = newNode;
                curr->lf = false;
                return;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->rf) {
                newNode->right = curr->right;
                newNode->left = curr;
                curr->right = newNode;
                curr->rf = false;
                return;
            } else {
                curr = curr->right;
            }
        }
    }
}

int main() {
    // Create dummy node
    Node* root = new Node(-1); // Dummy node
    root->left = nullptr;
    root->right = root;

    int n;
    cout << "Enter number of nodes to insert: ";
    cin >> n;

    cout << "Enter " << n << " values: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        insertIntoTBST(root, val);
    }

    cout << "Inorder Traversal of TBST: ";
    inorderTraversal(root);

    return 0;
}
