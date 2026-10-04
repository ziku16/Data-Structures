#include <iostream>
#include <string>
using namespace std;

// Node structure for logging system
struct Node {
    string logMessage;
    Node* next;

    Node(string msg) {
        logMessage = msg;
        next = nullptr;
    }
};

// Function to display linked list in reverse order without modifying the list structure
// Uses recursion: the function calls itself until the end of list is reached, 
// and then prints the elements while unwinding the call stack (latest first, oldest last).
void displayReverse(Node* head) {
    if (head == nullptr) {
        return; // Base case: end of linked list
    }
    
    // Recursive call to reach the end of the list first
    displayReverse(head->next);
    
    // Print current node log message as the call stack unwinds
    cout << "Log: " << head->logMessage << " (Address: " << head << ")" << endl;
}

// Helper function to display list in forward order
void displayForward(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "Log: " << temp->logMessage << endl;
        temp = temp->next;
    }
}

// Helper function to append a log entry at the end of list
void appendLog(Node*& head, Node*& tail, string msg) {
    Node* newNode = new Node(msg);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Helper function to free allocated memory
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

    // Oldest log entry at head, newest log at end
    appendLog(head, tail, "10:00 AM - System Startup");
    appendLog(head, tail, "10:05 AM - User Login: admin");
    appendLog(head, tail, "10:15 AM - Database Connection Established");
    appendLog(head, tail, "10:30 AM - Warning: High Memory Usage");
    appendLog(head, tail, "10:45 AM - Critical: Sensor Timeout Error");

    cout << "=== Forward Order (Oldest to Newest) ===" << endl;
    displayForward(head);

    cout << "\n=== Reverse Order (Newest to Oldest) [Logs displayed in reverse without structural modification] ===" << endl;
    displayReverse(head);

    // Clean memory
    freeList(head);
    return 0;
}
