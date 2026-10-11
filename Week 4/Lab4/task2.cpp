#include <iostream>
using namespace std;

// Node representing a person in the elimination circle
struct Node {
    int id;
    Node* next;

    Node(int val) : id(val), next(nullptr) {}
};

// Builds a circular linked list of n people labeled 1 to n
Node* createCircle(int n) {
    if (n <= 0) return nullptr;

    Node* head = new Node(1);
    Node* prev = head;

    for (int i = 2; i <= n; i++) {
        Node* newNode = new Node(i);
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Close circle by linking last node to head
    return head;
}

// Solves Josephus problem by eliminating every k-th person until one remains
int josephus(int n, int k) {
    if (n <= 0 || k <= 0) {
        cout << "Invalid input values." << endl;
        return -1;
    }

    Node* head = createCircle(n);

    // Find the node right before head to manage deletion easily
    Node* prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    Node* curr = head;
    cout << "Elimination order (every " << k << "-th person): ";

    // Repeat elimination until a single node points to itself
    while (curr->next != curr) {
        // Count k - 1 steps to reach the k-th person
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }

        cout << curr->id << " ";

        // Bypass and delete the eliminated person
        prev->next = curr->next;
        Node* eliminated = curr;
        curr = curr->next; // Next countdown starts from the immediate successor
        delete eliminated;
    }

    cout << endl;
    int survivor = curr->id;
    delete curr; // Free the last remaining node
    return survivor;
}

int main() {
    int n = 7;
    int k = 3;

    cout << "=== Josephus Problem Simulation ===" << endl;
    cout << "Number of people (n): " << n << endl;
    cout << "Step count (k): " << k << endl;

    int winner = josephus(n, k);
    cout << "Survivor (Winner): Person " << winner << endl;

    cout << "\n=== Second Simulation ===" << endl;
    n = 5;
    k = 2;
    cout << "Number of people (n): " << n << ", Step count (k): " << k << endl;
    winner = josephus(n, k);
    cout << "Survivor (Winner): Person " << winner << endl;

    return 0;
}
