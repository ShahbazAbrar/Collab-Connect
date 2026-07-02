#include "include/RequestQueue.h"

// Constructor
RequestQueue::RequestQueue() : front(nullptr), rear(nullptr), size(0), requestIdCounter(0) {}

// Destructor - clean up all nodes
RequestQueue::~RequestQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Enqueue request to rear of queue
void RequestQueue::enqueue(QString brand, QString campaign, QString influencer, int campaignId) {
    requestIdCounter++;
    RequestNode* newRequest = new RequestNode(requestIdCounter, brand, campaign, influencer, campaignId);
    
    if (isEmpty()) {
        front = rear = newRequest;
    } else {
        rear->next = newRequest;
        rear = newRequest;
    }
    
    size++;
}

// Load request with existing ID
void RequestQueue::loadRequest(int id, QString brand, QString campaign, QString influencer, int campaignId, QDateTime timestamp) {
    RequestNode* newRequest = new RequestNode(id, brand, campaign, influencer, campaignId);
    newRequest->timestamp = timestamp;
    
    if (isEmpty()) {
        front = rear = newRequest;
    } else {
        rear->next = newRequest;
        rear = newRequest;
    }
    
    // Update counter if needed to avoid ID conflicts
    if (id > requestIdCounter) {
        requestIdCounter = id;
    }
    
    size++;
}

// Dequeue request from front of queue (FIFO)
RequestNode* RequestQueue::dequeue() {
    if (isEmpty()) {
        return nullptr;
    }
    
    RequestNode* temp = front;
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    size--;
    
    // Note: Caller is responsible for deleting the returned node
    temp->next = nullptr;
    temp->next = nullptr;
    return temp;
}

// Remove specific request by ID
bool RequestQueue::removeRequest(int requestId) {
    if (isEmpty()) return false;
    
    RequestNode* current = front;
    RequestNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->requestId == requestId) {
            if (prev == nullptr) {
                // Removing front
                front = front->next;
                if (front == nullptr) rear = nullptr;
            } else {
                prev->next = current->next;
                if (current == rear) rear = prev;
            }
            
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Peek at front without removing
RequestNode* RequestQueue::peek() {
    return front;
}

// Get all requests as formatted strings
QVector<QString> RequestQueue::getAllRequestsAsStrings() {
    QVector<QString> results;
    RequestNode* current = front;
    
    while (current != nullptr) {
        QString requestStr = QString("Request #%1: %2 wants %3 for '%4' (Campaign ID: %5)\nTime: %6")
            .arg(current->requestId)
            .arg(current->brandName)
            .arg(current->influencerName)
            .arg(current->campaignName)
            .arg(current->campaignId)
            .arg(current->timestamp.toString("yyyy-MM-dd hh:mm"));
        
        results.append(requestStr);
        current = current->next;
    }
    
    return results;
}

// Check if queue is empty
bool RequestQueue::isEmpty() {
    return front == nullptr;
}

// Get queue size
int RequestQueue::getSize() {
    return size;
}
