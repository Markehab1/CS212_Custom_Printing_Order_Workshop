#ifndef MATERIALLIST_H
#define MATERIALLIST_H

#include "Models.h"

struct MaterialNode {
  Material data;
  MaterialNode* next;
};

extern MaterialNode* materialHead;

bool addMaterial(Material m);                                // false if ID is duplicate or price/stock is negative
bool deleteMaterial(int id);                                 // false if ID not found
Material* findMaterial(int id);                              // NULL if not found
bool updateMaterial(int id, double newPrice, int newStock);  // false if not found or values invalid
void displayMaterials();                                     // prints a table, or "No materials" if empty
int countMaterials();
bool isMaterialListEmpty();

#endif
