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

    bool isEmpty() const { return frontNode == nullptr; }
    int size() const { return count; }
};

// Bubble sort using queue operations
template <typename QueueType>
void bubbleSortQueue(QueueType& q) {
    int n = q.size();
    if (n <= 1) return;

    for (int i = 0; i < n; i++) {
        // Carry the larger value forward across adjacent comparisons
        int curr = q.dequeue();
        for (int j = 0; j < n - 1; j++) {
            int nextVal = q.dequeue();
            if (curr > nextVal) {
                q.enqueue(nextVal);
            } else {
                q.enqueue(curr);
                curr = nextVal;
            }
        }
        // Place the largest value of this pass at the back
        q.enqueue(curr);
    }
}

int main() {
    cout << "Bubble Sort on ArrayQueue:\n";
    ArrayQueue qArr;
    qArr.enqueue(64); qArr.enqueue(34); qArr.enqueue(25); qArr.enqueue(12); qArr.enqueue(22);
    bubbleSortQueue(qArr);
    while (!qArr.isEmpty()) {
        cout << qArr.dequeue() << " ";
    }
    cout << "\n\n";

    cout << "Bubble Sort on LLQueue:\n";
    LLQueue qLL;
    qLL.enqueue(5); qLL.enqueue(1); qLL.enqueue(4); qLL.enqueue(2); qLL.enqueue(8);
    bubbleSortQueue(qLL);
    while (!qLL.isEmpty()) {
        cout << qLL.dequeue() << " ";
    }
    cout << "\n";

    return 0;
}