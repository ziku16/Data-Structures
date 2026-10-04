#include <iostream>
#include <string>
using namespace std;

// Node structure for playlist song
struct Node {
    string songTitle;
    Node* next;

    Node(string title) {
        songTitle = title;
        next = nullptr;
    }
};

// Function to reverse playlist in-place by changing pointer links only.
// Node memory addresses remain exactly the same.
void reversePlaylist(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next; // Store next node pointer
        current->next = prev;     // Reverse current node's pointer direction
        prev = current;           // Move prev forward
        current = nextNode;       // Move current forward
    }
    
    head = prev; // Update head to point to the new first element (originally last element)
}

// Function to display playlist along with node memory addresses
void displayPlaylist(Node* head) {
    Node* temp = head;
    int count = 1;
    while (temp != nullptr) {
        cout << count++ << ". " << temp->songTitle << " [Node Address: " << temp << "]" << endl;
        temp = temp->next;
    }
}

// Helper to append song
void addSong(Node*& head, string title) {
    Node* newNode = new Node(title);
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
void freePlaylist(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* playlist = nullptr;

    addSong(playlist, "Bohemian Rhapsody");
    addSong(playlist, "Hotel California");
    addSong(playlist, "Stairway to Heaven");
    addSong(playlist, "Imagine");
    addSong(playlist, "Sweet Child O' Mine");

    cout << "=== Original Playlist (Forward Traversal) ===" << endl;
    displayPlaylist(playlist);

    // Perform in-place reversal by altering links
    reversePlaylist(playlist);

    cout << "\n=== Reversed Playlist (Traversal Starts From Last Song) ===" << endl;
    cout << "Note: Node addresses match original nodes, proving only link pointers were modified." << endl;
    displayPlaylist(playlist);

    freePlaylist(playlist);
    return 0;
}
