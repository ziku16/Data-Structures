#include <iostream>
using namespace std;

// Node structure representing a customer's fruit price in shopping cart
struct Node {
    int price;
    Node* next;

    Node(int p) {
        price = p;
        next = nullptr;
    }
};

// Function to partition shopping cart linked list into two separate lists:
// 1. Even-priced fruits list
// 2. Odd-priced fruits list
// Operates strictly in-place by updating pointer links. No new nodes are created.
void partitionEvenOdd(Node* head, Node*& evenHead, Node*& oddHead) {
    evenHead = nullptr;
    oddHead = nullptr;
    Node* evenTail = nullptr;
    Node* oddTail = nullptr;

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next; // Save next pointer
        current->next = nullptr;       // Isolate current node

        if (current->price % 2 == 0) {
            // Even price
            if (evenHead == nullptr) {
                evenHead = evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {
            // Odd price
            if (oddHead == nullptr) {
                oddHead = oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }
        current = nextNode; // Move to next item
    }
}

// Function to display list of fruit prices along with node memory addresses
void displayList(Node* head) {
    if (!head) {
        cout << "List is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << "$" << temp->price << " [Node Address: " << temp << "]";
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

// Helper to insert item
void addFruitPrice(Node*& head, int price) {
    Node* newNode = new Node(price);
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
    Node* cart = nullptr;

    // Add fruit prices (mix of even and odd)
    addFruitPrice(cart, 12);
    addFruitPrice(cart, 7);
    addFruitPrice(cart, 15);
    addFruitPrice(cart, 24);
    addFruitPrice(cart, 9);
    addFruitPrice(cart, 18);
    addFruitPrice(cart, 30);
    addFruitPrice(cart, 5);

    cout << "=== Original Customer Shopping Cart ===" << endl;
    displayList(cart);

    Node* evenLine = nullptr;
    Node* oddLine = nullptr;

    // Divide list into even and odd lines
    partitionEvenOdd(cart, evenLine, oddLine);

    cout << "\n=== Line 1: Even-Priced Fruits ===" << endl;
    displayList(evenLine);

    cout << "\n=== Line 2: Odd-Priced Fruits ===" << endl;
    displayList(oddLine);

    cout << "\nNote: Memory addresses of all nodes remain identical to original nodes." << endl;

    freeList(evenLine);
    freeList(oddLine);
    return 0;
}
