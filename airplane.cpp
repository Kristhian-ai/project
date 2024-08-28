#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip> // Include the necessary header for setw
#include <stack>
#include <windows.h>
#include <thread>
#include <cstdlib>
#include <chrono>


using namespace std;

struct Node {
    vector<string> row;
    Node* next;

    Node(const vector<string>& rowData) : row(rowData), next(nullptr) {}
};

stack<string> passengerStack;
vector<vector<string>> readCSV(const string& filename);
void display_flights(const string& filename);
void display_seats(const string& filename, const string& destination);
void passenger_info(const string& name, const string& flight_num, const string& seat, const string& cost, const int& idx);
int get_prices(string filename, string destination);
string find_cost(const string& selected_seat, const vector<vector<string>>& content, string destination);
string ask_name();
int find_flight_index(string filename, string destination);
void book_seat(const string& filename, const string& destination);
void print_receipt();
void checkFlights();
void Abt();
int choice;
void menu(string part);
void press_enter();
void printing();
void promo();
void signIn();
void signUp();
void logOut();
void delete_row(const string& filename, int row_index);
int name_indx(string filename, string name);
vector<string> seat_indx(string filename, string name);
void revert_seat(const string& filename, string name, int flight_idx, string seats, string flightnum);
int ask_promo(string destination);
int cancel_find_flight_index(string filename, string destination);


bool run_promo = false;

struct User {
    string username;
    string password;
};

User users[10];
int userCount = 0;

bool sign_in_flag = true;

bool flag = true;


int main()
{
    while (sign_in_flag)
    {
        menu("signin");
    }

    while (flag)
    {
        menu("not signin");
    }
    return 0;
}

void clearscreen()
{
    system("cls");
}

vector<vector<string>> readCSV(const string& filename)
{
    vector<vector<string>> data;
    ifstream inputFile(filename);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            vector<string> row;
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            data.push_back(row);
        }

        inputFile.close();
    }
    else
    {
        cout << "Unable to open file: " << filename << endl;
    }

    return data;
}

void display_flights(const string& filename)
{
    vector<vector<string>> content = readCSV(filename);

    const int columnWidth = 25;

    for (const auto& row : content)
    {
        if (row.size() >= 3)
        {
            cout << left << setw(columnWidth) << row[0];
            cout << left << setw(columnWidth) << row[1];
            cout << left << setw(columnWidth) << row[2] << endl;
        }
    }
}

void display_seats(const string& filename, const string& destination)
{
    vector<vector<string>> content = readCSV(filename);

    int idx = -1;
    for (int i = 0; i < content.size(); i++)
    {
        if (content[i][1].find(destination) != string::npos)
        {
            idx = i;
            break;
        }
    }

    if (idx != -1)
    {
        string& flight_number = content[idx][0];
        string& location = content[idx][1];
        string& available_seats = content[idx][2];

        // Print flight number and destination
        cout << "Flight Seat Assignment\n\n";
        cout << "Flight number: " << flight_number << endl;
        cout << "Destination: " << location << endl;

        for (size_t i = 3; i < content.size(); ++i)
        {
            if (i >= content.size())
            {
                break;
            }
            else if (i % 4 == 3)
            {
                cout << "   " << content[idx][i] << content[idx][i + 1] << "  ";
            }
            else if (i % 4 == 1)
            {
                cout << content[idx][i] << content[idx][i + 1] << "  ";
            }
            if (i % 16 == 14)
            {
                cout << endl;
            }
        }
        cout << "\n";

        size_t start_index = 35;
        size_t num_rows = (content[idx].size() - start_index + 2) / 9;

        // Print the seats in the desired format
        for (size_t i = 0; i < num_rows; ++i)
        {
            for (size_t j = start_index + i * 9; j < (start_index + i * 9) + 9 && j < content[idx].size(); ++j)
            {
                cout << content[idx][j];
                if ((j - start_index + 1) % 3 == 0)
                {
                    cout << "   ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Destination not found." << endl;
    }
}

void passenger_info(const string& name, const string& flight_num, const string& seat, const string& cost, const int& idx)
{
    // Store passenger information in the stack
    ofstream file("passengerflights.csv", ios::app);
    if (file.is_open())
    {
        file << name << "," << flight_num << "," << seat << "," << cost << "," << idx << "\n";
        cout << "Passenger information saved successfully." << endl;
        file.close();
    }
    else
    {
        cout << "Error opening the file for writing." << endl;
    }

    string passengerData = name + "," + flight_num + "," + seat + "," + cost;
    passengerStack.push(passengerData);
    cout << "Passenger information saved successfully." << endl;
}

Node* linkedlist_readCSV(const string& filename) {
    Node* head = nullptr;
    ifstream inputFile(filename);
    string line;

    if (inputFile.is_open()) {
        Node* current = nullptr;
        while (getline(inputFile, line)) {
            vector<string> rowData;
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, ',')) {
                rowData.push_back(cell);
            }

            Node* newNode = new Node(rowData);
            if (head == nullptr) {
                head = newNode;
                current = head;
            } else {
                current->next = newNode;
                current = newNode;
            }
        }

        inputFile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }

    return head;
}

void deleteLinkedList(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int get_prices(string filename, string destination)
{
    string price;
    Node* head = linkedlist_readCSV(filename);

    Node* current = head;
    while (current != nullptr)
    {
        if (current->row[0].find(destination) != string::npos)
        {
            price = current->row[1];
            break;
        }
        current = current->next;
    }

    deleteLinkedList(head); // Assuming you have a function to delete the linked list and free memory

    int price_num;
    price_num = stoi(price);
    return price_num;
}

string find_cost(const string& selected_seat, const vector<vector<string>>& content, string destination)
{
    char arr[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    char arr2[8] = {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
    const string FILENAME = "flightprices.csv";
    int price;
    string price_str;
    for (int i = 0; i < 8; i++)
    {
        if (selected_seat.find(arr[i]) != string::npos)
        {
            price = get_prices(FILENAME, destination);
            int luxury_cost = price + (price * 0.4);
            price_str = to_string(luxury_cost);
            return price_str;
        }
        else if (selected_seat.find(arr2[i]) != string::npos)
        {
            price = get_prices(FILENAME, destination);
            price_str = to_string(price);
            return price_str;
        }
    }
    return "";
}

string ask_name()
{
    string name;
    cout << "Input the name of the ticket holder: ";
    cin >> name;
    return name;
}

int find_flight_index(string filename, string destination)
{
    vector<vector<string>> content = readCSV(filename);
    int idx;
    for (int i = 1; i < content.size(); i++)
    {
        if (content[i][1].find(destination) != string::npos)
        {
            idx = stoi(content[i + 1][0]);
            return idx;
        }
    }
    cout<<"problem here";
    press_enter();
    return -1;
}

void book_seat(const string& filename, const string& destination)
{
    vector<vector<string>> content = readCSV(filename);

    int flight_index = find_flight_index(filename, destination);
    //TODO: change flight num to integer
    int flightnum[16];
    for (int i = 1; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            if (j == 0)
            {
                flightnum[i - 1] = stoi(content[i][0]);
            }
        }
    }

    //TODO: Implement binary search
    int idx = -1;
    int left = 0;
    int right = content.size() - 1;
    int counter = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (flightnum[mid] == flight_index)
        {
            idx = mid;
            break;
        }
        else if (flightnum[mid] < flight_index)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
        counter++;
    }
    
    string selectedSeat, name, flightNum, cost;
    int seat_index = -1, choice;


    if (idx != -1)
    {
        clearscreen();
        display_seats(filename, destination);

        cout << "Select Desired Seat: ";
        cin >> selectedSeat;

        //TODO: Confirmation error case
        for (int i = 3; i < content[idx].size(); i++)
        {
            if (selectedSeat == content[idx][i] && content[idx][i] != "X ")
            {
                seat_index = i;
                int seatsNum = stoi(content[idx][2]) - 1;
                content[idx][2] = to_string(seatsNum);
                content[idx][i] = "X ";
                break;
            }
        }

        if (seat_index != -1)
        {
            name = ask_name();

            flightNum = content[idx][0];
            cost = find_cost(selectedSeat, content, destination);

            int price = 0;

                if (run_promo == false)
                {
                    clearscreen();
                    cout << "==Confirmation of Booking==\n";
                    cout << "Name: " << name << endl;
                    cout << "Flight Number: " << flightNum << endl;
                    cout << "Destination: " << destination << endl;
                    cout << "Selected Seat: " << selectedSeat << endl;
                    cout << "Ticket Cost: " << cost << endl;
                    cout << "===========================\n";
                    cout << "\nAre the information correct?\n1-True\n2-False\n\nEnter Choice: ";

                    cin >> choice;
                    passenger_info(name, flightNum, selectedSeat, cost, seat_index);
                }
                else if (run_promo == true)
                {
                    price = ask_promo(destination);
                    int cost_int = stoi(cost);
                    float computation = (1 - (price / 100.0)) * (cost_int); // Use floating-point arithmetic
                    int computation_int = static_cast<int>(computation);
                    string computation_str = to_string(computation_int);
                    clearscreen();

                    cout << "==Confirmation of Booking==\n";
                    cout << "Name: " << name << endl;
                    cout << "Flight Number: " << flightNum << endl;
                    cout << "Destination: " << destination << endl;
                    cout << "Selected Seat: " << selectedSeat << endl;
                    cout << "Ticket Cost: " << computation_str << endl;
                    cout << "===========================\n";
                    cout << "\nAre the information correct?\n1-True\n2-False\n\nEnter Choice: ";

                    cin >> choice;

                    passenger_info(name, flightNum, selectedSeat, computation_str, seat_index);
                }
                else
                {
                    cout<<"Invalid run promo";
                    press_enter();
                }
                ofstream outputFile(filename);
                if (outputFile.is_open())
                {
                    for (const auto& row : content)
                    {
                        for (size_t i = 0; i < row.size(); i++)
                        {
                            outputFile << row[i];
                            if (i != row.size() - 1)
                            {
                                outputFile << ",";
                            }
                        }
                        outputFile << endl;
                    }

                    outputFile.close();
                    clearscreen();
                    printing();
                    print_receipt();
                    press_enter();
                    cout << "File modified successfully." << endl;
                }
                else
                {
                    cout << "Could not open the file for writing." << endl;
                    menu("part2");
                }
        }
        else
        {
            cout << "Invalid seat selection." << endl;
        }
    }
    else
    {
        cout << "Destination not found." << endl;
    }
}

void press_enter()
{
    cout << "\nKINDLY PRESS ENTER TO CONTINUE...";
    cin.ignore();
    cin.get();
}

void print_receipt()
{
    if (passengerStack.empty())
    {
        cout << "No passenger information available." << endl;
        return;
    }

    while (!passengerStack.empty())
    {
        string passengerData = passengerStack.top();
        passengerStack.pop();

        stringstream ss(passengerData);
        string item;
        vector<string> passengerInfo;

        while (getline(ss, item, ','))
        {
            passengerInfo.push_back(item);
        }

        if (passengerInfo.size() == 4)
        {
            string name = passengerInfo[0];
            string flightNum = passengerInfo[1];
            string seat = passengerInfo[2];
            string cost = passengerInfo[3];

            cout << "\n======= Receipt =======\n";
            cout << "Name: " << name << endl;
            cout << "Flight Number: " << flightNum << endl;
            cout << "Seat: " << seat << endl;
            cout << "Cost: " << cost << endl;
            cout << "=======================\n";
        }
    }
}

void Abt(){
system("cls");
cout<<"  _|_|        _|_|_|          _|_|        _|    _|      _|_|_|_|_|  "<<endl;
cout<<"_|    _|      _|    _|      _|    _|      _|    _|          _|      "<<endl;
cout<<"_|_|_|_|      _|_|_|        _|    _|      _|    _|          _|      "<<endl;
cout<<"_|    _|      _|    _|      _|    _|      _|    _|          _|      "<<endl;
cout<<"_|    _|      _|_|_|          _|_|          _|_|            _|      "<<endl;                                
cout<<endl;
cout<<endl;                                
cout<<"+-------------------------------------------------------------------------------+"<<endl;
cout<<"| Introducing the high-flying C++ Flight Booking System! Buckle up and prepare  |"<<endl;
cout<<"| for an exciting journey through the world of aviation. With a smooth sign-in  |"<<endl;
cout<<"| and sign-up function, you'll have access to a sky full of possibilities. Book |"<<endl;
cout<<"| your dream destination effortlessly and cancel with ease if plans change. But |"<<endl;
cout<<"| wait, there's more! Our promo menu will sweep you off your feet with exclusive|"<<endl;
cout<<"| deals and discounts, making your travel experience even more unforgettable.   |"<<endl;
cout<<"| Soar through the code and enjoy the seamless interface as you navigate your   |"<<endl;
cout<<"| way to the perfect flight. Whether you're a jetsetter or a casual traveler,   |"<<endl;
cout<<"| this system will keep you flying high and craving more adventures. Bon voyage!|"<<endl;
cout<<"+-------------------------------------------------------------------------------+"<<endl;
cout<<endl;
cout<<endl;
cout<<"Project of:"<<endl;
cout<<"Marc Linus Rosales"<<endl;
cout<<"Kristhian Pinili"<<endl;
cout<<"Gerard Andrei Malapote"<<endl;
cout<<endl;
cout<<"This project is done in partial fulfillment of the final exams in Data Structures and Algorithms."<<endl;
cout<<endl;

    press_enter();
    clearscreen();        
}

void promo()
{
    clearscreen();
    string filename = "Promos.csv";
    vector<vector<string>> content = readCSV(filename);
    cout<<"=============Available Promos at Blank Airline=============\n";
    display_flights(filename);
    cout<<"===========================================================\n";
}

void menu(string part){
    clearscreen();
    int flightindex = 0;
    int rowToDelete = 0;
    if (part == "signin")
    {
        cout << "====== Main Menu ======\n";
        cout << "1. Sign In\n";
        cout << "2. Sign Up\n";
        cout << "3. Log Out\n";
        cout << "4. Exit\n";
        cout<<  "=======================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        clearscreen();

        switch (choice) {
            case 1:
                signIn();
                break;
            case 2:
                signUp();
                break;
            case 3:
                logOut();
                break;
            case 4:
                cout << "Exiting the program, HAVE A SAFE TRIP!\n";
                flag = false;
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    }
    else
    {
	cout<<"==========Main Menu==========";
	cout<<endl;
	cout<<"1. Check Available FLights"<<endl;
	cout<<"2. Book a Flight"<<endl;
	cout<<"3. Cancel Flight"<<endl;
	cout<<"4. Check for Flight Promos"<<endl;
	cout<<"5. About"<<endl;
	cout<<"6. Exit"<<endl;
    cout<<"=============================";
	cout<<endl;
	cout<<"\nEnter Choice: "<<endl;
    int choice, price;
	cin>>choice;
	string destination, filename, name;
    vector<string> seat;
    vector<vector<string>> content;


	switch (choice){
		case 1:
            clearscreen();
            cout<<"=================Available Flights at Blank Airlines=================\n";
            display_flights("availableflights.csv");
            cout<<"=====================================================================\n";
            press_enter();
			break;
		case 2:
            run_promo = false;
            clearscreen();
            cout<<"=================Available Flights at Blank Airlines=================\n";
            display_flights("availableflights.csv");
            cout<<"=====================================================================\n";
            cout << "\nEnter Desired Destination: ";
            cin >> destination;

            book_seat("availableflights.csv", destination);

			break;
		case 3:
            clearscreen();
            filename = "passengerflights.csv";
            cout<<"====Cancellation of Flight====\n\n";
            cout<<"Name to be deleted: ";
            cin>>name;
            rowToDelete = name_indx("passengerflights.csv", name); // Example: delete the 3rd row
            seat = seat_indx("passengerflights.csv", name);
            // flightindex = find_flight_index("availableflights.csv",seat[1]);
            flightindex = cancel_find_flight_index("availableflights.csv",seat[1]);

            if (rowToDelete == 0)
            {
                cout<<"index 0";
            }
            else
            {
                clearscreen();
                cout<<"====Cancellation of Flight====\n\n";

                cout <<"Cancel the flight of: "<<name;
                cout<<"\nSeat Number: "<<seat[0];
                cout<<"\nFlight Number: "<<seat[1];
                cout<<"\n\n==============================";
                cout<<"\n\nAre the information correct?\n1-True\n2-False\n\nEnter Choice: ";
                int choice;
                cin>>choice;
                if (choice == 1)
                {
                    revert_seat("availableflights.csv", name, flightindex, seat[0], seat[1]);
                    delete_row("passengerflights.csv", name_indx("passengerflights.csv", name));
                    press_enter();
                }
                else
                {   
                    clearscreen();
                    cout<<"Return to Main Menu\n";
                    press_enter();
                }
            }
			break;
		case 4:
            run_promo = true;
            promo();
            content = readCSV("Promos.csv");
            cout<<"\nSelect Promo Destination: ";
            cin>>destination;
            press_enter();

            book_seat("availableflights.csv", destination);

			break;
		case 5:
			Abt();
			break;
		case 6:
            clearscreen();
            flag = false;
            cout<<"Thank you for using _____ airline";
			break;
		default:
			cout<<"Invalid prompt.";
            press_enter();
    }
	}
}

int cancel_find_flight_index(string filename, string destination)
{
    vector<vector<string>> content = readCSV(filename);
    int idx;
    for (int i = 1; i < content.size(); i++)
    {
        if (content[i][0].find(destination) != string::npos)
        {
            // idx = stoi(content[i][0]);
            idx = i;
            return idx;
        }
    }
    return -1;
}

int ask_promo(string destination)
{
    vector<vector<string>> content = readCSV("Promos.csv");
    string price;
    int price_int;
    for (int i = 1; i<content.size(); i++)
    {
        if (content[i][1].find(destination)!=string::npos)
        {
            price = content[i][0].substr(0,2);
        }
    }
    price_int = stoi(price);
    return price_int;
    // find_cost(const string& selected_seat, const vector<vector<string>>& content, string destination)

}

void printing() {
    // Set ASCII to print special character.
    // Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    // 177 and 219 are from ASCII table
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\t\tLoading...";
    cout << "\n\t\t\t\t";

    for (int i = 0; i < 25; i++)
        cout << (char)bar1;

    // Recursive, so it would cover the bar1
    cout << "\r";
    cout << "\t\t";
    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        // Sleep is for delay
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    cout << "\n\t\t\t\t";
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

void signIn() {
    string username, password;
    cout << "Sign In\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool found = false;

    ifstream file("users.csv");
    if (file) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string storedUsername = line.substr(0, pos);
                string storedPassword = line.substr(pos + 1);
                if (storedUsername == username && storedPassword == password) {
                    found = true;
                    break;
                }
            }
        }
        file.close();
    } else {
        cout << "Error: Failed to open the user data file.\n";
    }

    clearscreen();

    if (found) {
        cout << "Sign in successful! Welcome to BLANK Airlines\n";
        sign_in_flag = false;
        press_enter();

    } else {
        cout << "Invalid username or password. Please try again.\n";
        press_enter();
    }
}

void signUp() {
    if (userCount == 10) {
        cout << "Cannot create more users. Maximum user limit reached.\n";
        return;
    }

    string username, password;
    cout << "Sign Up\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;

    // Open the CSV file in append mode and write the user data
    ofstream file("users.csv", ios::app);
    if (file) {
        file << username << "," << password << "\n";
        file.close();
        cout << "Sign up successful!\n";
    } else {
        cout << "Error: Failed to open the user data file.\n";
    }

    clearscreen();
}

void logOut() {
    clearscreen();
    cout << "Logged out successfully!\n";
}

void delete_row(const string& filename, int row_index) {
    // Read the CSV file into memory
    vector<vector<string>> data = readCSV(filename);

    // Check if row_index is valid
    if (row_index < 1 || row_index >= data.size()) {
        cout << "Invalid row index." << endl;
        return;
    }

    // Remove the row at row_index
    data.erase(data.begin() + row_index);

    // Overwrite the file with updated content
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); i++) {
                outputFile << row[i];
                if (i != row.size() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << endl;
        }
        outputFile.close();
        // cout << "Row deleted successfully." << endl;

    } else {
        cout << "Could not open the file for writing." << endl;
    }
}

int name_indx(string filename, string name)
{
    vector<vector<string>> content = readCSV(filename);

    for (int i = 1; i < content.size(); i++) {
            if (content[i][0].find(name) != string::npos) {
                return i;
            }
    }
    cout<<"Name not found, ngek";
    return -1;
}

vector<string> seat_indx(string filename, string name)
{
    vector<vector<string>> content = readCSV(filename);
    int idx_name = name_indx("passengerflights.csv", name);
    vector<string> data;

    data.push_back(content[idx_name][2]); //seat
    data.push_back(content[idx_name][1]);//flight num
    data.push_back(content[idx_name][4]); //seat index
    return data;

}

void revert_seat(const string& filename, string name, int flight_idx, string seats, string flightnum) {
    vector<vector<string>> content = readCSV(filename);
    vector<string> s_idx = seat_indx("passengerflights.csv", name);
    
    int seat = stoi(s_idx[2]);
    for (int i = 1; i < content.size(); i++) {
        if (flight_idx == i) {  // flight_idx returns an index but it is compard to the flightnum
            content[flight_idx][seat] = s_idx[0];  // Assign the original seat value back
            // clearscreen();
            // cout<<"====Cancellation of Flight====\n\n";

            // cout <<"Cancel the flight of: "<<name;
            // cout<<"\nSeat Number: "<<seats;
            // cout<<"\nFlight Number: "<<flightnum;
            // cout<<"\n\n==============================";
            // cout<<"\n\nAre the information correct?\n1-True\n2-False\n\nEnter Choice: ";
            // int choice;
            // cin>>choice;
            // if (choice == 1)
            // {
            //     continue;
            // }
            // else
            // {
            //     return;
            // }
        }
    }

    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& row : content) {
            for (size_t i = 0; i < row.size(); i++) {
                outputFile << row[i];
                if (i != row.size() - 1) {
                    outputFile << ",";
                }
            }
            outputFile << endl;
        }
        outputFile.close();
        clearscreen();
        cout<<"========Cancellation of Flight========\n\n";
        cout<<"Successfully Canceled the flight of: "<<name;
        cout<<"\n\n======================================\n";

    } else {
        cout << "Could not open the file for writing." << endl;
    }
}

