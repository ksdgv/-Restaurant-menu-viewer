#include <algorithm>
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <stdexcept>
#include <string>

using namespace std;

// Function to select menu items by hotel ID
void selectMenuByHotelID(const string &hotelID) {
  try {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(
        "tcp://127.0.0.1:3306", "root1",
        "54325"); // Replace with your database connection details

    con->setSchema("restaurant");

    // Get hotel details
    prep_stmt =
        con->prepareStatement("SELECT hotel_name FROM menu WHERE id = ?");
    prep_stmt->setString(1, hotelID);
    res = prep_stmt->executeQuery();

    if (res->next()) {
      cout << "Hotel ID: " << hotelID << endl;
      cout << "Hotel Name: " << res->getString("hotel_name") << endl;

      // Print menu table header
      cout << left << setw(25) << "Starters" << setw(15) << "Price" << setw(30)
           << "Main Courses" << setw(15) << "Price" << setw(30) << "Desserts"
           << setw(15) << "Price" << setw(30) << "Beverages" << setw(15)
           << "Price" << endl;

      cout << setfill('-') << setw(145) << "-" << setfill(' ') << endl;

      // Prepare and execute the query for menu items
      prep_stmt = con->prepareStatement("SELECT * FROM menu WHERE id = ?");
      prep_stmt->setString(1, hotelID);
      res = prep_stmt->executeQuery();

      // Process the result set
      while (res->next()) {
        // Access individual fields using res->getString or res->getDouble, etc.
        cout << left << setw(25) << res->getString("starters") << fixed
             << setprecision(2) << setw(15) << res->getDouble("starter_price")
             << setw(25) << res->getString("main_courses") << setw(15)
             << res->getDouble("main_price") << setw(15)
             << res->getString("desserts") << setw(15)
             << res->getDouble("dessert_price") << setw(25)
             << res->getString("beverages") << setw(15)
             << res->getDouble("beverages_price") << endl;
      }

      cout << setfill('-') << setw(145) << "-" << setfill(' ') << endl;
    } else {
      cout << "Hotel not found." << endl;
    }

    delete res;
    delete prep_stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "SQL Exception: " << e.what() << endl;
  }
}

void fetchHotelData(const string &hotelType) {
  sql::mysql::MySQL_Driver *driver;
  sql::Connection *con;

  try {
    // Create a MySQL driver instance
    driver = sql::mysql::get_mysql_driver_instance();

    // Connect to the MySQL database
    con = driver->connect("tcp://127.0.0.1:3306", "root1", "54325");
    con->setSchema("restaurant");

    // Create a statement
    sql::Statement *stmt = con->createStatement();

    // Execute the SELECT query with the provided hotel type
    string query =
        "SELECT id, name, ratings FROM hotels WHERE type = '" + hotelType + "'";
    sql::ResultSet *res = stmt->executeQuery(query);

    // Determine maximum column widths
    int maxIdWidth = 0, maxNameWidth = 0, maxRatingsWidth = 0;

    while (res->next()) {
      maxIdWidth =
          max(maxIdWidth, static_cast<int>(res->getString("id").length()));
      maxNameWidth =
          max(maxNameWidth, static_cast<int>(res->getString("name").length()));
      maxRatingsWidth =
          max(maxRatingsWidth,
              10); // Assuming the maximum width for ratings is 10 characters
    }

    // Rewind ResultSet for actual printing
    res->beforeFirst();

    // Print the results with better formatting
    cout << left << setw(maxIdWidth + 2) << "ID" << setw(maxNameWidth + 2)
         << "Name" << setw(maxRatingsWidth + 2) << "Ratings" << endl;
    cout << setfill('-')
         << setw(maxIdWidth + maxNameWidth + maxRatingsWidth + 4) << ""
         << setfill(' ') << endl;

    while (res->next()) {
      cout << left << setw(maxIdWidth + 2) << res->getString("id")
           << setw(maxNameWidth + 2) << res->getString("name")
           << setw(maxRatingsWidth + 2) << res->getDouble("ratings") << endl;
    }

    // Clean up
    delete res;
    delete stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }
}

void book_table(const string &id, const string &dineDate) {
  sql::mysql::MySQL_Driver *driver;
  sql::Connection *con;

  try {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root1", "54325");

    con->setSchema("restaurant");

    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res =
        stmt->executeQuery("SELECT * FROM hotels WHERE id = '" + id + "'");

    if (res->next()) {
      while (res->next()) {
        cout << "==================================================" << endl;
        cout << "                 Booking Information              " << endl;
        cout << "==================================================" << endl;
        cout << "Hotel name: " << res->getString("name")
             << " || Hotel Id: " << res->getString("id") << endl;

        // Generate a random table number between 1 and 10
        int tableNumber = rand() % 10 + 1;

        // Include <iomanip> for setw and setfill
        cout << "Table no: " << setw(2) << tableNumber << endl;

        // Print the date given by the user in DD-MM-YYYY format
        cout << "Dine date: " << dineDate << endl;
        cout << "Address: " << res->getString("address") << endl;
        cout << "Contact number: " << res->getString("contact_number") << endl;
        cout << "==================================================" << endl;
      }

      delete res;
      delete stmt;
      delete con;
    } else {
      throw std::runtime_error("Invalid hotel ID: " + id);
    }
  } catch (sql::SQLException &e) {
    cout << "SQL Error: " << e.what() << endl;
  }
}

// Function to search for hotels based on user inputs
void search(string itemName, double minPrice, double maxPrice,
            double minRating) {
  // Convert itemName to lowercase for case-insensitive search
  transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

  try {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    // Create a connection
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root1", "54325");
    con->setSchema("restaurant");

    // Step 1: Insert relatively matched items into alias table
    stringstream insertQuery;
    insertQuery << "CREATE TEMPORARY TABLE alias_table AS "
                << "SELECT * FROM menu WHERE "
                << "LOWER(starters) LIKE '%" << itemName << "%' OR "
                << "LOWER(main_courses) LIKE '%" << itemName << "%' OR "
                << "LOWER(desserts) LIKE '%" << itemName << "%' OR "
                << "LOWER(beverages) LIKE '%" << itemName << "%'";

    sql::Statement *insertStmt = con->createStatement();
    insertStmt->execute(insertQuery.str());

    // Step 2: Further filter down to another alias table
    stringstream filterQuery;
    filterQuery << "CREATE TEMPORARY TABLE filtered_table AS "
                << "SELECT * FROM alias_table WHERE "
                << "starter_price BETWEEN " << minPrice << " AND " << maxPrice;

    sql::Statement *filterStmt = con->createStatement();
    filterStmt->execute(filterQuery.str());

    // Step 3: Perform ratings on the filtered table
    stringstream ratingQuery;
    ratingQuery
        << "SELECT DISTINCT h.id, h.name AS hotel_name, m.starters, "
           "m.main_courses, m.desserts, m.beverages, "
        << "m.starter_price, m.main_price, m.dessert_price, m.beverages_price "
        << "FROM hotels h JOIN filtered_table m ON h.name = m.hotel_name "
        << "WHERE h.ratings >= " << minRating;

    sql::Statement *ratingStmt = con->createStatement();
    sql::ResultSet *res = ratingStmt->executeQuery(ratingQuery.str());

    // Process the results
    while (res->next()) {
      cout << "Hotel Id: " << res->getString("id")
           << "    Hotel name: " << res->getString("hotel_name") << endl;
      cout << "Items:                                    Price" << endl;
      cout << setw(30) << left << res->getString("starters") << setw(10)
           << right << res->getString("starter_price") << endl;
      cout << setw(30) << left << res->getString("main_courses") << setw(10)
           << right << res->getString("main_price") << endl;
      cout << setw(30) << left << res->getString("desserts") << setw(10)
           << right << res->getString("dessert_price") << endl;
      cout << setw(30) << left << res->getString("beverages") << setw(10)
           << right << res->getString("beverages_price") << endl;
      cout << endl;
    }

    // Cleanup
    delete res;
    delete ratingStmt;
    delete filterStmt;
    delete insertStmt;
    delete con;
  } catch (sql::SQLException &e) {
    cerr << "SQL Error: " << e.what() << endl;
  }
}
