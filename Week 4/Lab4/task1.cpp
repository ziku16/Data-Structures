#include <iostream>
using namespace std;

// Node structure for Circular Singly Linked List
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Insert a node at the end of the circular linked list
void insertEnd(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head; // Point to itself to maintain circularity
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

// Helper to find the last node in the circular list
Node* getLastNode(Node* head) {
    if (head == nullptr) return nullptr;
    Node* curr = head;
    while (curr->next != head) {
        curr = curr->next;
    }
    return curr;
}

// Delete all nodes containing even or odd values based on deleteEven flag
void deleteByParity(Node*& head, bool deleteEven) {
    if (head == nullptr) return;

    // Phase 1: Remove matching nodes from the beginning (head updates require fixing the tail link)
    Node* last = getLastNode(head);
    while (head != nullptr && ((head->data % 2 == 0) == deleteEven)) {
        // If only a single node exists and it matches
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        Node* temp = head;
        head = head->next;
        last->next = head; // Tail must always link back to new head
        delete temp;
    }

    if (head == nullptr) return;

    // Phase 2: Traverse and remove matching nodes from the rest of the circle
    Node* curr = head;
    while (curr->next != head) {
        if ((curr->next->data % 2 == 0) == deleteEven) {
            Node* toDelete = curr->next;
            curr->next = toDelete->next; // Bypass the matching node
            delete toDelete;
        } else {
            curr = curr->next;
        }
    }
}

// Deletes all even-valued nodes
void deleteEvenNodes(Node*& head) {
    deleteByParity(head, true);
}

// Deletes all odd-valued nodes
void deleteOddNodes(Node*& head) {
    deleteByParity(head, false);
}

// Free all memory allocated for the circular list
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
    Node* list1 = nullptr;
    int values1[] = {12, 7, 18, 21, 34, 45, 50};
    for (int v : values1) insertEnd(list1, v);

    cout << "=== Demonstration 1: Deleting Even Values ===" << endl;
    cout << "Initial List: ";
    display(list1);

    deleteEvenNodes(list1);
    cout << "After Deleting Even Nodes: ";
    display(list1);

    freeList(list1);

    cout << "\n=== Demonstration 2: Deleting Odd Values ===" << endl;
    Node* list2 = nullptr;
    int values2[] = {11, 24, 35, 48, 59, 62, 77};
    for (int v : values2) insertEnd(list2, v);

    cout << "Initial List: ";
    display(list2);

    deleteOddNodes(list2);
    cout << "After Deleting Odd Nodes: ";
    display(list2);

    freeList(list2);
    return 0;
}
