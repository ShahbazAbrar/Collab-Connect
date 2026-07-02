#ifndef NOTIFICATIONSTACK_H
#define NOTIFICATIONSTACK_H

#include <QString>
#include <QVector>
#include <QDateTime>

// Notification structure
struct Notification {
    QString message;
    QDateTime timestamp;
    QString category; // "REQUEST", "TASK", "CAMPAIGN", "SYSTEM"
    QString recipient; // "ALL", "brand", or specific username
    bool isRead;
    
    // Constructor
    Notification(QString msg = "", QString cat = "SYSTEM", QString rcpt = "ALL")
        : message(msg), timestamp(QDateTime::currentDateTime()), 
          category(cat), recipient(rcpt), isRead(false) {}
};

// Stack for LIFO notification management
class NotificationStack {
    friend class SystemManager;
private:
    QVector<Notification> items;
    int maxSize;
    
public:
    NotificationStack(int max = 100);
    
    // Push notification to top
    void push(QString message, QString category = "SYSTEM", QString recipient = "ALL");
    
    // Pop notification from top
    Notification pop();
    
    // Peek at top without removing
    Notification peek();
    
    // Get all notifications as strings (top to bottom)
    QVector<QString> getAllNotificationsAsStrings();
    
    // Clear all notifications
    void clear();
    
    // Utility
    bool isEmpty();
    int getSize();
};

#endif // NOTIFICATIONSTACK_H
