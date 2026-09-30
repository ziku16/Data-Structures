#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* prev;
    Node* next;
};

// Insert a node at the end
void insertAtEnd(Node*& head, int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    // If list is empty
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // Find the last node
    Node* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    // Connect new node
    temp->next = newNode;
    newNode->prev = temp;
}

// Display the list
void display(Node* head)
{
    Node* temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

// Function to swap two nodes
void swapNodes(Node*& head, int value1, int value2)
{
    // If both values are the same, no need to swap
    if (value1 == value2)
        return;

    Node* node1 = nullptr;
    Node* node2 = nullptr;

    // Search for both nodes
    Node* temp = head;

    while (temp != nullptr)
    {
        if (temp->data == value1)
            node1 = temp;

        if (temp->data == value2)
            node2 = temp;

        temp = temp->next;
    }

    // If either node was not found
    if (node1 == nullptr || node2 == nullptr)
    {
        cout << "One or both values were not found!" << endl;
        return;
    }

    // Save the neighboring nodes
    Node* node1Prev = node1->prev;
    Node* node1Next = node1->next;

    Node* node2Prev = node2->prev;
    Node* node2Next = node2->next;

    // Case 1: node1 comes immediately before node2
    if (node1->next == node2)
    {
        node1->prev = node2;
        node1->next = node2Next;

        node2->prev = node1Prev;
        node2->next = node1;

        if (node1Prev != nullptr)
            node1Prev->next = node2;

        if (node2Next != nullptr)
            node2Next->prev = node1;
    }

    // Case 2: node2 comes immediately before node1
    else if (node2->next == node1)
    {
        node2->prev = node1;
        node2->next = node1Next;

        node1->prev = node2Prev;
        node1->next = node2;

        if (node2Prev != nullptr)
            node2Prev->next = node1;

        if (node1Next != nullptr)
            node1Next->prev = node2;
    }

    // Case 3: Nodes are not next to each other
    else
    {
        // Connect node1's old neighbors to node2
        if (node1Prev != nullptr)
            node1Prev->next = node2;

        if (node1Next != nullptr)
            node1Next->prev = node2;

        // Connect node2's old neighbors to node1
        if (node2Prev != nullptr)
            node2Prev->next = node1;

        if (node2Next != nullptr)
            node2Next->prev = node1;

        // Swap prev pointers
        node1->prev = node2Prev;
        node2->prev = node1Prev;

        // Swap next pointers
        node1->next = node2Next;
        node2->next = node1Next;
    }

    // Update head if node1 or node2 was the head
    if (head == node1)
        head = node2;
    else if (head == node2)
        head = node1;
}

int main()
{
    Node* head = nullptr;

    // Create the list
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);
    insertAtEnd(head, 50);

    cout << "Original List: ";
    display(head);

    int value1, value2;

    cout << "Enter first value: ";
    cin >> value1;

    cout << "Enter second value: ";
    cin >> value2;

    // Swap the actual nodes
    swapNodes(head, value1, value2);

    cout << "List after swapping: ";
    display(head);

    return 0;
}