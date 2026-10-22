#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    explicit Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

// Returns node height or 0 for null pointers
int getHeight(const Node* n) {
    return n ? n->height : 0;
}

// Balance factor = height(left) - height(right)
int getBalance(const Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Recalculates height based on child heights
void updateHeight(Node* n) {
    if (n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }
}

// ----------------------------------------------------
// 1. Right Rotation (Handles LL Imbalance)
// ----------------------------------------------------
//       y                               x
//      / \     Rotate Right (y)        / \
//     x   T3   --------------->       T1  y
//    / \                                 / \
//   T1  T2                              T2  T3
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights bottom-up (y first, then x)
    updateHeight(y);
    updateHeight(x);

    return x; // New subtree root
}

// ----------------------------------------------------
// 2. Left Rotation (Handles RR Imbalance)
// ----------------------------------------------------
//     x                                   y
//    / \       Rotate Left (x)           / \
//   T1  y      -------------->          x   T3
//      / \                             / \
//     T2  T3                          T1  T2
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights bottom-up (x first, then y)
    updateHeight(x);
    updateHeight(y);

    return y; // New subtree root
}

// ----------------------------------------------------
// 3. LR Rotation (Left-Right Imbalance)
// ----------------------------------------------------
// Left rotation on left child, then right rotation on root
Node* rotateLeftRight(Node* root) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

// ----------------------------------------------------
// 4. RL Rotation (Right-Left Imbalance)
// ----------------------------------------------------
// Right rotation on right child, then left rotation on root
Node* rotateRightLeft(Node* root) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

// Inserts a key and automatically applies the appropriate rotation
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicate keys not allowed in standard AVL
    }

    // Step 1: Update node height
    updateHeight(node);

    // Step 2: Check balance factor
    int balance = getBalance(node);

    // Case 1: LL Imbalance
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Case 2: RR Imbalance
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Case 3: LR Imbalance
    if (balance > 1 && key > node->left->key) {
        return rotateLeftRight(node);
    }

    // Case 4: RL Imbalance
    if (balance < -1 && key < node->right->key) {
        return rotateRightLeft(node);
    }

    return node;
}

// Pre-order traversal to verify tree structure: Node (BF)
void preOrder(const Node* root) {
    if (!root) return;
    cout << root->key << " (BF: " << getBalance(root) << ") ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node* root = nullptr;

    /* Inserting keys that trigger rotations:
       10, 20, 30 -> triggers RR rotation
       40, 50     -> triggers RR rotation
       25         -> triggers RL rotation
    */
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int k : keys) {
        root = insert(root, k);
    }

    cout << "Pre-order traversal of constructed AVL tree:\n";
    preOrder(root);
    cout << "\n";

    return 0;
}