#include <iostream>
using namespace std;

// Doubly Linked List Node representing a theater seat
struct Node {
    int seatNumber;
    Node* prev;
    Node* next;

    Node(int num) {
        seatNumber = num;
        prev = nullptr;
        next = nullptr;
    }
};

// Function to rearrange seats according to the theater seating pattern:
// First and last seats remain fixed (aisle seats).
// From both ends inward, seats are alternately swapped toward the center.
// Memory addresses of all nodes remain unchanged.
void rearrangeTheaterSeats(Node* head, Node* tail) {
    if (head == nullptr || head == tail || head->next == tail) {
        return; // Need at least 3 seats to have inner seats to swap
    }

    // First seat (head) and last seat (tail) remain fixed.
    // Start left pointer at head->next (pos 1) and right pointer at tail->prev (pos N-2)
    Node* left = head->next;
    Node* right = tail->prev;

    bool shouldSwap = true;

    while (left != nullptr && right != nullptr && left != right && left->prev != right) {
        if (shouldSwap) {
            // Swap seat numbers between symmetric inner nodes
            int temp = left->seatNumber;
            left->seatNumber = right->seatNumber;
            right->seatNumber = temp;
        }

        // Alternate the swap flag (swap, skip, swap, skip...)
        shouldSwap = !shouldSwap;

        // Move left inward to next seat, and right inward to prev seat
        left = left->next;
        right = right->prev;
    }
}

// Function to display seats with memory addresses
void displaySeats(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->seatNumber << " [Address: " << temp << "]";
        if (temp->next != nullptr) cout << " <-> ";
        temp = temp->next;
    }
    cout << endl;
}

// Helper to append seat node
void addSeat(Node*& head, Node*& tail, int seatNum) {
    Node* newNode = new Node(seatNum);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
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
    Node* head = nullptr;
    Node* tail = nullptr;

    // Original seat order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
    for (int i = 1; i <= 9; i++) {
        addSeat(head, tail, i);
    }

    cout << "=== Original Theater Seat Order ===" << endl;
    displaySeats(head);

    // Apply seating pattern
    rearrangeTheaterSeats(head, tail);

    cout << "\n=== Rearranged Theater Seat Order ===" << endl;
    cout << "Expected Output: 1 <-> 8 <-> 3 <-> 6 <-> 5 <-> 4 <-> 7 <-> 2 <-> 9" << endl;
    cout << "Actual Output:   ";
    displaySeats(head);

    freeList(head);
    return 0;
}
