#include <iostream>
#include <stdexcept>

using namespace std;

class ArrayStack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    ArrayStack(int cap = 100) : capacity(cap), topIndex(-1) {
        arr = new int[capacity];
    }
    ~ArrayStack() { delete[] arr; }

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

// Insertion sort using an auxiliary stack
template <typename StackType>
void insertionSortStack(StackType& inputStack) {
    StackType tempStack;

    while (!inputStack.isEmpty()) {
        int current = inputStack.pop();

        // Push elements larger than current back onto inputStack to find current's place
        while (!tempStack.isEmpty() && tempStack.peek() > current) {
            inputStack.push(tempStack.pop());
        }

        tempStack.push(current);
    }

    // Move elements back so the smallest element stays at the top of inputStack
    while (!tempStack.isEmpty()) {
        inputStack.push(tempStack.pop());
    }
}

int main() {
    cout << "Insertion Sort on ArrayStack (popped from top to bottom):\n";
    ArrayStack arrStack;
    arrStack.push(34); arrStack.push(3); arrStack.push(31); arrStack.push(98); arrStack.push(92); arrStack.push(23);
    insertionSortStack(arrStack);
    while (!arrStack.isEmpty()) {
        cout << arrStack.pop() << " ";
    }
    cout << "\n\n";

    cout << "Insertion Sort on LLStack (popped from top to bottom):\n";
    LLStack llStack;
    llStack.push(42); llStack.push(17); llStack.push(89); llStack.push(8); llStack.push(13);
    insertionSortStack(llStack);
    while (!llStack.isEmpty()) {
        cout << llStack.pop() << " ";
    }
    cout << "\n";

    return 0;
}