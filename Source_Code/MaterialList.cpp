#include "MaterialList.h"
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
using namespace std;


MaterialNode* materialHead = NULL;

// Appends a material with a finite, nonnegative price and nonnegative stock.
// One walk checks for a duplicate ID and finds the last node in O(n) time.
// If the list is empty, the new node becomes the head.
bool addMaterial(Material m) {
  if (!isfinite(m.price) || m.price < 0 || m.stock < 0) {
    return false;
  }

  MaterialNode* last = NULL;
  for (MaterialNode* current = materialHead; current != NULL; current = current->next) {
    if (current->data.id == m.id) {
      return false;
    }
    last = current;
  }

  MaterialNode* node = new MaterialNode{m, NULL};
  if (last == NULL) {
    materialHead = node;
  } else {
    last->next = node;
  }
  return true;
}

// Looks for the ID in O(n) time while keeping track of the previous node.
// Updates the head or the previous node's next pointer, then frees the node.
// Returns false if the ID is missing.
bool deleteMaterial(int id) {
  MaterialNode* previous = NULL;
  MaterialNode* current = materialHead;
  while (current != NULL && current->data.id != id) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    return false;
  }

  if (previous == NULL) {
    materialHead = current->next;
  } else {
    previous->next = current->next;
  }
  delete current;
  return true;
}

// Follows the next pointers from the head to search for the ID in O(n) time.
// Returns the address of the stored record, or NULL if the ID is missing.
Material* findMaterial(int id) {
  for (MaterialNode* current = materialHead; current != NULL; current = current->next) {
    if (current->data.id == id) {
      return &current->data;
    }
  }
  return NULL;
}

// Checks the new price and stock, then looks up the material by ID.
// Changes only those two fields and returns false if either check fails.
// The lookup takes O(n) time in the worst case.
bool updateMaterial(int id, double newPrice, int newStock) {
  if (!isfinite(newPrice) || newPrice < 0 || newStock < 0) {
    return false;
  }

  Material* material = findMaterial(id);
  if (material == NULL) {
    return false;
  }

  material->price = newPrice;
  material->stock = newStock;
  return true;
}

// Prints an empty-list message or shows the ID, name, price, and stock of each material.
// Visits each node once and displays prices to two decimal places.
// Restores cout's flags and precision after printing the table.
void displayMaterials() {
  if (isMaterialListEmpty()) {
    cout << "No materials\n";
    return;
  }

  const int idWidth = 11;
  const int nameWidth = 22;
  const int priceWidth = 12;
  const int stockWidth = 10;
  const ios::fmtflags previousFlags = cout.flags();
  const streamsize previousPrecision = cout.precision();

  cout << right << setw(idWidth) << "ID" << " | "
       << left << setw(nameWidth) << "Name" << " | "
       << right << setw(priceWidth) << "Price" << " | "
       << setw(stockWidth) << "Stock" << '\n';

  cout << fixed << setprecision(2);
  for (const MaterialNode* current = materialHead; current != NULL; current = current->next) {
    const Material& material = current->data;
    cout << right << setw(idWidth) << material.id << " | "
         << left << setw(nameWidth) << material.name << " | "
         << right << setw(priceWidth) << material.price << " | "
         << setw(stockWidth) << material.stock << '\n';
  }

  cout.flags(previousFlags);
  cout.precision(previousPrecision);
}

// Counts one material per node by walking from the head to NULL in O(n) time.
int countMaterials() {
  int count = 0;
  for (const MaterialNode* current = materialHead; current != NULL; current = current->next) {
    ++count;
  }
  return count;
}

// Checks whether the head is NULL in O(1) time.
bool isMaterialListEmpty() {
  return materialHead == NULL;
}
