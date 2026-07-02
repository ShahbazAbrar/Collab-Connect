#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <QString>
#include <QVector>
#include <QDateTime>

// Request node for queue
struct RequestNode {
    int requestId;
    QString brandName;
    QString campaignName;
    QString influencerName;
    int campaignId;
    QDateTime timestamp;
    RequestNode* next;
    
    // Constructor
    RequestNode(int id, QString brand, QString campaign, QString influencer, int campId)
        : requestId(id), brandName(brand), campaignName(campaign), 
          influencerName(influencer), campaignId(campId), 
          timestamp(QDateTime::currentDateTime()), next(nullptr) {}
};

// Queue for FIFO collaboration request handling
class RequestQueue {
    friend class SystemManager;
private:
    RequestNode* front;
    RequestNode* rear;
    int size;
    int requestIdCounter;
    
public:
    RequestQueue();
    
    // Enqueue request to rear
    void enqueue(QString brand, QString campaign, QString influencer, int campaignId = 0);
    // Load request with existing ID (for persistence)
    void loadRequest(int id, QString brand, QString campaign, QString influencer, int campaignId, QDateTime timestamp);
    
    // Dequeue request from front
    RequestNode* dequeue();

    // Remove specific request by ID (for dashboard interaction)
    bool removeRequest(int requestId);

    // Peek at front without removing
    
    // Peek at front without removing
    RequestNode* peek();
    
    // Get all requests as strings
    QVector<QString> getAllRequestsAsStrings();
    
    // Utility
    bool isEmpty();
    int getSize();
    
    ~RequestQueue();
};

#endif // REQUESTQUEUE_H
