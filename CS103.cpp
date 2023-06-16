// Zach Lovett & James McGregor CS103 Project
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
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

// Menu Prices
double pie = 5.0;
double hotchips = 10.0;
double pizza = 12.50;
double sushi = 15.0;
double sausageroll = 5.0;
double brownie = 7.50;
double sandwich = 5.0;
double bagel = 5.0;
double donut = 7.0;

void orderMenu() {
	system("cls"); // Clear Screen
	drawMenu(); // Draws MENU Logo
	map<string, double> menuItems = { // Name and price for all products
		{"Steak and Cheese Pie", 5.00},
		{"Hot Chips", 10.00},
		{"Pizza", 12.50},
		{"Sushi", 15.00},
		{"Sausage Roll", 5.00},
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
		cout << "Enter the item you wish to order or press 0 to exit: ";
		cin >> itemChoice;

		if (itemChoice == "0") { // Exit to Menu
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
	cout << "\nShopping Cart:\n";
	if (order.empty()) {
		cout << "No items ordered.\n";
	}
	else {
		for (const auto& item : order) {
			cout << item << " - $" << menuItems[item] << "\n";
		}
		cout << "Total: $" << total << "\n\n";
	}

}



void createuser() {
	system("cls"); // clear screen

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

void viewaccounts() {
	int choice;
	do {
		system("cls"); //Clear Screen
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
	system("cls"); //Clear Screen
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


void loginuser() {   // Login User

	system("cls"); // clear screen
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




void adminmenu()  // Admin Menu
{
	system("cls"); // clear screen
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

void usermenu(string username)  // User menu
{
	system("cls"); // clear screen
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

// Discounts

// Billing


int main()
{
	system("cls"); // clear screen
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