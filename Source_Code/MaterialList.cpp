#include "MaterialList.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

MaterialNode* materialHead = nullptr;

namespace {

// Return the link to the matching node, or the empty link at the end.
MaterialNode** findMaterialLink(int id) {
  MaterialNode** link = &materialHead;
  while (*link != nullptr && (*link)->data.id != id) {
    link = &(*link)->next;
  }
  return link;
}

bool hasValidValues(double price, int stock) {
  return price >= 0.0 && stock >= 0;
}

}  // namespace

bool addMaterial(Material m) {
  if (!hasValidValues(m.price, m.stock)) {
    return false;
  }

  MaterialNode** link = findMaterialLink(m.id);
  if (*link != nullptr) {
    return false;
  }

  *link = new MaterialNode{std::move(m), nullptr};
  return true;
}

bool deleteMaterial(int id) {
  MaterialNode** link = findMaterialLink(id);
  MaterialNode* node = *link;
  if (node == nullptr) {
    return false;
  }

  *link = node->next;
  delete node;
  return true;
}

Material* findMaterial(int id) {
  MaterialNode* node = *findMaterialLink(id);
  return node == nullptr ? nullptr : &node->data;
}

bool updateMaterial(int id, double newPrice, int newStock) {
  if (!hasValidValues(newPrice, newStock)) {
    return false;
  }

  Material* material = findMaterial(id);
  if (material == nullptr) {
    return false;
  }

  material->price = newPrice;
  material->stock = newStock;
  return true;
}

void displayMaterials() {
  std::stringstream table;
  if (isMaterialListEmpty()) {
    table << "No materials\n";
  } else {
    table << std::left << std::setw(10) << "ID" << " | "
          << std::setw(24) << "Name" << " | " << std::right
          << std::setw(12) << "Price" << " | " << std::setw(10) << "Stock" << '\n';

    table << std::fixed << std::setprecision(2);
    for (const MaterialNode* node = materialHead; node != nullptr; node = node->next) {
      const Material& material = node->data;
      table << std::left << std::setw(10) << material.id << " | "
            << std::setw(24) << material.name << " | " << std::right
            << std::setw(12) << material.price << " | " << std::setw(10) << material.stock << '\n';
    }
  }
  std::cout << table.rdbuf();
}

int countMaterials() {
  int count = 0;
  for (const MaterialNode* node = materialHead; node != nullptr; node = node->next) {
    ++count;
  }
  return count;
}

bool isMaterialListEmpty() {
  return materialHead == nullptr;
}
