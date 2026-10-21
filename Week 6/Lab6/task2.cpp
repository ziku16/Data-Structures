#include <iostream>
#include <stdexcept>

using namespace std;

// Templated class to support any data type in the Deque
template <typename T>
class Deque {
private:
    // Definition of a node in the doubly linked list
    struct Node {
        T data;         // Value stored in the node
        Node* next;     // Pointer to the next node
        Node* prev;     // Pointer to the previous node

        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* frontPtr;    // Pointer to the front element
    Node* rearPtr;     // Pointer to the rear element
    size_t count;      // Total number of elementsImplement the Deque in linked list.

public:
    // Default constructor
    Deque() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    // Destructor to free dynamic memory
    ~Deque() {
        clear();
    }

    // Copy constructor
    Deque(const Deque& other) : frontPtr(nullptr), rearPtr(nullptr), count(0) {
        Node* curr = other.frontPtr;
        while (curr) {
            insertRear(curr->data);
            curr = curr->next;
        }
    }

    // Overloaded assignment operator
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            clear();
            Node* curr = other.frontPtr;
            while (curr) {
                insertRear(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    // Check if the deque is empty
    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    // Return current size of deque
    size_t size() const {
        return count;
    }

    // Insert an element at the front
    void insertFront(const T& element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            newNode->next = frontPtr;
            frontPtr->prev = newNode;
            frontPtr = newNode;
        }
        count++;
    }

    // Insert an element at the rear
    void insertRear(const T& element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            newNode->prev = rearPtr;
            rearPtr = newNode;
        }
        count++;
    }

    // Delete the front element
    void deleteFront() {
        if (isEmpty()) {
            throw underflow_error("Deque is empty: cannot delete from front");
        }
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;

        if (frontPtr == nullptr) {
            rearPtr = nullptr; // Deque became empty
        } else {
            frontPtr->prev = nullptr;
        }

        delete temp;
        count--;
    }

    // Delete the rear element
    void deleteRear() {
        if (isEmpty()) {
            throw underflow_error("Deque is empty: cannot delete from rear");
        }
        Node* temp = rearPtr;
        rearPtr = rearPtr->prev;

        if (rearPtr == nullptr) {
            frontPtr = nullptr; // Deque became empty
        } else {
            rearPtr->next = nullptr;
        }

        delete temp;
        count--;
    }

    // Get the front element
    T getFront() const {
        if (isEmpty()) {
            throw underflow_error("Deque is empty: no front element");
        }
        return frontPtr->data;
    }

    // Get the rear element
    T getRear() const {
        if (isEmpty()) {
            throw underflow_error("Deque is empty: no rear element");
        }
        return rearPtr->data;
    }

    // Clear all elements from the deque
    void clear() {
        while (!isEmpty()) {
            deleteFront();
        }
    }

    // Display elements from front to rear
    void display() const {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
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
    Deque<int> dq;

    cout << "Inserting at rear: 10, 20" << endl;
    dq.insertRear(10);
    dq.insertRear(20);

    cout << "Inserting at front: 5, 1" << endl;
    dq.insertFront(5);
    dq.insertFront(1);

    cout << "Deque contents: ";
    dq.display(); // Output: 1 5 10 20

    cout << "Front element: " << dq.getFront() << endl; // 1
    cout << "Rear element: " << dq.getRear() << endl;   // 20

    cout << "Deleting front..." << endl;
    dq.deleteFront();
    dq.display(); // Output: 5 10 20

    cout << "Deleting rear..." << endl;
    dq.deleteRear();
    dq.display(); // Output: 5 10

    cout << "Current Deque size: " << dq.size() << endl;

    return 0;
}