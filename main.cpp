// main.cpp

#include "mainwindow.h"
#include <QApplication>

// --- DSA Structure Placeholders ---
// You will implement your Binary Search Tree (BST) and Linked List (LL)
// data structures and related logic here or in dedicated helper files.

#include "include/SystemManager.h" // <--- Include backend

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Create SystemManager once
    SystemManager* manager = new SystemManager(); 
    
    // Pass it to MainWindow
    MainWindow w(manager);
    w.show();
    
    int result = a.exec();
    
    // Cleanup
    delete manager;
    
    return result;
}
