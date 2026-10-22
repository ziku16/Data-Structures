#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    explicit Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(const Node* n) {
    return n ? n->height : 0;
}

int getBalance(const Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

void updateHeight(Node* n) {
    if (n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    updateHeight(node);
    int balance = getBalance(node);

    // Left-Left (LL) Case
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right-Right (RR) Case
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left-Right (LR) Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left (RL) Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Traverses and prints nodes layer by layer using a FIFO queue
void levelOrderTraversal(const Node* root) {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    queue<const Node*> q;
    q.push(root);

    int level = 0;
    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes present at the current depth
        cout << "Level " << level++ << ": ";

        for (int i = 0; i < levelSize; ++i) {
            const Node* current = q.front();
            q.pop();

            cout << current->key << " [BF: " << getBalance(current) << "]  ";

            if (current->left)  q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << "\n";
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    /*
       Inserting keys: 10, 20, 30, 40, 50, 25
       The AVL rotations balance the tree into:
                 30
               /    \
             20      40
            /  \       \
           10  25       50
    */
    Node* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int k : keys) {
        root = insert(root, k);
    }

    cout << "Level Order Traversal of AVL Tree:\n";
    levelOrderTraversal(root);

    deleteTree(root);
    return 0;
}