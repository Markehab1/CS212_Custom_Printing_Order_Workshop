#ifndef ORDERBST_H
#define ORDERBST_H

#include "Models.h"

struct OrderNode {
  Order data;
  OrderNode* left;
  OrderNode* right;
};

extern OrderNode* orderRoot;

bool insertOrder(Order o);     // false if the orderId already exists
Order* searchOrder(int id);    // NULL if not found
bool deleteOrder(int id);      // false if not found (handles 0, 1 and 2 children)
void inorderOrders();          // prints orders sorted by ID
void preorderOrders();
void postorderOrders();
int countOrders();
bool isTreeEmpty();

#endif
