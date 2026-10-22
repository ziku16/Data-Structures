#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Inserts a new value respecting BST properties (left < root < right)
Node* insert(Node* root, int val) {
    if (!root) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

// Prints leaf values and returns the total count of leaf nodes
int printAndCountLeaves(const Node* root) {
    if (!root) {
        return 0;
    }

    // A leaf node has no left and no right child
    if (!root->left && !root->right) {
        cout << root->data << " ";
        return 1;
    }

    // Recurse down both subtrees and aggregate counts
    return printAndCountLeaves(root->left) + printAndCountLeaves(root->right);
}

// Helper to free allocated memory
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    /*
             50
           /    \
         30      70
        /  \    /  \
       20  40  60  80

       Leaves are: 20, 40, 60, 80 (Count = 4)
    */

    Node* root = nullptr;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int v : values) {
        root = insert(root, v);
    }

    cout << "Leaf nodes: ";
    int leafCount = printAndCountLeaves(root);
    cout << "\nTotal leaf count: " << leafCount << "\n";

    deleteTree(root);
    return 0;
}