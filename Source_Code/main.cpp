#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>   // for system()
#include "MaterialList.h"
#include "Sorting.h"
#include "Search.h"
#include "ProductionQueue.h"
#include "RevisionStack.h"
#include "OrderBST.h"
using namespace std;

// ================= Input helpers =================

// Keeps asking until the user types a whole number
int readInt(string prompt) {
  int value;
  while (true) {
    cout << prompt;
    cin >> value;
    if (cin.fail() || cin.peek() != '\n') {
      cin.clear();                                          // clear the error
      cin.ignore(numeric_limits<streamsize>::max(), '\n');  // throw away the bad line
      cout << "Invalid input, please enter a number.\n";
    } else {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return value;
    }
  }
}

// Same idea, for prices
double readDouble(string prompt) {
  double value;
  while (true) {
    cout << prompt;
    cin >> value;
    if (cin.fail() || cin.peek() != '\n') {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input, please enter a number.\n";
    } else {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return value;
    }
  }
}

// Reads a full line (so "Logo A" with a space works)
string readText(string prompt) {
  string text;
  while (true) {
    cout << prompt;
    getline(cin, text);
    if (text != "") {
      return text;
    }
    cout << "This field can't be empty.\n";
  }
}

// Clears the console window
void clearScreen() {
#ifdef _WIN32
  system("cls");      // Windows
#else
  system("clear");    // Mac / Linux
#endif
}

// Waits so the user can read the result before the screen clears
void pauseScreen() {
  cout << "\nPress Enter to continue...";
  string dummy;
  getline(cin, dummy);
}

void comingSoon() {
  cout << "Coming soon...\n";
}

// ================= Sub-menus =================

void materialsMenu() {
  int choice;
  do {
    clearScreen();
    cout << "----- Materials -----\n";
    cout << "1. Add material\n";
    cout << "2. Delete material\n";
    cout << "3. Update material\n";
    cout << "4. Find material by ID\n";
    cout << "5. Find material by name\n";
    cout << "6. Show all materials\n";
    cout << "7. Sort materials by price\n";
    cout << "8. Restock material\n";
    cout << "0. Back\n";
    choice = readInt("Choose: ");

    switch (choice) {
      case 1: comingSoon(); break;
      case 2: comingSoon(); break;
      case 3: comingSoon(); break;
      case 4: comingSoon(); break;
      case 5: comingSoon(); break;
      case 6: comingSoon(); break;
      case 7: comingSoon(); break;
      case 8: comingSoon(); break;
      case 0: break;
      default: cout << "Invalid choice, try again.\n";
    }

    if (choice != 0) {
      pauseScreen();
    }
  } while (choice != 0);
}

void ordersMenu() {
  int choice;
  do {
    clearScreen();
    cout << "----- Orders -----\n";
    cout << "1. Place order\n";
    cout << "2. Find order by ID\n";
    cout << "3. Change order design\n";
    cout << "4. Undo last design change\n";
    cout << "5. Delete order\n";
    cout << "0. Back\n";
    choice = readInt("Choose: ");

    switch (choice) {
      case 1: comingSoon(); break;
      case 2: comingSoon(); break;
      case 3: comingSoon(); break;
      case 4: comingSoon(); break;
      case 5: comingSoon(); break;
      case 0: break;
      default: cout << "Invalid choice, try again.\n";
    }

    if (choice != 0) {
      pauseScreen();
    }
  } while (choice != 0);
}

void productionMenu() {
  int choice;
  do {
    clearScreen();
    cout << "----- Production -----\n";
    cout << "1. Produce next order\n";
    cout << "2. Show waiting orders\n";
    cout << "0. Back\n";
    choice = readInt("Choose: ");

    switch (choice) {
      case 1: comingSoon(); break;
      case 2: comingSoon(); break;
      case 0: break;
      default: cout << "Invalid choice, try again.\n";
    }

    if (choice != 0) {
      pauseScreen();
    }
  } while (choice != 0);
}

void reportsMenu() {
  int choice;
  do {
    clearScreen();
    cout << "----- Reports -----\n";
    cout << "1. All orders (inorder - sorted by ID)\n";
    cout << "2. All orders (preorder)\n";
    cout << "3. All orders (postorder)\n";
    cout << "4. Design revision history\n";
    cout << "0. Back\n";
    choice = readInt("Choose: ");

    switch (choice) {
      case 1: comingSoon(); break;
      case 2: comingSoon(); break;
      case 3: comingSoon(); break;
      case 4: comingSoon(); break;
      case 0: break;
      default: cout << "Invalid choice, try again.\n";
    }

    if (choice != 0) {
      pauseScreen();
    }
  } while (choice != 0);
}

// ================= Main menu =================

int main() {
  int choice;
  do {
    clearScreen();
    cout << "===== Custom Printing Order Workshop =====\n";
    cout << "1. Materials\n";
    cout << "2. Orders\n";
    cout << "3. Production\n";
    cout << "4. Reports\n";
    cout << "0. Exit\n";
    choice = readInt("Choose: ");

    switch (choice) {
      case 1: materialsMenu(); break;
      case 2: ordersMenu(); break;
      case 3: productionMenu(); break;
      case 4: reportsMenu(); break;
      case 0: cout << "Goodbye!\n"; break;
      default:
        cout << "Invalid choice, try again.\n";
        pauseScreen();
    }
  } while (choice != 0);

  return 0;
}