#include "Sorting.h"

#include <cstddef>
#include <utility>

using namespace std;

// Uses the Lab 5 exchange sort to order materials from cheapest to most expensive.
// Compares the current record with each later record and swaps if the later price is lower.
// Each pass leaves the cheapest remaining material at the current node.
// For n materials it makes n(n - 1) / 2 comparisons, taking O(n^2) time and O(1) extra space.
void sortMaterialsByPrice() {
  for (MaterialNode* current = materialHead; current != NULL; current = current->next) {
    for (MaterialNode* later = current->next; later != NULL; later = later->next) {
      if (current->data.price > later->data.price) {
        // Keep the ID, name, price, and stock together when exchanging records.
        swap(current->data, later->data);
      }
    }
  }
}
