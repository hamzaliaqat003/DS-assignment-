#include <iostream>
#include <string>

using namespace std;

struct Task {
    int taskId;
    string description;
    int priority;
    Task* next;
};

Task* head = nullptr;

// Function to add a new task to the list at the correct position based on priority
void addTask(int taskId, string description, int priority) {
    Task* newTask = new Task;
    newTask->taskId = taskId;
    newTask->description = description;
    newTask->priority = priority;
    newTask->next = nullptr;

    if (head == nullptr || priority > head->priority) {
        newTask->next = head;
        head = newTask;
    } else {
        Task* current = head;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }
}

// Function to remove the task with the highest priority (i.e., delete from the start)
void removeHighestPriorityTask() {
    if (head != nullptr) {
        Task* temp = head;
        head = head->next;
        delete temp;
    }
}

// Function to remove a specific task using its task ID
void removeTaskById(int taskId) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    if (head->taskId == taskId) {
        Task* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Task* current = head;
    while (current->next != nullptr && current->next->taskId != taskId) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Task* temp = current->next;
        current->next = temp->next;
        delete temp;
    } else {
        cout << "Task with ID " << taskId << " not found.\n";
    }
}

// Function to view all tasks
void viewTasks() {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Task* current = head;
    while (current != nullptr) {
        cout << "Task ID: " << current->taskId << endl;
        cout << "Description: " << current->description << endl;
        cout << "Priority: " << current->priority << endl;
        cout << endl;
        current = current->next;
    }
}

// Main function
int main() {
    int choice;

    do {
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int taskId, priority;
                string description;

                cout << "Enter task ID: ";
                cin >> taskId;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter priority level: ";
                cin >> priority;

                addTask(taskId, description, priority);
                break;
            }
            case 2:
                viewTasks();
                break;
            case 3:
                removeHighestPriorityTask();
                break;
            case 4: {
                int taskId;
                cout << "Enter task ID to remove: ";
                cin >> taskId;
                removeTaskById(taskId);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}