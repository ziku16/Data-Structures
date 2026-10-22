#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Traversal: Node -> Right -> Left
void preOrderNRL(const TreeNode* root) {
    if (!root) return;

    cout << root->val << " ";
    preOrderNRL(root->right);
    preOrderNRL(root->left);
}

// Traversal: Right -> Node -> Left
void inOrderRNL(const TreeNode* root) {
    if (!root) return;

    inOrderRNL(root->right);
    cout << root->val << " ";
    inOrderRNL(root->left);
}

// Traversal: Right -> Left -> Node
void postOrderRLN(const TreeNode* root) {
    if (!root) return;

    postOrderRLN(root->right);
    postOrderRLN(root->left);
    cout << root->val << " ";
}

int main() {
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    // Expected: 1 3 6 2 5 4
    cout << "Pre-order (NRL):  ";
    preOrderNRL(root);
    cout << "\n";

    // Expected: 6 3 1 5 2 4
    cout << "In-order (RNL):   ";
    inOrderRNL(root);
    cout << "\n";

    // Expected: 6 3 5 4 2 1
    cout << "Post-order (RLN): ";
    postOrderRLN(root);
    cout << "\n";

    delete root->right->right;
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;

    return 0;
}