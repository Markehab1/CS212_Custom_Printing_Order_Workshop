#include "Sorting.h"

namespace {

MaterialNode* mergeByPrice(MaterialNode* left, MaterialNode* right) {
  MaterialNode* head = nullptr;
  MaterialNode** nextLink = &head;

  while (left != nullptr && right != nullptr) {
    // Pick from the left half on ties to keep the original order.
    if (left->data.price <= right->data.price) {
      *nextLink = left;
      left = left->next;
    } else {
      *nextLink = right;
      right = right->next;
    }
    nextLink = &(*nextLink)->next;
  }

  *nextLink = left == nullptr ? right : left;
  return head;
}

MaterialNode* mergeSortByPrice(MaterialNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  MaterialNode* middle = head;
  MaterialNode* fast = head->next;
  while (fast != nullptr && fast->next != nullptr) {
    middle = middle->next;
    fast = fast->next->next;
  }

  MaterialNode* right = middle->next;
  middle->next = nullptr;
  return mergeByPrice(mergeSortByPrice(head), mergeSortByPrice(right));
}

}  // namespace

void sortMaterialsByPrice() {
  materialHead = mergeSortByPrice(materialHead);
}
