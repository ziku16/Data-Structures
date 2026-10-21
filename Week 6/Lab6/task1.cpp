#include <iostream>
#include <stdexcept>

using namespace std;

// Templated class to support any data type in the Dynamic Queue
template <typename T>
class DynamicQueue {
private:
    // Definition of a node in the linked list
    struct Node {
        T data;         // Value stored in the node
        Node* next;     // Pointer to the next node in the queue

        // Node constructor initializing data and next pointer
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* frontPtr;    // Pointer to the front element of the queue
    Node* rearPtr;     // Pointer to the rear element of the queue
    size_t count;      // Tracks the total number of elements in the queue

public:
    // Default constructor initializing an empty queue
    DynamicQueue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    // Destructor to free dynamically allocated memory on object destruction
    ~DynamicQueue() {
        clear();
    }

    // Copy constructor for deep copying another queue instance
    DynamicQueue(const DynamicQueue& other) : frontPtr(nullptr), rearPtr(nullptr), count(0) {
        Node* curr = other.frontPtr;
        while (curr) {
            enqueue(curr->data);
            curr = curr->next;
        }
    }

    // Overloaded assignment operator for deep copying assignments
    DynamicQueue& operator=(const DynamicQueue& other) {
        if (this != &other) {
            clear(); // Clean up existing dynamic memory
            Node* curr = other.frontPtr;
            while (curr) {
                enqueue(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Checks if the queue contains no elements
    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    // Returns the current number of elements in the queue
    size_t size() const {
        return count;
    }

    // Inserts a new element at the rear of the queue
    void enqueue(const T& element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            // If empty, both front and rear point to the newly created node
            frontPtr = rearPtr = newNode;
        } else {
            // Append new node after rear and update the rear pointer
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    // Removes the element from the front of the queue
    void dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue is empty: cannot perform dequeue");
        }
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        
        // If queue becomes empty after deletion, reset rear pointer to nullptr
        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }
        
        delete temp; // Free memory allocated for dequeued node
        count--;
    }

    // Returns the value stored at the front of the queue without removing it
    T front() const {
        if (isEmpty()) {
            throw underflow_error("Queue is empty: no front element");
        }
        return frontPtr->data;
    }

    // Returns the value stored at the rear of the queue without removing it
    T rear() const {
        if (isEmpty()) {
            throw underflow_error("Queue is empty: no rear element");
        }
        return rearPtr->data;
    }

    // Removes all nodes from the queue to free dynamic memory
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Displays all elements of the queue from front to rear
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node* curr = frontPtr;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    DynamicQueue<int> q;

    cout << "Enqueuing 10, 20, 30..." << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Queue contents: ";
    q.display();

    cout << "Front element: " << q.front() << endl;
    cout << "Rear element: " << q.rear() << endl;

    cout << "Dequeuing front element..." << endl;
    q.dequeue();

    cout << "Queue contents after dequeue: ";
    q.display();

    cout << "Current Queue size: " << q.size() << endl;

    return 0;
}