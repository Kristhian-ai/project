# ✈️ Flight Booking System

A console-based C++ application that allows users to browse available flights, check prices, and book tickets. Built as a solo project, this system handles flight management, user bookings, and pricing using simple CSV file storage—ideal for learning file handling and system design in C++.

## 🚀 Features

- View available flights and destinations
- Display flight pricing information
- Book flights with basic user input
- Store user and booking data in CSV files
- Command-line user interaction

## 🛠 Technologies Used

- **Language:** C++  
- **IDE:** Visual Studio Code (with `.vscode` settings)  
- **Data Storage:** CSV files (`availableflights.csv`, `flightprices.csv`, `passengerflights.csv`, `users.csv`)

## ▶️ How to Run the Project

1. **Clone or Download the Repository**
   ```bash
   git clone https://github.com/Kristhian-ai/Flight-Booking-System.git
   ```

2. **Open in VS Code or any C++ IDE**

3. **Build and Run**
   - Make sure `airplane.cpp` and all `.csv` files are in the same directory.
   - Compile the program using a C++ compiler:
     ```bash
     g++ airplane.cpp -o flight_booking
     ./flight_booking
     ```

4. **Interact via Console**
   - Follow the on-screen prompts to search and book flights.

## 📂 File Descriptions

- `airplane.cpp` - Main program logic
- `availableflights.csv` - Stores flight schedule and details
- `flightprices.csv` - Stores pricing information
- `passengerflights.csv` - Logs passenger bookings
- `users.csv` - User credentials or data (if applicable)

## 📄 License

This project is open-source and free to use under the MIT License.

---

Developed with 💻 and ✈️ by Kristhian-ai
