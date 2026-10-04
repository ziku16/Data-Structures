#include <iostream>
#include <string>
using namespace std;

// Node structure representing a Task in Circular Linked List
struct TaskNode {
    string name;
    int priority;      // Higher value = higher priority
    string status;     // "pending", "in-progress", or "completed"
    TaskNode* next;

    TaskNode(string n, int p, string s = "pending") {
        name = n;
        priority = p;
        status = s;
        next = nullptr;
    }
};

// Task Scheduler class managing circular linked list of tasks
class TaskScheduler {
private:
    TaskNode* head;
    TaskNode* tail;
    TaskNode* currentExecutionTask;

public:
    TaskScheduler() {
        head = nullptr;
        tail = nullptr;
        currentExecutionTask = nullptr;
    }

    ~TaskScheduler() {
        if (head == nullptr) return;

        TaskNode* curr = head;
        tail->next = nullptr; // Break circular link for safe deletion

        while (curr != nullptr) {
            TaskNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    // 1. Add a Task: Insert at end, maintaining circular structure
    void addTask(string name, int priority, string status = "pending") {
        TaskNode* newTask = new TaskNode(name, priority, status);
        if (head == nullptr) {
            head = tail = currentExecutionTask = newTask;
            newTask->next = head; // Point to self to make circular
        } else {
            tail->next = newTask;
            newTask->next = head; // Maintain circular structure
            tail = newTask;
        }
        cout << "Added task: \"" << name << "\" [Priority: " << priority << ", Status: " << status << "]" << endl;
    }

    // 2. Remove a Task by name
    void removeTask(string name) {
        if (head == nullptr) {
            cout << "Scheduler is empty." << endl;
            return;
        }

        TaskNode* curr = head;
        TaskNode* prev = tail;
        bool found = false;

        do {
            if (curr->name == name) {
                found = true;
                break;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);

        if (!found) {
            cout << "Task \"" << name << "\" not found." << endl;
            return;
        }

        // Single node left in list
        if (head == tail && head->name == name) {
            delete head;
            head = tail = currentExecutionTask = nullptr;
            cout << "Removed task: \"" << name << "\". Scheduler is now empty." << endl;
            return;
        }

        // Updating pointers for removal
        if (curr == currentExecutionTask) {
            currentExecutionTask = curr->next;
        }
        if (curr == head) {
            head = head->next;
            tail->next = head;
        } else if (curr == tail) {
            tail = prev;
            tail->next = head;
        } else {
            prev->next = curr->next;
        }

        cout << "Removed task: \"" << name << "\" successfully." << endl;
        delete curr;
    }

    // 3. Get Next Task: Round-robin traversal. Skips completed tasks until a pending or in-progress task is found.
    TaskNode* getNextTask() {
        if (head == nullptr) {
            cout << "No tasks available." << endl;
            return nullptr;
        }

        TaskNode* startSearch = currentExecutionTask;

        do {
            if (currentExecutionTask->status != "completed") {
                TaskNode* taskToExecute = currentExecutionTask;
                // Move pointer to next task for future round-robin calls
                currentExecutionTask = currentExecutionTask->next;
                return taskToExecute;
            }
            currentExecutionTask = currentExecutionTask->next;
        } while (currentExecutionTask != startSearch);

        cout << "All tasks in the schedule are completed!" << endl;
        return nullptr;
    }

    // 4. Display All Tasks starting from head around the circular list
    void displayAllTasks() {
        if (head == nullptr) {
            cout << "No tasks in scheduler." << endl;
            return;
        }

        cout << "\n=== Current Task Schedule (Circular List) ===" << endl;
        TaskNode* temp = head;
        int count = 1;
        do {
            cout << count++ << ". Task: \"" << temp->name 
                 << "\" | Priority: " << temp->priority 
                 << " | Status: " << temp->status;
            if (temp == currentExecutionTask) cout << "  [<-- Next Round Pointer]";
            cout << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // 5. Update Task Status based on name
    void updateTaskStatus(string name, string newStatus) {
        if (head == nullptr) {
            cout << "Scheduler is empty." << endl;
            return;
        }

        TaskNode* temp = head;
        do {
            if (temp->name == name) {
                temp->status = newStatus;
                cout << "Updated status of task \"" << name << "\" to: " << newStatus << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Task \"" << name << "\" not found." << endl;
    }
};

int main() {
    TaskScheduler scheduler;

    // Add Tasks
    scheduler.addTask("Database Backup", 3, "pending");
    scheduler.addTask("Generate Monthly Report", 2, "pending");
    scheduler.addTask("Cleanup Temp Files", 1, "completed");
    scheduler.addTask("Process User Payments", 5, "pending");

    // Display all tasks
    scheduler.displayAllTasks();

    // Get next task in round-robin fashion
    cout << "\n--- Round-Robin Execution ---" << endl;
    TaskNode* task = scheduler.getNextTask();
    if (task) {
        cout << "Executing Next Task: \"" << task->name << "\" (Status: " << task->status << ")" << endl;
        scheduler.updateTaskStatus(task->name, "in-progress");
    }

    task = scheduler.getNextTask();
    if (task) {
        cout << "Executing Next Task: \"" << task->name << "\" (Status: " << task->status << ")" << endl;
    }

    // Remove a task
    cout << "\n--- Removing Task ---" << endl;
    scheduler.removeTask("Cleanup Temp Files");

    // Display updated scheduler
    scheduler.displayAllTasks();

    return 0;
}
