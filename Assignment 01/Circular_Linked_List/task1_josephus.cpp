#include <iostream>
using namespace std;

// Node structure for Josephus Circle
struct Node {
    int personId;
    Node* next;

    Node(int id) {
        personId = id;
        next = nullptr;
    }
};

// Function to solve the Josephus Problem using a Circular Linked List.
// N = total number of persons, M = count at which the M-th person is eliminated.
int solveJosephus(int N, int M) {
    if (N <= 0 || M <= 0) return -1;

    // Step 1: Create a Circular Linked List with N persons (1 to N)
    Node* head = new Node(1);
    Node* prev = head;

    for (int i = 2; i <= N; i++) {
        Node* newNode = new Node(i);
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Point tail back to head to make it circular

    // Step 2: Simulate elimination process
    Node* curr = head;
    Node* prevNode = prev; // Points to the node preceding head

    cout << "Elimination order: ";
    while (curr->next != curr) { // Continue until only 1 person remains
        // Skip M - 1 persons
        for (int count = 1; count < M; count++) {
            prevNode = curr;
            curr = curr->next;
        }

        // Eliminate M-th person
        cout << curr->personId << " ";
        prevNode->next = curr->next; // Bypass eliminated node
        Node* temp = curr;
        curr = curr->next;           // Move to next person in circle
        delete temp;                 // Free memory of eliminated person
    }

    int survivor = curr->personId;
    delete curr; // Clean up remaining survivor node
    cout << endl;

    return survivor;
}

int main() {
    int N = 7; // Total persons
    int M = 3; // Elimination step

    cout << "=== Josephus Problem Solver ===" << endl;
    cout << "Total persons (N): " << N << endl;
    cout << "Elimination step (M): " << M << endl;

    int survivor = solveJosephus(N, M);

    cout << "\nSafe Position to Survive: Person #" << survivor << endl;
    return 0;
}
