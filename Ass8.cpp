#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node *left, *right;
    bool lf, rf; // lf and rf indicate whether left/right pointers are threads

    Node(int x) {
        val = x;
        left = right = nullptr;
        lf = rf = false;
    }
};

// Insert node into normal BST
Node* insertBST(Node* root, int key) {
    if (!root)
        return new Node(key);

    if (key < root->val)
        root->left = insertBST(root->left, key);
    else
        root->right = insertBST(root->right, key);

    return root;
}

// Convert BST to Inorder Threaded BST
void convertToThreaded(Node* root, Node*& prev, Node* dummy) {
    if (!root) return;

    convertToThreaded(root->left, prev, dummy);

    if (!root->left) {
        root->left = prev;
        root->lf = true;
    }

    if (prev && !prev->right) {
        prev->right = root;
        prev->rf = true;
    }

    prev = root;

    convertToThreaded(root->right, prev, dummy);
}

// Find the leftmost node (used in traversal)
Node* leftMost(Node* node, Node* dummy) {
    while (node && !node->lf && node->left != dummy)
        node = node->left;
    return node;
}

// Inorder traversal of threaded BST
void inorderTraversal(Node* root, Node* dummy) {
    Node* curr = leftMost(root, dummy);
    while (curr && curr != dummy) {
        cout << curr->val << " ";
        if (curr->rf)
            curr = curr->right;
        else
            curr = leftMost(curr->right, dummy);
    }
    cout << endl;
}

int main() {
    Node* bstRoot = nullptr;
    int n, val;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter " << n << " node values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        bstRoot = insertBST(bstRoot, val);
    }

    // Dummy node as threaded BST root
    Node* dummy = new Node(-1);
    dummy->left = bstRoot;
    dummy->right = dummy;
    dummy->lf = dummy->rf = false;

    Node* prev = dummy;
    convertToThreaded(bstRoot, prev, dummy);

    // Connect the last node's right to dummy
    if (prev) {
        prev->right = dummy;
        prev->rf = true;
    }

    cout << "Inorder Traversal of Threaded BST: ";
    inorderTraversal(bstRoot, dummy);

    return 0;
}
