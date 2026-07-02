#include "include/NotificationStack.h"

// Constructor
NotificationStack::NotificationStack(int max) : maxSize(max) {
    items.reserve(max);
}

// Push notification to top of stack
void NotificationStack::push(QString message, QString category, QString recipient) {
    if (items.size() >= maxSize) {
        // Remove oldest notification (at bottom) if at max capacity
        items.removeFirst();
    }
    
    Notification notif(message, category, recipient);
    items.append(notif);
}

// Pop notification from top of stack (LIFO)
Notification NotificationStack::pop() {
    if (isEmpty()) {
        return Notification("", "SYSTEM");
    }
    
    Notification top = items.last();
    items.removeLast();
    return top;
}

// Peek at top without removing
Notification NotificationStack::peek() {
    if (isEmpty()) {
        return Notification("", "SYSTEM");
    }
    
    return items.last();
}

// Get all notifications as strings (top to bottom)
QVector<QString> NotificationStack::getAllNotificationsAsStrings() {
    QVector<QString> results;
    
    // Iterate from top to bottom (reverse order)
    for (int i = items.size() - 1; i >= 0; i--) {
        QString readStatus = items[i].isRead ? "[Read]" : "[New]";
        QString notifStr = QString("%1 [%2] %3\n%4")
            .arg(readStatus)
            .arg(items[i].category)
            .arg(items[i].message)
            .arg(items[i].timestamp.toString("yyyy-MM-dd hh:mm"));
        
        results.append(notifStr);
    }
    
    return results;
}

// Clear all notifications
void NotificationStack::clear() {
    items.clear();
}

// Check if stack is empty
bool NotificationStack::isEmpty() {
    return items.isEmpty();
}

// Get stack size
int NotificationStack::getSize() {
    return items.size();
}
