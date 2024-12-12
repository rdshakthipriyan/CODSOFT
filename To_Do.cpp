#include <iostream>
#include <string>

using namespace std;

// Define a structure to represent a task
struct Task {
    string description;
    bool completed;
};

// Define the maximum number of tasks allowed in the list
const int MAX_TASKS = 10;

// Function to add a task to the list
void addTask(Task tasks[], int &taskCount) {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full. Cannot add more tasks.\n";
        return;
    }

    cout << "Enter task description: ";
    cin.ignore();  // To clear the input buffer before reading a string
    getline(cin, tasks[taskCount].description);  // Read the entire task description
    tasks[taskCount].completed = false;  // New tasks are initially not completed
    taskCount++;

    cout << "Task added successfully!\n";
}

// Function to view all tasks
void viewTasks(const Task tasks[], int taskCount) {
    if (taskCount == 0) {
        cout << "No tasks in the list.\n";
        return;
    }

    cout << "Task List:\n";
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i].description << " [" 
             << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
    }
}

// Function to mark a task as completed
void markTaskCompleted(Task tasks[], int taskCount) {
    int taskNumber;
    cout << "Enter the task number to mark as completed: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[taskNumber - 1].completed = true;  // Mark the task as completed
    cout << "Task marked as completed.\n";
}

// Function to remove a task
void removeTask(Task tasks[], int &taskCount) {
    int taskNumber;
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;

    if (taskNumber < 1 || taskNumber > taskCount) {
        cout << "Invalid task number.\n";
        return;
    }

    // Shift all tasks after the removed task to the left
    for (int i = taskNumber - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;  // Decrease the task count
    cout << "Task removed successfully.\n";
}

// Function to display the menu
void displayMenu() {
    cout << "\nTo-Do List Manager\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Remove Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Task tasks[MAX_TASKS];  // Array to store tasks
    int taskCount = 0;  // To keep track of the number of tasks

    int choice;
    do {
        displayMenu();  // Display the menu
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks, taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                markTaskCompleted(tasks, taskCount);
                break;
            case 4:
                removeTask(tasks, taskCount);
                break;
            case 5:
                cout << "Exiting To-Do List Manager...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);  // Exit the loop when the user chooses option 5

    return 0;
}
