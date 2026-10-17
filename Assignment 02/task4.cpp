#include <iostream>
#include <stdexcept>

using namespace std;

class ArrayQueue {
private:
    int* arr;
    int capacity;
    int frontIdx;
    int rearIdx;
    int count;

public:
    ArrayQueue(int cap = 100) : capacity(cap), frontIdx(0), rearIdx(-1), count(0) {
        arr = new int[capacity];
    }
    ~ArrayQueue() { delete[] arr; }

    void enqueue(int val) {
        if (count == capacity) throw overflow_error("Queue Overflow");
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx] = val;
        count++;
    }

    int dequeue() {
        if (isEmpty()) throw underflow_error("Queue Underflow");
        int val = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return val;
    }

    int front() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return arr[frontIdx];
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

class LLQueue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* frontNode;
    Node* rearNode;
    int count;

public:
    LLQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}
    ~LLQueue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    int dequeue() {
        if (isEmpty()) throw underflow_error("Queue Underflow");
        Node* temp = frontNode;
        int val = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        count--;
        return val;
    }

    int front() const {
        if (isEmpty()) throw underflow_error("Queue is empty");
        return frontNode->data;
    }

    bool isEmpty() const { return frontNode == nullptr; }
    int size() const { return count; }
};

// Selection sort using queue rotations
template <typename QueueType>
void selectionSortQueue(QueueType& q) {
    int n = q.size();

    for (int i = 0; i < n; i++) {
        int unsortedCount = n - i;
        int minVal = q.front();

        // Pass 1: Find the minimum value in the unsorted section
        for (int j = 0; j < unsortedCount; j++) {
            int val = q.dequeue();
            if (val < minVal) minVal = val;
            q.enqueue(val);
        }

        // Pass 2: Re-enqueue all elements except the first occurrence of minVal
        bool removed = false;
        for (int j = 0; j < unsortedCount; j++) {
            int val = q.dequeue();
            if (val == minVal && !removed) {
                removed = true;
            } else {
                q.enqueue(val);
            }
        }
        // Place the isolated minimum value at the end of the sorted section
        q.enqueue(minVal);

        // Rotate previously sorted elements to return unsorted items to the front
        for (int j = 0; j < i; j++) {
            q.enqueue(q.dequeue());
        }
    }
}

int main() {
    cout << "Selection Sort on ArrayQueue:\n";
    ArrayQueue qArr;
    qArr.enqueue(29); qArr.enqueue(10); qArr.enqueue(14); qArr.enqueue(37); qArr.enqueue(13);
    selectionSortQueue(qArr);
    while (!qArr.isEmpty()) {
        cout << qArr.dequeue() << " ";
    }
    cout << "\n\n";

    cout << "Selection Sort on LLQueue:\n";
    LLQueue qLL;
    qLL.enqueue(77); qLL.enqueue(2); qLL.enqueue(45); qLL.enqueue(12); qLL.enqueue(8);
    selectionSortQueue(qLL);
    while (!qLL.isEmpty()) {
        cout << qLL.dequeue() << " ";
    }
    cout << "\n";

    return 0;
}