#include <iostream>
using namespace std;

// Node structure for IoT sensor reading
struct Node {
    int sensorId;
    double reading;
    Node* next;

    Node(int id, double val) {
        sensorId = id;
        reading = val;
        next = nullptr;
    }
};

// Function to detect loop in singly linked list using Floyd's Cycle Detection Algorithm
// (Tortoise and Hare technique). Runs in O(N) time and O(1) auxiliary space.
bool detectLoop(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return false; // Empty list or single node without loop cannot have a cycle
    }

    Node* slow = head; // Moves 1 step at a time
    Node* fast = head; // Moves 2 steps at a time

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // Move slow pointer 1 step forward
        fast = fast->next->next;    // Move fast pointer 2 steps forward

        // If slow and fast pointers meet, a loop/cycle exists in the list
        if (slow == fast) {
            return true;
        }
    }

    return false; // Fast pointer reached NULL, so list has no loop
}

// Helper to add node to list
void addSensorReading(Node*& head, Node*& tail, int id, double val) {
    Node* newNode = new Node(id, val);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Helper to free memory (only for linear acyclic list)
void freeAcyclicList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    // Build a normal linear IoT buffer
    addSensorReading(head, tail, 101, 24.5);
    addSensorReading(head, tail, 102, 25.1);
    addSensorReading(head, tail, 103, 23.8);
    addSensorReading(head, tail, 104, 26.0);
    addSensorReading(head, tail, 105, 24.9);

    cout << "Test 1: Linear Sensor Buffer (No cycle)" << endl;
    if (detectLoop(head)) {
        cout << "Result: Loop detected!" << endl;
    } else {
        cout << "Result: No loop detected. Buffer is healthy." << endl;
    }

    // Now introduce a faulty loop pointer: point tail->next back to sensor 103 (3rd node)
    Node* thirdNode = head->next->next; // Sensor 103 node
    tail->next = thirdNode; // Creating cycle: 105 -> 103

    cout << "\nTest 2: Faulty Sensor Buffer (Cycle introduced: Node 105 points back to Node 103)" << endl;
    if (detectLoop(head)) {
        cout << "Result: Loop DETECTED! Faulty pointer identified successfully." << endl;
    } else {
        cout << "Result: No loop detected." << endl;
    }

    // Break the loop before cleanup to avoid infinite loop during deletion
    tail->next = nullptr;
    freeAcyclicList(head);

    return 0;
}
