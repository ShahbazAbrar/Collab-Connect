#ifndef CAMPAIGNTASKS_H
#define CAMPAIGNTASKS_H

#include <QString>
#include <QVector>

// Task node for linked list
struct TaskNode {
    int taskId;
    QString description;
    bool completed;
    QString deadline;
    TaskNode* next;
    
    // Constructor
    TaskNode(int id, QString desc, QString dl = "")
        : taskId(id), description(desc), completed(false), 
          deadline(dl), next(nullptr) {}
};

// Singly Linked List for managing campaign tasks
class CampaignTasks {
    friend class SystemManager;
private:
    TaskNode* head;
    int taskCounter;
    
public:
    CampaignTasks();
    
    // Add task to end of list
    void addTask(QString description, QString deadline = "");
    // Load task with existing ID
    void loadTask(int id, QString description, bool completed, QString deadline);
    
    // Mark task as completed
    bool markComplete(int taskId);
    
    // Retrieve all tasks as formatted strings
    QVector<QString> getAllTasksAsStrings();
    
    // Get counts
    int getPendingCount();
    int getCompletedCount();
    
    // Utility
    bool isEmpty();
    
    ~CampaignTasks();
};

#endif // CAMPAIGNTASKS_H
