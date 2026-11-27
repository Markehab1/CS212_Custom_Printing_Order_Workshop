#include "MaterialList.h"
#include "Sorting.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

namespace {

int failures = 0;

// Prints the result of one test and counts any failure for the final summary.
void check(bool passed, const char* description) {
  cout << (passed ? "[PASS] " : "[FAIL] ") << description << '\n';
  if (!passed) {
    ++failures;
  }
}

// Finds a material by ID and checks every field against the expected record.
bool materialMatches(const Material& expected) {
  const Material* actual = findMaterial(expected.id);
  return actual != NULL && actual->id == expected.id &&
         actual->name == expected.name && actual->price == expected.price &&
         actual->stock == expected.stock;
}

// Walks from the head and checks that the IDs match in order with no extra nodes.
bool listOrderMatches(initializer_list<int> expectedIds) {
  const MaterialNode* node = materialHead;
  for (int expectedId : expectedIds) {
    if (node == NULL || node->data.id != expectedId) {
      return false;
    }
    node = node->next;
  }
  return node == NULL;
}

// Sends displayMaterials output to a string so tests can check what it prints.
string captureDisplay() {
  ostringstream output;
  streambuf* original = cout.rdbuf(output.rdbuf());
  displayMaterials();
  cout.rdbuf(original);
  return output.str();
}

}  // namespace

// Runs the linked-list and sorting tests. A nonzero exit code signals a failure.
int main() {
  const Material canvas = {10, "Canvas", 15.75, 7};
  const Material paper = {20, "Paper", 3.25, 38};
  const Material cotton = {30, "Cotton", 11.50, 14};
  const Material vinyl = {40, "Vinyl", 21.90, 0};
  const Material updatedCanvas = {10, "Canvas", 18.25, 12};

  check(isMaterialListEmpty(), "isMaterialListEmpty returns true for a new list");
  check(countMaterials() == 0, "countMaterials returns zero for a new list");
  check(captureDisplay() == "No materials\n", "displayMaterials reports an empty list");
  check(!deleteMaterial(10), "deleteMaterial rejects an empty list");
  sortMaterialsByPrice();
  check(isMaterialListEmpty(), "sortMaterialsByPrice handles an empty list");

  check(addMaterial(canvas), "addMaterial accepts the first valid material");
  check(materialMatches(canvas), "findMaterial returns the record for an existing ID");
  check(findMaterial(999) == NULL, "findMaterial returns NULL for a missing ID");
  check(!isMaterialListEmpty(), "isMaterialListEmpty returns false after adding a material");
  sortMaterialsByPrice();
  check(listOrderMatches({10}) && materialMatches(canvas),
        "sortMaterialsByPrice handles a one-item list");

  check(!addMaterial({10, "Duplicate", 2.0, 1}), "addMaterial rejects a duplicate ID");
  check(!addMaterial({50, "Invalid", -1.0, 1}), "addMaterial rejects a negative price");
  check(!addMaterial({50, "Invalid", 1.0, -1}), "addMaterial rejects negative stock");
  check(!addMaterial({50, "Invalid", numeric_limits<double>::quiet_NaN(), 1}),
        "addMaterial rejects a nonfinite price");
  check(countMaterials() == 1 && materialMatches(canvas),
        "Rejected additions preserve the existing record and count");

  check(updateMaterial(10, updatedCanvas.price, updatedCanvas.stock) &&
        materialMatches(updatedCanvas), "updateMaterial changes the price and stock");
  check(!updateMaterial(999, 2.0, 1), "updateMaterial rejects a missing ID");
  check(!updateMaterial(10, -1.0, 1), "updateMaterial rejects a negative price");
  check(!updateMaterial(10, 2.0, -1), "updateMaterial rejects negative stock");
  check(!updateMaterial(10, numeric_limits<double>::infinity(), 1),
        "updateMaterial rejects a nonfinite price");
  check(materialMatches(updatedCanvas), "Rejected updates preserve the existing record");

  check(addMaterial(paper), "addMaterial accepts a second material");
  check(addMaterial(cotton), "addMaterial accepts a third material");
  check(addMaterial(vinyl), "addMaterial accepts zero stock");
  check(countMaterials() == 4, "countMaterials returns four for a populated list");
  sortMaterialsByPrice();
  check(listOrderMatches({20, 30, 10, 40}), "sortMaterialsByPrice orders prices cheapest first");
  check(materialMatches(paper) && materialMatches(cotton) &&
        materialMatches(updatedCanvas) && materialMatches(vinyl),
        "Sorting keeps IDs, names, prices, and stock together");

  const string table = captureDisplay();
  check(table.find("ID") != string::npos && table.find("Name") != string::npos &&
        table.find("Price") != string::npos && table.find("Stock") != string::npos,
        "displayMaterials prints all four column headings");
  check(table.find("Paper") < table.find("Cotton") &&
        table.find("Cotton") < table.find("Canvas") &&
        table.find("Canvas") < table.find("Vinyl") && table.find("Vinyl") != string::npos,
        "displayMaterials prints each material in price order");
  check(table.find("3.25") != string::npos && table.find("11.50") != string::npos &&
        table.find("18.25") != string::npos && table.find("21.90") != string::npos,
        "displayMaterials shows prices to two decimal places");
  cout << "\nSorted materials table\n" << table << '\n';

  check(!deleteMaterial(999) && countMaterials() == 4, "deleteMaterial rejects a missing ID");
  check(deleteMaterial(10) && listOrderMatches({20, 30, 40}) && findMaterial(10) == NULL,
        "deleteMaterial removes a middle node");
  check(deleteMaterial(20) && listOrderMatches({30, 40}), "deleteMaterial removes the head");
  check(deleteMaterial(40) && listOrderMatches({30}), "deleteMaterial removes the tail");
  check(updateMaterial(30, 0.0, 0) && materialMatches({30, "Cotton", 0.0, 0}),
        "updateMaterial accepts zero price and stock");
  check(deleteMaterial(30) && isMaterialListEmpty() && countMaterials() == 0,
        "deleteMaterial removes the only remaining node");

  const Material sample = {50, "Sample", 0.0, 0};
  const Material swatch = {60, "Swatch", 0.0, 2};
  check(addMaterial(paper) && addMaterial(sample) && addMaterial(swatch),
        "addMaterial accepts zero price and stock");
  sortMaterialsByPrice();
  check((listOrderMatches({50, 60, 20}) || listOrderMatches({60, 50, 20})) &&
        materialMatches(sample) && materialMatches(swatch) && materialMatches(paper),
        "sortMaterialsByPrice keeps both records with matching prices");
  deleteMaterial(50);
  deleteMaterial(60);
  deleteMaterial(20);

  if (failures == 0) {
    cout << "\nAll materials tests passed.\n";
    return 0;
  }
  cout << '\n' << failures << " materials test(s) failed.\n";
  return 1;
}
