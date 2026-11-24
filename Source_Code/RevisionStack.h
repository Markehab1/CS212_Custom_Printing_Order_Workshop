#ifndef REVISIONSTACK_H
#define REVISIONSTACK_H

#include "Models.h"

const int STACK_SIZE = 100;

bool pushRevision(Revision r);    // false if the stack is full
bool popRevision(Revision &r);    // false if empty; otherwise puts the top revision in r and removes it
bool peekRevision(Revision &r);   // false if empty; otherwise puts the top revision in r without removing it
bool isStackEmpty();
bool isStackFull();
int stackSize();
void displayRevisions();          // prints from top to bottom

#endif
