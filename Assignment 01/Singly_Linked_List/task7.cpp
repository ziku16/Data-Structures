#include <iostream>
using namespace std;

// Node structure for numbered warehouse box
struct Node {
    int boxNumber;
    Node* next;

    Node(int num) {
        boxNumber = num;
        next = nullptr;
    }
};

// Helper function to reverse a linked list segment in-place.
// Returns the new head and sets tail out-parameter to the original head (new tail).
Node* reverseSegment(Node* head, Node*& segmentTail) {
    segmentTail = head; // Original head will become the tail after reversal
    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    return prev; // New head of reversed segment
}

// Function to reverse first half and second half separately
void reverseHalves(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return; // Nothing to reverse if list is empty or has 1 element
    }

    // Step 1: Count total number of boxes
    int totalBoxes = 0;
    Node* temp = head;
    while (temp != nullptr) {
        totalBoxes++;
        temp = temp->next;
    }

    int halfSize = totalBoxes / 2;

    // Step 2: Traverse to the end of the first half
    Node* firstHalfEnd = head;
    for (int i = 1; i < halfSize; i++) {
        firstHalfEnd = firstHalfEnd->next;
    }

    // Step 3: Split into two separate lists
    Node* secondHalfHead = firstHalfEnd->next;
    firstHalfEnd->next = nullptr; // Terminate first half

    // Step 4: Reverse both halves in-place
    Node* firstHalfTail = nullptr;
    Node* newFirstHalfHead = reverseSegment(head, firstHalfTail);

    Node* secondHalfTail = nullptr;
    Node* newSecondHalfHead = reverseSegment(secondHalfHead, secondHalfTail);

    // Step 5: Connect tail of reversed first half to head of reversed second half
    firstHalfTail->next = newSecondHalfHead;

    // Step 6: Update head of the overall list
    head = newFirstHalfHead;
}

// Function to display boxes
void displayBoxes(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->boxNumber;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

// Helper to append box
void addBox(Node*& head, int num) {
    Node* newNode = new Node(num);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Memory cleanup
void freeList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* boxes = nullptr;

    // Populate boxes 1 through 8
    for (int i = 1; i <= 8; i++) {
        addBox(boxes, i);
    }

    cout << "=== Original Warehouse Boxes Order ===" << endl;
    displayBoxes(boxes);

    // Perform reversal of first half and second half separately
    reverseHalves(boxes);

    cout << "\n=== Rearranged Warehouse Boxes Order ===" << endl;
    cout << "Expected Output: 4 -> 3 -> 2 -> 1 -> 8 -> 7 -> 6 -> 5" << endl;
    cout << "Actual Output:   ";
    displayBoxes(boxes);

    freeList(boxes);
    return 0;
}
