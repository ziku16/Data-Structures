#include <iostream>
#include <string>
using namespace std;

// Node structure representing a friend in line
struct Node {
    string name;
    Node* next;

    Node(string friendName) {
        name = friendName;
        next = nullptr;
    }
};

// Function to find the middle friend in a singly linked list.
// If count is odd: returns the single center friend.
// If count is even: returns the left-center friend (the one standing to the left of center).
Node* findMiddleFriend(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* slow = head;
    Node* fast = head;

    // Fast pointer moves 2 steps, slow pointer moves 1 step.
    // By checking (fast->next != nullptr && fast->next->next != nullptr),
    // when fast reaches the end, slow points directly to the center (odd count) 
    // or the left-center friend (even count).
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Helper to add friend to line
void addFriend(Node*& head, string name) {
    Node* newNode = new Node(name);
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

// Display line of friends
void displayLine(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "[" << temp->name << "]";
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
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
    // Test Case 1: Odd number of friends (5 friends)
    Node* oddGroup = nullptr;
    addFriend(oddGroup, "Alice");
    addFriend(oddGroup, "Bob");
    addFriend(oddGroup, "Charlie");
    addFriend(oddGroup, "Dana");
    addFriend(oddGroup, "Eva");

    cout << "=== Test 1: Odd Number of Friends (5 Friends) ===" << endl;
    cout << "Line: ";
    displayLine(oddGroup);
    Node* midOdd = findMiddleFriend(oddGroup);
    if (midOdd) {
        cout << "Middle Friend (Exact Center): " << midOdd->name << endl;
    }

    // Test Case 2: Even number of friends (6 friends)
    Node* evenGroup = nullptr;
    addFriend(evenGroup, "Alice");
    addFriend(evenGroup, "Bob");
    addFriend(evenGroup, "Charlie");
    addFriend(evenGroup, "Dana");
    addFriend(evenGroup, "Eva");
    addFriend(evenGroup, "Frank");

    cout << "\n=== Test 2: Even Number of Friends (6 Friends) ===" << endl;
    cout << "Line: ";
    displayLine(evenGroup);
    Node* midEven = findMiddleFriend(evenGroup);
    if (midEven) {
        cout << "Middle Friend (Left-Center Choice): " << midEven->name << endl;
    }

    freeList(oddGroup);
    freeList(evenGroup);
    return 0;
}
