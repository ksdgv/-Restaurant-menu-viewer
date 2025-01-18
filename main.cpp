#include <iostream>
#include <limits>
#include <string>

using namespace std;

void fetchHotelData(const string &hotelType);
void selectMenuByHotelID(const string &hotelID);
void book_table(const string &id, const string &dineDate);
void search(string itemName, double minPrice, double maxPrice,
            double minRating);

class HotelManager {
public:
  void run() {
    while (start) {
      displayMainMenu();
      choice = getValidChoice();

      if (choice == 1) {
        handleRestaurantMenu();
      } else if (choice = 2) {
        handleSearch();
      } else if (choice == 3) {
        start = false;
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
    cout << "== Loop99 has been wrapped up. ==" << endl;
  }

private:
  string hotelID;
  string date;
  bool start = true;
  int choice;

  void displayMainMenu() const {
    cout << "1. Restaurants\n"
         << "2. Search\n"
         << "3. Exit\n";
  }

  int getValidChoice() {
    while (true) {
      cout << "Enter your choice: ";
      cin >> choice;
      cout << "-------------------------------------------------------\n";

      if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid number.\n";
      } else {
        break;
      }
    }
    return choice;
  }

  void handleRestaurantMenu() {
    while (start) {
      displayRestaurantMenu();
      choice = getValidChoice();

      if (choice == 1) {
        handleHotelType("Pure Veg");
      } else if (choice == 2) {
        handleHotelType("Non-veg");
      } else if (choice == 3) {
        break;
      } else if (choice == 4) {
        start = false;
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  }

  void displayRestaurantMenu() const {
    cout << "-------------------------------------------------------\n"
         << "1. Veg\n"
         << "2. Non-veg\n"
         << "3. Back\n"
         << "4. Exit\n"
         << "-------------------------------------------------------\n";
  }

  void handleHotelType(const string &hotelType) {
    while (start) {
      fetchHotelData(hotelType);
      displayHotelOptions();
      choice = getValidChoice();

      if (choice == 1) {
        handleHotelMenu();
      } else if (choice == 2) {
        bookTable();
      } else if (choice == 3) {
        break;
      } else if (choice == 4) {
        start = false;
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  }

  void displayHotelOptions() const {
    cout << "-------------------------------------------------------\n"
         << "1. Hotel Menu\n"
         << "2. Book table\n"
         << "3. Back\n"
         << "4. Exit\n"
         << "-------------------------------------------------------\n";
  }

  void handleHotelMenu() {
    cout << "Enter hotel ID: ";
    cin >> hotelID;
    selectMenuByHotelID(hotelID);

    while (start) {
      displayBookTableOptions();
      choice = getValidChoice();

      if (choice == 1) {
        bookTable();
      } else if (choice == 2) {
        break;
      } else if (choice == 3) {
        start = false;
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  }

  void displayBookTableOptions() const {
    cout << "-------------------------------------------------------\n"
         << "1. Book table\n"
         << "2. Back\n"
         << "3. Exit\n"
         << "-------------------------------------------------------\n";
  }

  void bookTable() {
    cout << "Enter hotel ID: ";
    cin >> hotelID;
    cout << "Enter Date in 'DD-MM-YYYY': ";
    cin >> date;
    book_table(hotelID, date);
    confirmBooking();
  }

  void confirmBooking() {
    while (start) {
      displayConfirmationOptions();
      choice = getValidChoice();

      if (choice == 1) {
        cout << "------------------------------------------------------\n"
             << "===Table is booked successfully===\n"
             << "------------------------------------------------------\n";
        start = false;
      } else if (choice == 2) {
        break;
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  }

  void displayConfirmationOptions() const {
    cout << "-------------------------------------------------------\n"
         << "1. Confirm\n"
         << "2. Back\n"
         << "-------------------------------------------------------\n";
  }

  void handleSearch() {
    while (start) {
      string itemName;
      double minPrice = 0.0, maxPrice = 1000.0, minRating = 0.0;

      getUserInputs(itemName, minPrice, maxPrice, minRating);
      search(itemName, minPrice, maxPrice, minRating);

      displayBookTableOptions();
      int innerChoice = getValidChoice();

      if (innerChoice == 1) {
        bookTable();
      } else if (innerChoice == 2) {
        break;
      } else if (innerChoice == 3) {
        start = false;
      }
    }
  }

  void getUserInputs(string &itemName, double &minPrice, double &maxPrice,
                     double &minRating) const {
    cout << "Enter item name: ";
    cin >> itemName;

    cout << "Enter minimum price: ";
    cin >> minPrice;

    cout << "Enter maximum price: ";
    cin >> maxPrice;

    cout << "Enter minimum rating: ";
    cin >> minRating;
  }
};

int main() {
  HotelManager hotelManager;
  hotelManager.run();

  return 0;
}

