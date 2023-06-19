// Zach Lovett & James McGregor CS103 Project
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

// Login System

struct User {
	string username;
	string password;
	string type; // "admin" or "user"
};

// Define Functions
void loginuser();
void adminmenu();
void viewaccounts();
void usermenu(string username);
void orderMenu();
void createuser();
void exitprogram();
void drawMenu();
int main();
void saveOrderToFile();
void checkout();
void cash();
void card();

// Menu Prices
double pie = 5.0;
double chips = 10.0;
double pizza = 12.50;
double sushi = 15.0;
double brownie = 7.50;
double sandwich = 5.0;
double bagel = 5.0;
double donut = 7.0;


void saveOrderToFile(const vector<string>& order, double total) {
	ofstream outputFile("Orders.txt", ios::app);
	if (outputFile.is_open()) {
		outputFile << "Order Summary: \n";
		for (const auto& item : order) {
			outputFile <<item << "\n";
		}
		outputFile << "Total: $" << total << "\n";
		outputFile << "----------------------------------\n";
		outputFile.close();
	}
}


void orderMenu() {
	system("cls");
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
	double total = 0.0;

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
			break;
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
	string username;
	cout << "\nShopping Cart:\n";
	if (order.empty()) {
		cout << "No items ordered.\n";
	}
	else {
		for (const auto& item : order) {
			cout << item << " - $" << menuItems[item] << "\n";
		}
		cout << "\nTotal: $" << total;

		saveOrderToFile(order, total);

		// Discounts
		int discountChoice;
		string discount;
		cout << "\n\nDo you have any discount codes?";
		cout << "\n1. Enter Discount Code";
		cout << "\n2. Continue To Checkout";
		cout << "\nEnter your choice: ";
		cin >> discountChoice;

		switch(discountChoice) {
			case 1:
				cout << "\nEnter Discount Code: ";
				cin >> discount;
				if (discount == "xXZ9D6" || discount == "ncpFNs" || discount == "2925Ye" || discount == "9VqAna" || discount == "y82Fxh") {
					cout << "\nCode Approved!";
					total -= total * 0.20;
					cout << "\nYour Total Is $" << total << "\n\n";
					checkout();
					break;
					
				}
			case 2:
				checkout();
				break;
		}
	}
}


// Checkout
void checkout() {
	system("cls");
	system("clear");
	int option;
	cout << "Choose your payment method";
	cout << "\n1. Cash";
	cout << "\n2. Credit Card";
	cout << "\nEnter you choice: ";
	cin >> option;
	
	switch(option) {
		case 1:
			cash();
			break;
		case 2:
			card();
			break;
	}
}

// Create Account
void createuser() {
	system("cls");
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

// Delete Account
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

// View Accounts
void viewaccounts() {
	int choice;
	do {
		system("cls");
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
	system("cls");
	system("clear"); //Clear Screen
}



// Menu Logo
void drawMenu() {
	cout << "   ********           ********   *****************   *******       *****   *****    ***** \n";
	cout << "   *   *   *         *   *   *   *               *   *      *      *   *   *   *    *   * \n";
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


void exitprogram() { //Program Exit
	cout << "Exiting program. Goodbye!" << endl;
	exit(0);
}

// Login
void loginuser() {   // Login User
	system("cls");
	system("clear"); // clear screen
	string username, password;
	int attempts = 0;
	bool found = false;
	User currentuser; // Define currentuser variable in outer scope
	while (attempts < 3 && !found) {
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
			cout << "Invalid username or password." << endl;
			attempts++;
		}
	}


	if (found) {
		cout << "Login Successful!" << endl;
		if (currentuser.type == "admin") {
			adminmenu();
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
void adminmenu()
{
	system("cls");
	system("clear"); // clear screen
	int choice;
	do {
		drawMenu();
		cout << "Admin Menu:" << endl;
		cout << "1. Order" << endl;
		cout << "2. View Accounts" << endl;
		cout << "3. Logout" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			orderMenu();
			break;
		case 2:
			viewaccounts();
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

// User Menu
void usermenu(string username)
{
	system("cls");
	system("clear"); // clear screen
	int choice;
	do {
		drawMenu();
		cout << "\nSchool Luch Menu" << endl;
		cout << "1. Order Food" << endl;
		cout << "2. Logout" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			orderMenu();
		case 2:
			main();
			break;
		case 3:
			exitprogram();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 2);

}


// Payment

void cash() {
	system("cls");
	system("clear");

	string username;
	User currentuser;
	int choice;
	cout << "Please insert your cash...";
	cout << "\n1. Insert Cash";
	cout << "\n2. Return to Payment Methods";
	cout << "\nEnter your choice: ";
	cin >> choice;

	switch(choice) {
		case 1:
			cout << "\nProcessing Payment...";
			cout << "\nPayment Accepted.";

			int option;
			cout << "\n\nPress 'Y' to return to the Main Menu: ";
			cin >> option;
			if (currentuser.type == "admin" && option == 'Y' || option == 'y') {
				adminmenu();
			}
			else if (currentuser.type == "user" && option == 'Y' || option == 'y') {
				usermenu(username);
			}
			
		case 2:
			checkout();
	}
}

void card() {
	system("cls");
	system("clear");

	// Declare variables
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

	string menuReturn;
	while(true) {
		User currentuser;
		string username;
		cout << "\n\nType 'exit' to return to the menu: ";
		cin >> menuReturn;
		if (currentuser.type == "admin" && menuReturn == 'exit' || menuReturn == 'Exit') {
			adminmenu();
		}
		else if (currentuser.type == "user" && menuReturn == 'exit' || menuReturn == 'Exit') {
			usermenu(username);
		}
	}
}

// Billing

int main()
{
	system("cls");
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
}