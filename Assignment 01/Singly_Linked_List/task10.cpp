#include <iostream>
using namespace std;

// Node structure representing a task in processing sequence
struct Node {
    int taskId;
    Node* next;

    Node(int id) {
        taskId = id;
        next = nullptr;
    }
};

// Function to swap every two consecutive nodes in pairs by modifying pointer links.
// Node addresses remain unchanged.
void swapPairs(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return; // Empty list or single node requires no pairwise swaps
    }

    Node dummy(0);
    dummy.next = head;
    Node* prev = &dummy;

    while (prev->next != nullptr && prev->next->next != nullptr) {
        Node* first = prev->next;
        Node* second = prev->next->next;

        // Perform pair swap by updating next pointers
        first->next = second->next;
        second->next = first;
        prev->next = second;

        // Advance prev pointer for next pair
        prev = first;
    }

    head = dummy.next; // Update actual list head
}

// Function to display task sequence along with node memory addresses
void displayTasks(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->taskId << " [Address: " << temp << "]";
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Helper to append task
void addTask(Node*& head, int id) {
    Node* newNode = new Node(id);
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
    Node* taskList = nullptr;

    // Create task list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
    for (int i = 1; i <= 6; i++) {
        addTask(taskList, i);
    }

    cout << "=== Initial Task Sequence ===" << endl;
    displayTasks(taskList);

    // Swap adjacent task nodes in pairs
    swapPairs(taskList);

    cout << "\n=== Rearranged Task Sequence (Pairwise Swapped) ===" << endl;
    cout << "Expected Output: 2 -> 1 -> 4 -> 3 -> 6 -> 5 -> NULL" << endl;
    cout << "Actual Output:   ";
    displayTasks(taskList);

    freeList(taskList);
    return 0;
}
