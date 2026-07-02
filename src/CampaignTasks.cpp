#include "include/CampaignTasks.h"

// Constructor
CampaignTasks::CampaignTasks() : head(nullptr), taskCounter(0) {}

// Destructor - clean up all nodes
CampaignTasks::~CampaignTasks() {
    TaskNode* current = head;
    while (current != nullptr) {
        TaskNode* next = current->next;
        delete current;
        current = next;
    }
}

// Add task to end of linked list
void CampaignTasks::addTask(QString description, QString deadline) {
    taskCounter++;
    TaskNode* newTask = new TaskNode(taskCounter, description, deadline);
    
    if (head == nullptr) {
        head = newTask;
    } else {
        // Traverse to end of list
        TaskNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTask;
    }
}

// Load task with existing ID
void CampaignTasks::loadTask(int id, QString description, bool completed, QString deadline) {
    TaskNode* newTask = new TaskNode(id, description, deadline);
    newTask->completed = completed;
    
    if (head == nullptr) {
        head = newTask;
    } else {
        // Traverse to end
        TaskNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTask;
    }
    
    // Update counter
    if (id > taskCounter) {
        taskCounter = id;
    }
}

// Mark task as completed by ID
bool CampaignTasks::markComplete(int taskId) {
    TaskNode* current = head;
    
    while (current != nullptr) {
        if (current->taskId == taskId) {
            current->completed = true;
            return true;
        }
        current = current->next;
    }
    
    return false; // Task not found
}

// Get all tasks as formatted strings
QVector<QString> CampaignTasks::getAllTasksAsStrings() {
    QVector<QString> results;
    TaskNode* current = head;
    
    while (current != nullptr) {
        QString status = current->completed ? "[✓]" : "[ ]";
        QString taskStr = QString("%1 Task %2: %3")
            .arg(status)
            .arg(current->taskId)
            .arg(current->description);
        
        if (!current->deadline.isEmpty()) {
            taskStr += QString(" (Due: %1)").arg(current->deadline);
        }
        
        results.append(taskStr);
        current = current->next;
    }
    
    return results;
}

// Get count of pending tasks
int CampaignTasks::getPendingCount() {
    int count = 0;
    TaskNode* current = head;
    
    while (current != nullptr) {
        if (!current->completed) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

// Get count of completed tasks
int CampaignTasks::getCompletedCount() {
    int count = 0;
    TaskNode* current = head;
    
    while (current != nullptr) {
        if (current->completed) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

// Check if list is empty
bool CampaignTasks::isEmpty() {
    return head == nullptr;
}
