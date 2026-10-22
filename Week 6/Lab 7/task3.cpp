#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Helper: finds the node with the minimum value in a subtree (leftmost node)
Node* findMin(Node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Inserts a new value respecting BST properties
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

// Deletes a node with the specified key handling all 3 cases
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    // Step 1: Traverse the tree to find the node
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Target node found; handle the 3 deletion cases:

        // Case 1: No child (Leaf node)
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }

        // Case 2a: Only right child exists
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2b: Only left child exists
        if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Both children exist
        // Find in-order successor (smallest node in the right subtree)
        Node* successor = findMin(root->right);

        // Copy successor value to this node
        root->data = successor->data;

        // Delete the successor from the right subtree
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

// In-order traversal helper to inspect the tree (always sorted)
void inOrder(const Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

int main() {
    /*
             50
           /    \
         30      70
        /  \    /  \
       20  40  60  80
    */
    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        root = insert(root, v);
    }

    cout << "Initial tree (in-order): ";
    inOrder(root);
    cout << "\n";

    // Test Case 1: Delete a leaf node (20)
    root = deleteNode(root, 20);
    cout << "After deleting 20 (Leaf): ";
    inOrder(root);
    cout << "\n";

    // Test Case 2: Delete a node with one child (30 now has only child 40)
    root = deleteNode(root, 30);
    cout << "After deleting 30 (One child): ";
    inOrder(root);
    cout << "\n";

    // Test Case 3: Delete a node with two children (50 has 40 and 70)
    root = deleteNode(root, 50);
    cout << "After deleting 50 (Two children): ";
    inOrder(root);
    cout << "\n";

    return 0;
}