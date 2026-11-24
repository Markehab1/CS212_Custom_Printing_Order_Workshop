#ifndef MODELS_H
#define MODELS_H

#include <string>
using namespace std;

// A material the workshop prints on (stored in the Linked List)
struct Material {
    int id;
    string name;
    double price;
    int stock;
};

// A printing order (stored in the BST, its ID waits in the Queue)
struct Order {
    int orderId;
    string customer;
    int materialId;
    int qty;
    string design;
    string status;   // "Pending" or "Done"
};

// An old design saved before a change (stored in the Stack for Undo)
struct Revision {
    int orderId;
    string oldDesign;
};

#endif