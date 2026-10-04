#include <iostream>
#include <string>
using namespace std;

// Node structure representing a book in library catalog
struct Node {
    int bookId;
    string title;
    Node* next;

    Node(int id, string bookTitle) {
        bookId = id;
        title = bookTitle;
        next = nullptr;
    }
};

// Function to delete all instances of a given book identifier from the catalog.
// Handles beginning (head), middle, end (tail), and multiple/all matches.
void deleteAllBookInstances(Node*& head, int targetId) {
    // 1. Handle deletion at the beginning (head matches targetId)
    while (head != nullptr && head->bookId == targetId) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    if (head == nullptr) {
        return; // List was empty or contained only targetId nodes
    }

    // 2. Handle deletion in the middle or end
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->bookId == targetId) {
            Node* temp = current->next;
            current->next = current->next->next; // Bypass node to delete
            delete temp;
        } else {
            current = current->next;
        }
    }
}

// Function to display catalog
void displayCatalog(Node* head) {
    if (!head) {
        cout << "[Catalog is empty]" << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->bookId << " | Title: \"" << temp->title << "\"" << endl;
        temp = temp->next;
    }
}

// Helper to add book
void addBook(Node*& head, int id, string title) {
    Node* newNode = new Node(id, title);
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
    Node* library = nullptr;

    // Populate catalog with target ID (101) at beginning, middle, end, and multiple times
    addBook(library, 101, "Data Structures and Algorithms"); // Match at head
    addBook(library, 101, "Data Structures Duplicate Copy");  // Match at head (consecutive)
    addBook(library, 202, "Clean Code");
    addBook(library, 101, "Data Structures Special Edition"); // Match in middle
    addBook(library, 303, "Design Patterns");
    addBook(library, 101, "Data Structures Hardcover");      // Match at end

    cout << "=== Initial Library Catalog ===" << endl;
    displayCatalog(library);

    int targetToDelete = 101;
    cout << "\n=== Deleting All Copies of Book ID: " << targetToDelete << " ===" << endl;
    deleteAllBookInstances(library, targetToDelete);

    cout << "\n=== Updated Library Catalog ===" << endl;
    displayCatalog(library);

    freeList(library);
    return 0;
}
