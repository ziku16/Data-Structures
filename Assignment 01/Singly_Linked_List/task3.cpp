#include <iostream>
#include <string>
using namespace std;

// Node structure for contact
struct Node {
    string contactName;
    string phoneNumber;
    Node* next;

    Node(string name, string phone) {
        contactName = name;
        phoneNumber = phone;
        next = nullptr;
    }
};

// Function to remove duplicates without using any extra arrays, vectors, or built-in containers.
// Employs a two-pointer nested traversal approach (O(1) auxiliary memory space).
void removeDuplicates(Node* head) {
    Node* current = head;

    // Outer loop traverses each node in the list
    while (current != nullptr) {
        Node* runner = current;

        // Inner loop checks subsequent nodes for duplicate contact names
        while (runner->next != nullptr) {
            if (runner->next->contactName == current->contactName) {
                // Duplicate found: bypass and delete duplicate node
                Node* duplicate = runner->next;
                runner->next = runner->next->next; // Update link to skip duplicate
                delete duplicate;                  // Free memory of duplicate
            } else {
                runner = runner->next; // Advance inner pointer
            }
        }
        current = current->next; // Advance outer pointer
    }
}

// Function to display contact list
void displayContacts(Node* head) {
    Node* temp = head;
    if (!temp) {
        cout << "Contact list is empty." << endl;
        return;
    }
    while (temp != nullptr) {
        cout << "- " << temp->contactName << " (" << temp->phoneNumber << ")" << endl;
        temp = temp->next;
    }
}

// Helper to insert contact at end
void addContact(Node*& head, string name, string phone) {
    Node* newNode = new Node(name, phone);
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

// Free memory
void freeList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* contacts = nullptr;

    // Populate contacts with duplicates
    addContact(contacts, "Alice Smith", "123-456-7890");
    addContact(contacts, "Bob Jones", "987-654-3210");
    addContact(contacts, "Alice Smith", "123-456-7890"); // Duplicate
    addContact(contacts, "Charlie Brown", "555-123-4567");
    addContact(contacts, "Bob Jones", "987-654-3210"); // Duplicate
    addContact(contacts, "Diana Prince", "444-999-0000");

    cout << "=== Contact List Before Duplicate Removal ===" << endl;
    displayContacts(contacts);

    // Remove duplicate entries
    removeDuplicates(contacts);

    cout << "\n=== Contact List After Duplicate Removal ===" << endl;
    displayContacts(contacts);

    freeList(contacts);
    return 0;
}
