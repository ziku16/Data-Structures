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

// Function to reverse elements before middle and after middle
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

    if (totalBoxes % 2 == 0) {
        // EVEN length: Split into two equal halves
        Node* firstHalfEnd = head;
        for (int i = 1; i < halfSize; i++) {
            firstHalfEnd = firstHalfEnd->next;
        }

        Node* secondHalfHead = firstHalfEnd->next;
        firstHalfEnd->next = nullptr; // Terminate first half

        Node* firstHalfTail = nullptr;
        Node* newFirstHalfHead = reverseSegment(head, firstHalfTail);

        Node* secondHalfTail = nullptr;
        Node* newSecondHalfHead = reverseSegment(secondHalfHead, secondHalfTail);

        firstHalfTail->next = newSecondHalfHead;
        head = newFirstHalfHead;
    } else {
        // ODD length: Elements before mid are reversed, mid stays fixed, elements after mid are reversed
        Node* firstHalfEnd = head;
        for (int i = 1; i < halfSize; i++) {
            firstHalfEnd = firstHalfEnd->next;
        }

        Node* midNode = firstHalfEnd->next;
        firstHalfEnd->next = nullptr; // Terminate first half

        Node* secondHalfHead = midNode->next;
        midNode->next = nullptr; // Isolate mid node

        Node* firstHalfTail = nullptr;
        Node* newFirstHalfHead = reverseSegment(head, firstHalfTail);

        Node* secondHalfTail = nullptr;
        Node* newSecondHalfHead = reverseSegment(secondHalfHead, secondHalfTail);

        // Connect: reversed first half -> midNode -> reversed second half
        firstHalfTail->next = midNode;
        midNode->next = newSecondHalfHead;

        head = newFirstHalfHead;
    }
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
    for (int i = 1; i <= 9; i++) {
        addBox(boxes, i);
    }

    cout << "=== Original Order ===" << endl;
    cout << "Original: "; 
    displayBoxes(boxes);

    // Perform reversal of first half and second half separately
    reverseHalves(boxes);

    cout << "\n=== Rearranged Order ===" << endl;
    cout << "Output: ";
    displayBoxes(boxes);

    freeList(boxes);
    return 0;
}
