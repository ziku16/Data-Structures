#include <iostream>
#include <string>
using namespace std;

// Doubly Linked List Node for office desk
struct Node {
    string name;
    Node* prev;
    Node* next;

    Node(string personName) {
        name = personName;
        prev = nullptr;
        next = nullptr;
    }
};

// Function to swap desks starting from ends toward center by modifying doubly linked list pointers.
// Addresses of nodes remain fixed in memory.
void swapDesks(Node*& head, Node*& tail) {
    if (head == nullptr || head == tail) {
        return;
    }

    Node* current = head;
    Node* temp = nullptr;

    // Traverse the doubly linked list and swap 'prev' and 'next' pointers for each node
    while (current != nullptr) {
        // Swap next and prev pointers of current node
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to original 'next' node (which is now stored in current->prev after swap)
        current = current->prev;
    }

    // Update head and tail pointers
    if (temp != nullptr) {
        tail = head;
        head = temp->prev;
    }
}

// Function to display desk arrangement from head to tail with addresses
void displayDesks(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "[" << temp->name << " | Node Addr: " << temp << "]";
        if (temp->next != nullptr) cout << " <-> ";
        temp = temp->next;
    }
    cout << endl;
}

// Helper to append desk
void addDesk(Node*& head, Node*& tail, string name) {
    Node* newNode = new Node(name);
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

    // Initial arrangement: Alice, Bob, Charlie, Dana, Eva, Frank
    addDesk(head, tail, "Alice");
    addDesk(head, tail, "Bob");
    addDesk(head, tail, "Charlie");
    addDesk(head, tail, "Dana");
    addDesk(head, tail, "Eva");
    addDesk(head, tail, "Frank");

    cout << "=== Initial Office Desk Arrangement ===" << endl;
    displayDesks(head);

    // Swap desks from ends to center
    swapDesks(head, tail);

    cout << "\n=== Rearranged Office Desk Arrangement (Symmetric End Swaps) ===" << endl;
    cout << "Expected: Frank <-> Eva <-> Dana <-> Charlie <-> Bob <-> Alice" << endl;
    cout << "Actual:   ";
    displayDesks(head);

    freeList(head);
    return 0;
}
