#ifndef PRODUCTIONQUEUE_H
#define PRODUCTIONQUEUE_H

#include "Models.h"

const int QUEUE_SIZE = 50;

bool enqueueOrder(int orderId);   // false if the queue is full
int dequeueOrder();               // returns the order ID, or -1 if empty
int frontOrder();                 // returns the first order ID without removing it, or -1 if empty
bool isQueueEmpty();
bool isQueueFull();
int queueSize();
void displayQueue();

#endif
