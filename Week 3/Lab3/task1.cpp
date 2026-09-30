#include <iostream>
using namespace std;

// Node structure for the doubly linked list
struct Node
{
    int data;
    Node* prev;
    Node* next;
};

// Function to insert a node at the end
void insertAtEnd(Node*& head, int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    // If the list is empty
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // Move to the last node
    Node* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    // Connect the new node
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to display the list
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

// Function to reverse the doubly linked list
void reverse(Node*& head)
{
    Node* current = head;
    Node* temp = nullptr;

    // Traverse through the entire list
    while (current != nullptr)
    {
        // Swap the prev and next pointers
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to the next node
        // After swapping, prev points to the original next node
        current = current->prev;
    }

    // Update head
    // temp contains the previous pointer of the last processed node
    if (temp != nullptr)
    {
        head = temp->prev;
    }
}

int main()
{
    // Initially the list is empty
    Node* head = nullptr;

    // Create the doubly linked list
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    insertAtEnd(head, 40);

    cout << "Original List: ";
    display(head);

    // Reverse the list
    reverse(head);

    cout << "Reversed List: ";
    display(head);

    return 0;
}