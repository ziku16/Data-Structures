#include <iostream>
#include <stdexcept>

using namespace std;

// Array-based stack primitive
class ArrayStack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    ArrayStack(int cap = 100) : capacity(cap), topIndex(-1) {
        arr = new int[capacity];
    }
    ~ArrayStack() {
        delete[] arr;
    }

    void push(int val) {
        if (topIndex >= capacity - 1) throw overflow_error("Stack Overflow");
        arr[++topIndex] = val;
    }

    int pop() {
        if (isEmpty()) throw underflow_error("Stack Underflow");
        return arr[topIndex--];
    }

    int peek() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return arr[topIndex];
    }

    bool isEmpty() const { return topIndex == -1; }
};

// Linked-list-based stack primitive
class LLStack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* topNode;

public:
    LLStack() : topNode(nullptr) {}
    ~LLStack() {
        while (!isEmpty()) pop();
    }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) throw underflow_error("Stack Underflow");
        Node* temp = topNode;
        int val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    int peek() const {
        if (isEmpty()) throw underflow_error("Stack is empty");
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }
};

// Queue adapter using two stacks
template <typename StackType>
class QueueUsingTwoStacks {
private:
    StackType inStack;
    StackType outStack;

    // Shift elements to outStack only when outStack is empty
    // Reversing the stack contents flips LIFO order to FIFO
    void shiftStacks() {
        if (outStack.isEmpty()) {
            while (!inStack.isEmpty()) {
                outStack.push(inStack.pop());
            }
        }
    }

public:
    void enqueue(int val) {
        inStack.push(val);
    }

    int dequeue() {
        shiftStacks();
        if (outStack.isEmpty()) throw underflow_error("Queue Underflow");
        return outStack.pop();
    }

    int front() {
        shiftStacks();
        if (outStack.isEmpty()) throw underflow_error("Queue is empty");
        return outStack.peek();
    }

    bool isEmpty() const {
        return inStack.isEmpty() && outStack.isEmpty();
    }
};

int main() {
    cout << "Queue using Array-based Stacks:\n";
    QueueUsingTwoStacks<ArrayStack> arrQueue;
    arrQueue.enqueue(10);
    arrQueue.enqueue(20);
    arrQueue.enqueue(30);
    cout << "Dequeued: " << arrQueue.dequeue() << " (Expected: 10)\n";
    cout << "Front: " << arrQueue.front() << " (Expected: 20)\n\n";

    cout << "Queue using Linked-List-based Stacks:\n";
    QueueUsingTwoStacks<LLStack> llQueue;
    llQueue.enqueue(100);
    llQueue.enqueue(200);
    llQueue.enqueue(300);
    cout << "Dequeued: " << llQueue.dequeue() << " (Expected: 100)\n";
    cout << "Front: " << llQueue.front() << " (Expected: 200)\n";

    return 0;
}