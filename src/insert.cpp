#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Function to replace single quotes in a string with two single quotes
string replaceSingleQuotes(const string& input) {
    string result;
    for (char c : input) {
        if (c == '\'') {
            result += "''";
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        // Connect to the MySQL server
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root1", "54325");
        con->setSchema("restaurant");

        // Read CSV file and insert data into the 'menu' table
        ifstream inputFile("menu.csv");
        if (!inputFile.is_open()) {
            cerr << "Error opening file." << endl;
            return 1;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream ss(line);
            string id, hotel_name, starters, main_courses, desserts, beverages;
            double starter_price, main_price, dessert_price, beverages_price;

            getline(ss, id, ',');
            getline(ss, hotel_name, ',');
            getline(ss, starters, ',');
            getline(ss, main_courses, ',');
            getline(ss, desserts, ',');
            getline(ss, beverages, ',');

            ss >> starter_price;
            ss.ignore(); // Ignore the comma
            ss >> main_price;
            ss.ignore(); // Ignore the comma
            ss >> dessert_price;
            ss.ignore(); // Ignore the comma
            ss >> beverages_price;

            // Replace single quotes in strings with two single quotes
            id = replaceSingleQuotes(id);
            hotel_name = replaceSingleQuotes(hotel_name);
            starters = replaceSingleQuotes(starters);
            main_courses = replaceSingleQuotes(main_courses);
            desserts = replaceSingleQuotes(desserts);
            beverages = replaceSingleQuotes(beverages);

            // Insert data into the 'menu' table
            sql::Statement *stmt = con->createStatement();
            stmt->execute("INSERT INTO menu (id, hotel_name, starters, main_courses, desserts, beverages, "
                          "starter_price, main_price, dessert_price, beverages_price) VALUES "
                          "('" + id + "', '" + hotel_name + "', '" + starters + "', '" + main_courses + "', '" +
                          desserts + "', '" + beverages + "', " + to_string(starter_price) + ", " +
                          to_string(main_price) + ", " + to_string(dessert_price) + ", " + to_string(beverages_price) +
                          ")");
            delete stmt;
        }

        cout << "Data inserted successfully." << endl;

        delete con;
    } catch (sql::SQLException &e) {
        cerr << "SQL Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}

