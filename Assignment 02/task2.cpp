#include <iostream>
#include <stdexcept>

using namespace std;

// Array-based circular queue primitive
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
    ~ArrayQueue() {
        delete[] arr;
    }

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

// Linked-list-based queue primitive
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

// Stack adapter using two queues
template <typename QueueType>
class StackUsingTwoQueues {
private:
    QueueType q1;
    QueueType q2;

public:
    // Place new item into q2, then empty q1 behind it into q2
    // Re-transferring to q1 keeps the newest item at the queue head
    void push(int val) {
        q2.enqueue(val);
        while (!q1.isEmpty()) {
            q2.enqueue(q1.dequeue());
        }
        while (!q2.isEmpty()) {
            q1.enqueue(q2.dequeue());
        }
    }

    int pop() {
        if (q1.isEmpty()) throw underflow_error("Stack Underflow");
        return q1.dequeue();
    }

    int top() {
        if (q1.isEmpty()) throw underflow_error("Stack is empty");
        return q1.front();
    }

    bool isEmpty() const { return q1.isEmpty(); }
};

int main() {
    cout << "Stack using Array-based Queues:\n";
    StackUsingTwoQueues<ArrayQueue> arrStack;
    arrStack.push(10);
    arrStack.push(20);
    arrStack.push(30);
    cout << "Popped: " << arrStack.pop() << " (Expected: 30)\n";
    cout << "Top: " << arrStack.top() << " (Expected: 20)\n\n";

    cout << "Stack using Linked-List-based Queues:\n";
    StackUsingTwoQueues<LLQueue> llStack;
    llStack.push(100);
    llStack.push(200);
    llStack.push(300);
    cout << "Popped: " << llStack.pop() << " (Expected: 300)\n";
    cout << "Top: " << llStack.top() << " (Expected: 200)\n";

    return 0;
}