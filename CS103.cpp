#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


// Structure to store user information.
struct User { 
	string username;
	string password;
	string type; // "admin" or "user"
};

// Define Functions
void loginuser();
void adminmenu(string username);
void viewaccounts();
void Adminvieworder(string username);
void vieworder(string username);
void usermenu(string username);
void orderMenu(string username);
void createuser();
void exitprogram();
void drawMenu();
int main();
void saveOrderToFile(const string& username, const vector<string>& order, double total);
void checkout();
void cash();
void card();
void Deleteorder(const string& username);
void DeleteorderAdmin();

// Menu Prices
double pie = 5.0;
double chips = 10.0;
double pizza = 12.50;
double sushi = 15.0;
double brownie = 7.50;
double sandwich = 5.0;
double bagel = 5.0;
double donut = 7.0;

// Save Order to Text File
void saveOrderToFile(const string& username, const vector<string>& order, double total) {
	static int orderNumber = 1;
	map<string, double> menuItems = {
		{"Pie", 5.00},
		{"Chips", 10.00},
		{"Pizza", 12.50},
		{"Sushi", 15.00},
		{"Brownie", 7.50},
		{"Sandwich", 5.00},
		{"Bagel", 5.00},
		{"Donut", 7.00}
	};

	string fileName = username + ".txt"; // Creates file name for users order.
	ofstream outputFile(fileName, ios::app);
	ofstream adminFile("adminorder.txt", ios::app);
	if (outputFile.is_open() && adminFile.is_open()) {
		outputFile << "Order Number: " << orderNumber << "\n";
		outputFile << "Username: " << username << "\n";
		outputFile << "Order Summary: \n";
		adminFile << "Order Number: " << orderNumber << "\n";
		adminFile << "Username: " << username << "\n";
		adminFile << "Order Summary: \n";
		for (const auto& item : order) {
			outputFile << item << " - $" << menuItems[item] << "\n";
			adminFile << item << " - $" << menuItems[item] << "\n";
		}
		outputFile << "Total: $" << total << "\n";
		adminFile << "Total: $" << total << "\n";
		outputFile << "----------------------------------\n";
		adminFile << "----------------------------------\n";
		outputFile.close();
		adminFile.close();
	}
	orderNumber++;
}




// Function to delete an order from a user by specifying the order number and username.
void Deleteorder(const string& username) {
	string fileName = username + ".txt";
	vector<string> lines;
	ifstream userFile(fileName);
	string line;
	int orderNumberToDelete;
	cout << "Enter the order number of the order you want to delete: ";
	cin >> orderNumberToDelete;
	bool found = false;
	while (getline(userFile, line)) {
		if (line.find("Order Number: " + to_string(orderNumberToDelete)) != string::npos) {
			found = true;
			while (getline(userFile, line) && !line.empty()) {
				// skip lines until the next order
			}
		}
		else {
			lines.push_back(line);
		}
	}
	userFile.close();

	if (found) {
		ofstream userFileOut(fileName);
		for (const auto& line : lines) {
			userFileOut << line << "\n";
		}
		userFileOut.close();
		cout << "Order deleted successfully." << endl;
	}
	else {
		cout << "No orders found." << endl;
	}
}

// Function to delete order from the admins file by specifying the order number  and username.
void DeleteorderAdmin() {
	vector<string> lines;
	ifstream adminFile("adminorder.txt");
	string line;
	int orderNumberToDelete;
	cout << "Enter the order number of the order you want to delete: ";
	cin >> orderNumberToDelete;
	bool found = false;
	while (getline(adminFile, line)) {
		if (line.find("Order Number: " + to_string(orderNumberToDelete)) != string::npos) {
			found = true;
			while (getline(adminFile, line) && !line.empty()) {
				// skip lines until the next order
			}
		}
		else {
			lines.push_back(line);
		}
	}
	adminFile.close();

	if (found) {
		ofstream adminFileOut("adminorder.txt");
		for (const auto& line : lines) {
			adminFileOut << line << "\n";
		}
		adminFileOut.close();
		cout << "Order deleted successfully." << endl;
	}
	else {
		cout << "No order found with the specified order number." << endl;
	}
}


// Function to allow the admin to view all orders.
void Adminvieworder(string username) {
	int choice;
	do {

		system("clear"); // Clears the screen.
		ifstream inputFile("adminorder.txt");
		string line;
		bool found = false;
		while (getline(inputFile, line)) {
			found = true;
			cout << line << endl;
			while (getline(inputFile, line) && !line.empty()) {
				cout << line << endl;
			}
		}
		inputFile.close();
		if (!found) {
			cout << "No orders have been placed." << endl;
		}
		cout << "\n1. Delete Order" << endl;
		cout << "2. Back to Menu" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			DeleteorderAdmin();
			break;
		case 2:
			adminmenu(username);
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 2);
}

// Function to allow a user to view their order history.
void vieworder(string username) {
	int choice;
	do {

		system("clear"); // Clear screen.
		string fileName = username + ".txt";
		ifstream inputFile(fileName);
		string line;
		bool found = false;
		while (getline(inputFile, line)) {
			found = true;
			cout << line << endl;
			while (getline(inputFile, line) && !line.empty()) {
				cout << line << endl;
			}
			break;
		}
		inputFile.close();
		if (!found) {
			cout << "Account has no orders placed." << endl;
		}
		cout << "\n1. Delete Order" << endl;
		cout << "2. Back to Menu" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			Deleteorder(username);
			break;
		case 2:
			usermenu(username);
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 2);
}



// Function to display the order menu and allows a user to place a order.
void orderMenu(string username) {

	system("clear"); // Clear Screen
	drawMenu(); // Draws MENU Logo
	map<string, double> menuItems = { // Name and price for all products
		{"Pie", 5.00},
		{"Chips", 10.00},
		{"Pizza", 12.50},
		{"Sushi", 15.00},
		{"Brownie", 7.50},
		{"Sandwich", 5.00},
		{"Bagel", 5.00},
		{"Donut", 7.00}
	};

	vector<string> order;
	double total = 0.00;

	char choice;
	do {
		cout << "\nOur Menu:\n";
		for (const auto& item : menuItems) {
			cout << item.first << " - $" << item.second << "\n";
		}

		// Item Ordering
		string itemChoice;
		cout << "Enter the item you wish to order or type 'Exit' to exit: ";
		cin >> itemChoice;

		if (itemChoice == "Exit" || itemChoice == "exit") { // Exit to Menu
			main();
		}
		else if (menuItems.find(itemChoice) != menuItems.end()) {
			order.push_back(itemChoice);
			total += menuItems[itemChoice];

			// Option to Order More Food
			char continueChoice;
			cout << "Do you want to order more food? (Y/N): ";
			cin >> continueChoice;

			if (continueChoice == 'N' || continueChoice == 'n') {
				break;
			}
		}
		else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	// Shopping Cart
	while (true);
	User currentuser;
	cout << "\nShopping Cart:\n";
	if (order.empty()) {
		cout << "No items ordered.\n";
	}
	else {
		for (const auto& item : order) {
			cout << item << " - $" << menuItems[item] << "\n";
		}
		total = total * 1.15;
		cout << "\nTotal: $" << total << " inc GST";


		// Discounts
		int discountChoice;
		string discount;
		cout << "\n\nDo you have any discount codes?";
		cout << "\n1. Enter Discount Code";
		cout << "\n2. Continue To Checkout";
		cout << "\nEnter your choice: ";
		cin >> discountChoice;

		switch (discountChoice) {
		case 1:
			cout << "\nEnter Discount Code: ";
			cin >> discount;
			if (discount == "xXZ9D6" || discount == "ncpFNs" || discount == "2925Ye" || discount == "9VqAna" || discount == "y82Fxh") {
				cout << "\nCode Approved!";
				total -= total * 0.20;
				cout << "\nYour Total Is $" << total << " inc GST\n\n";
				saveOrderToFile(username, order, total);
				checkout();
				break;

			}
		case 2:
			saveOrderToFile(username, order, total);
			checkout();
			break;
		}
	}
}


// Checkout allows user to their payment method.
void checkout() {

	system("clear"); // Clear screen.
	int choice;
	cout << "Choose your payment method";
	cout << "\n1. Cash";
	cout << "\n2. Credit Card";
	cout << "\nEnter you choice: ";
	cin >> choice;

	switch (choice) {
	case 1:
		cash();
		break;
	case 2:
		card();
		break;
	}
}

// Create Account function.
void createuser() {

	system("clear"); // clear screen

	User newuser;
	cout << "Enter Username: ";
	cin >> newuser.username;
	cout << "Enter Password: ";
	cin >> newuser.password;
	cout << "Enter User Type (admin or user): ";
	cin >> newuser.type;

	ofstream usersfile("Accounts.txt", ios::app);
	usersfile << newuser.username << " " << newuser.password << " " << newuser.type << endl;
	usersfile.close();

	cout << "Account creation Successful!" << endl;

	main();
}

// Function to delete a account by specifying the username.
void deleteaccount(string username) {
	vector<User> users;
	User currentuser;
	ifstream usersfile("Accounts.txt");
	while (usersfile >> currentuser.username >> currentuser.password >> currentuser.type) {
		if (currentuser.username != username) {
			users.push_back(currentuser);
		}
	}
	usersfile.close();

	ofstream usersfileout("Accounts.txt");
	for (const auto& user : users) {
		usersfileout << user.username << " " << user.password << " " << user.type << endl;
	}
	usersfileout.close();
}

// View Accounts function.
void viewaccounts() {
	int choice;
	do {

		system("clear"); // Clear Screen
		cout << "All Accounts:\n";
		User currentuser;
		ifstream usersfile("Accounts.txt");
		while (usersfile >> currentuser.username >> currentuser.password >> currentuser.type) {
			cout << "Account Name: " << currentuser.username << ", Type: " << currentuser.type << endl;
		}
		usersfile.close();
		cout << "\n1. Delete Account" << endl;
		cout << "2. Return to Main Menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) {
			string username;
			cout << "Enter the username of the account to delete: ";
			cin >> username;
			deleteaccount(username);
			cout << "Account deleted successfully.\n";
		}
	} while (choice != 2);

	system("clear"); //Clear Screen
}

// Menu Logo
void drawMenu() {
	cout << "   ********           ********   *****************   *******       *****   *****    ***** \n";
	cout << "   *       *         *       *   *               *   *      *      *   *   *   *    *   * \n";
	cout << "   *   **   *       *   **   *   *   *************   *       *     *   *   *   *    *   * \n";
	cout << "   *   * *   *     *   * *   *   *   *               *   **   *    *   *   *   *    *   * \n";
	cout << "   *   *  *   *   *   *  *   *   *   *************   *   * *   *   *   *   *   *    *   * \n";
	cout << "   *   *   *   * *   *   *   *   *   *           *   *   *  *   *  *   *   *   *    *   * \n";
	cout << "   *   *    *   *   *    *   *   *   *************   *   *   *   * *   *   *   *    *   * \n";
	cout << "   *   *     *     *     *   *   *   *               *   *    *   **   *   *   ******   * \n";
	cout << "   *   *      *   *      *   *   *   *************   *   *     *       *   *            * \n";
	cout << "   *   *       * *       *   *   *               *   *   *      *      *   *            * \n";
	cout << "   *****        *        *****   *****************   *****       *******   ************** \n";
}

// Exit Program
void exitprogram() {
	cout << "Exiting program. Goodbye!" << endl;
	exit(0);
}

// Login
void loginuser() {   // Login User

	system("clear"); // clear screen
	string username, password;
	int attempts = 0; // Keeps track of attempted log ins.
	bool found = false;
	User currentuser;
	while (attempts < 3 && !found) { // Allows up to 3 login attempts.
		cout << "Enter Username: ";
		cin >> username;
		cout << "Enter Password: ";
		cin >> password;

		if (username.empty() || password.empty()) {
			cout << "Username and password cannot be nil." << endl;
			attempts++;
			continue;
		}

		ifstream usersfile("Accounts.txt");
		while (usersfile >> currentuser.username >> currentuser.password >> currentuser.type) {
			if (currentuser.username == username && currentuser.password == password) {
				found = true;
				break;
			}
		}
		usersfile.close();

		if (!found) {
			cout << "Invalid username or password. You have " << 2 - attempts << " attempts left." << endl;
			attempts++;
		}
	}


	if (found) {
		cout << "Login Successful!" << endl;
		if (currentuser.type == "admin") {
			adminmenu(username);
		}
		else {
			usermenu(username);
		}
	}
	else {
		cout << "Too Many failed login attempts. Please try again later." << endl;
	}

}


// Admin Menu
void adminmenu(string username)
{

	system("clear"); // clear screen
	int choice;
	do {
		drawMenu();
		cout << "Admin Menu:" << endl;
		cout << "1. Order" << endl;
		cout << "2. View Accounts" << endl;
		cout << "3. View Orders" << endl;
		cout << "4. Logout" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			orderMenu(username);
			break;
		case 2:
			viewaccounts();
			break;
		case 3:
			Adminvieworder(username);
		case 4:
			main();
			break;
		case 5:
			exitprogram();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 3);
}

// User Menu
void usermenu(string username)
{

	system("clear"); // clear screen
	int choice;
	do {
		drawMenu();
		cout << "\nSchool Luch Menu" << endl;
		cout << "1. Order Food" << endl;
		cout << "2. View Orders" << endl;
		cout << "3. Logout" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			orderMenu(username);
			break;
		case 2:
			vieworder(username);
			break;
		case 3:
			main();
			break;
		case 4:
			exitprogram();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 3);

}


// Cash Payment
void cash() {

	system("clear");

	string username;
	User currentuser;
	int insertChoice;
	cout << "Please insert your cash...";
	cout << "\n1. Insert Cash";
	cout << "\n2. Return to Payment Methods";
	cout << "\nEnter your choice: ";
	cin >> insertChoice;

	switch (insertChoice) {
	case 1:
		cout << "\nProcessing Payment...";
		cout << "\nPayment Accepted.";

		char choice;
		cout << "\n\nPress 'Y' to return to the Main Menu: ";
		cin >> choice;
		if (currentuser.type == "admin" && (choice == 'Y' || choice == 'y')) {
			adminmenu(username);
		}
		else if (currentuser.type == "user" && (choice == 'Y' || choice == 'y')) {
			usermenu(username);
		}
		break;
	case 2:
		checkout();
		break;
	}

	system("clear");
}

// Credit Card Payment
void card() {

	system("clear");

	// Declare variables
	User currentuser;
	string username;
	string cardNumber;
	string cardHolderName;
	int cvv;
	int expirationMonth;
	int expirationYear;

	// Payment Form
	cout << "     Payment\n";
	cout << "=================\n";

	// Gather CC information from user
	cout << "\nEnter Card Number: ";
	cin >> cardNumber;
	cout << "\nEnter Cardholder Name: ";
	cin >> cardHolderName;
	cout << "\nEnter CVV: ";
	cin >> cvv;
	cout << "\nEnter Expiration Month: ";
	cin >> expirationMonth;
	cout << "\nEnter Expiration Year: ";
	cin >> expirationYear;

	// Process Payment
	cout << "\n" << "Processing Payment...";
	cout << "\n\nCard Number: " << cardNumber;
	cout << "\nCardholder Name: " << cardHolderName;
	cout << "\nCVV: ***";
	cout << "\nExpiration Date: " << expirationMonth << "/" << expirationYear;
	cout << "\nPayment Successful!";

	char choice;
	cout << "\n\nPress 'Y' to return to the Main Menu: ";
	cin >> choice;

	switch (choice) {
	case 1:
		if (currentuser.type == "admin" && (choice == 'Y' || choice == 'y')) {
			adminmenu(username);
		}
		else if (currentuser.type == "user" && (choice == 'Y' || choice == 'y')) {
			usermenu(username);
		}
		break;
	case 2:
		cout << "Invalid choice. Please try again.";
		break;
	}

	system("clear");

}
// Billing

// Main
int main()
{

	system("clear");  // clear screen
	int choice;
	cout << "Welcome to the School Lunch Ordering System!" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice == 1) {
		loginuser();
	}
	else if (choice == 2) {
		createuser();
	}
	else if (choice == 3) {
		exitprogram();
	}
	return 0;
};