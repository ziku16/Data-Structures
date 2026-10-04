#include <iostream>
#include <string>
using namespace std;

// Node structure for hobby stamp collection
struct Node {
    string stampDesign;
    int issueYear;
    Node* next;

    Node(string design, int year) {
        stampDesign = design;
        issueYear = year;
        next = nullptr;
    }
};

// Function to remove duplicate stamp designs in-place.
// Uses nested pointer traversal without external vectors, arrays, or hash sets (O(1) auxiliary space).
void removeDuplicateStamps(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        Node* runner = current;

        // Traverse remaining list to identify matching stamp designs
        while (runner->next != nullptr) {
            if (runner->next->stampDesign == current->stampDesign) {
                // Delete duplicate node and re-link pointers
                Node* duplicateNode = runner->next;
                runner->next = runner->next->next;
                delete duplicateNode;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

// Function to display stamp collection
void displayStamps(Node* head) {
    if (!head) {
        cout << "Collection is empty." << endl;
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        cout << "- " << temp->stampDesign << " (" << temp->issueYear << ")" << endl;
        temp = temp->next;
    }
}

// Helper to add stamp
void addStamp(Node*& head, string design, int year) {
    Node* newNode = new Node(design, year);
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
    Node* stampCollection = nullptr;

    // Add stamps with duplicate designs
    addStamp(stampCollection, "Penny Black", 1840);
    addStamp(stampCollection, "Inverted Jenny", 1918);
    addStamp(stampCollection, "Penny Black", 1840); // Duplicate
    addStamp(stampCollection, "Mauritius Post Office", 1847);
    addStamp(stampCollection, "Inverted Jenny", 1918); // Duplicate
    addStamp(stampCollection, "Tre Skilling Yellow", 1855);

    cout << "=== Original Stamp Collection (With Duplicates) ===" << endl;
    displayStamps(stampCollection);

    // Remove duplicate designs
    removeDuplicateStamps(stampCollection);

    cout << "\n=== Unique Stamp Collection (After Removing Duplicates) ===" << endl;
    displayStamps(stampCollection);

    freeList(stampCollection);
    return 0;
}
