#include <iostream>
using namespace std;

// Node structure for Circular Singly Linked List
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Append a node at the end of the circular linked list
void insertEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        return;
    }

    Node* curr = head;
    while (curr->next != head) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->next = head;
}

// Display the circular linked list
void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* curr = head;
    do {
        cout << curr->data;
        curr = curr->next;
        if (curr != head) cout << " -> ";
    } while (curr != head);
    cout << " -> (back to head: " << head->data << ")" << endl;
}

// Deletes all nodes at even positions (1-based: 2, 4, 6, ...)
// If the last node is at an even position, it is also deleted and circular link is updated.
void deleteEvenPositionedNodes(Node*& head) {
    if (head == nullptr || head->next == head) {
        return; // Empty list or single node (pos 1 is odd, nothing to delete)
    }

    // Determine the total number of nodes in the circular list
    int total = 1;
    Node* temp = head;
    while (temp->next != head) {
        total++;
        temp = temp->next;
    }

    int evenCount = total / 2; // Total even-positioned nodes to eliminate
    Node* curr = head;

    for (int i = 0; i < evenCount; i++) {
        Node* evenNode = curr->next;     // Node at the even position
        curr->next = evenNode->next;     // Bypass even node to connect to next odd node
        delete evenNode;
        curr = curr->next;               // Advance to the newly connected odd node
    }
}

// Free memory allocated for the circular list
void freeList(Node*& head) {
    if (head == nullptr) return;
    Node* curr = head;
    Node* nextNode = nullptr;
    while (curr->next != head) {
        nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    delete curr;
    head = nullptr;
}

int main() {
    cout << "=== Case 1: Even Number of Nodes (6 elements, last node is even) ===" << endl;
    Node* list1 = nullptr;
    for (int i = 1; i <= 6; i++) {
        insertEnd(list1, i * 10);
    }
    cout << "Original List: ";
    display(list1);

    deleteEvenPositionedNodes(list1);
    cout << "After Deleting Even Positions: ";
    display(list1);
    freeList(list1);

    cout << "\n=== Case 2: Odd Number of Nodes (5 elements, last node is odd) ===" << endl;
    Node* list2 = nullptr;
    for (int i = 1; i <= 5; i++) {
        insertEnd(list2, i * 10);
    }
    cout << "Original List: ";
    display(list2);

    deleteEvenPositionedNodes(list2);
    cout << "After Deleting Even Positions: ";
    display(list2);
    freeList(list2);

    return 0;
}
