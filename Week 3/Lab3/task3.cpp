#include <iostream>
using namespace std;

// Node for Singly Linked List
struct SNode
{
    int data;
    SNode* next;
};

// Node for Doubly Linked List
struct DNode
{
    int data;
    DNode* prev;
    DNode* next;
};

// Insert into Singly Linked List
void insertSingly(SNode*& head, int value)
{
    SNode* newNode = new SNode;

    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    SNode* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Display Singly Linked List
void displaySingly(SNode* head)
{
    SNode* temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

// Function to convert Singly Linked List into Doubly Linked List
DNode* convertToDoubly(SNode* head)
{
    // Initially the doubly linked list is empty
    DNode* dHead = nullptr;

    // Keeps track of the last node in doubly linked list
    DNode* last = nullptr;

    SNode* current = head;

    // Traverse the singly linked list
    while (current != nullptr)
    {
        // Create a new doubly linked list node
        DNode* newNode = new DNode;

        newNode->data = current->data;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        // If doubly linked list is empty
        if (dHead == nullptr)
        {
            dHead = newNode;
            last = newNode;
        }
        else
        {
            // Connect the new node with the previous node
            last->next = newNode;
            newNode->prev = last;

            // Move last to the new node
            last = newNode;
        }

        // Move to the next node of singly linked list
        current = current->next;
    }

    return dHead;
}

// Display Doubly Linked List
void displayDoubly(DNode* head)
{
    DNode* temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

int main()
{
    // Create an empty singly linked list
    SNode* head = nullptr;

    // Create singly linked list
    insertSingly(head, 10);
    insertSingly(head, 20);
    insertSingly(head, 30);
    insertSingly(head, 40);

    cout << "Singly Linked List:" << endl;
    displaySingly(head);

    // Convert singly linked list to doubly linked list
    DNode* dHead = convertToDoubly(head);

    cout << "\nDoubly Linked List:" << endl;
    displayDoubly(dHead);

    return 0;
}