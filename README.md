# Restaurant Menu Viewer

## Team: Loop99
- **Abhin S Jacob (Team Leader)**
- **Deevankumar Gaddala**
- **Keeran Dhami**
- **Satwik Kotta**

## Overview
Restaurant Menu Viewer allows users to:
- View nearby restaurants along with their names, addresses, and cuisines.
- Select a restaurant to browse its menu.
- Search and filter menu items by keywords, price range, and rating.
- Optionally book a table for dining.

## Features
- **Restaurant Listing**: Displays nearby restaurants using a predefined list or API.
- **Menu Viewing**: Organized menu categories (starters, main courses, desserts, beverages).
- **Search & Filter**: Search menu items and apply filters.
- **Table Booking**: Reserve a table if the restaurant supports booking.

## Technology Stack
- **Language**: C++
- **Database**: MySQL
- **API**: Google Maps API (optional)
- **Libraries**: `mysqlcppconn` for MySQL connectivity

## Usage
1. Run the application using:
   ```bash
   g++ -o restaurant main.cpp functions.cpp -lstdc++ -lmysqlcppconn
   ./restaurant
