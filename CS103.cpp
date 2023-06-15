// Zach Lovett & James McGregor CS103 Project
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct User {
	string username;
	string password;
	string type; // "admin" or "user"
};


void loginuser(); //Define Functions
void adminmenu();
void usermenu(string username);
void createuser();
void exitprogram();
void drawMenu();
int main();
// Menu Details
int steakcheesepie = 5.0;
int hotchips = 10.0;
int pizza = 12.50;
int sushi = 15.0;
int sausageroll = 5.0;
int brownie = 7.50;
int sandwich = 5.0;
int bagel = 5.0;
int donut = 7.0;
// Payment

// Discounts

// Billing



void createuser() { // Create User
	system("cls"); // clear screen

	User newuser;
	cout << "Enter Username: ";
	cin >> newuser.username;
	cout << "Enter Password ";
	cin >> newuser.password;
	newuser.type = "user";

	ofstream usersfile("Accounts.txt", ios::app);
	usersfile << newuser.username << " " << newuser.password << " " << newuser.type << endl;
	usersfile.close();

	cout << "Account creation Successful!" << endl;

	main();

}




// Menu Logo
void drawMenu() {
	std::cout << "   ********           ********   *****************   *******       *****   *****    ***** \n";
	std::cout << "   *   *   *         *   *   *   *               *   *      *      *   *   *   *    *   * \n";
	std::cout << "   *   **   *       *   **   *   *   *************   *       *     *   *   *   *    *   * \n";
	std::cout << "   *   * *   *     *   * *   *   *   *               *   **   *    *   *   *   *    *   * \n";
	std::cout << "   *   *  *   *   *   *  *   *   *   *************   *   * *   *   *   *   *   *    *   * \n";
	std::cout << "   *   *   *   * *   *   *   *   *   *           *   *   *  *   *  *   *   *   *    *   * \n";
	std::cout << "   *   *    *   *   *    *   *   *   *************   *   *   *   * *   *   *   *    *   * \n";
	std::cout << "   *   *     *     *     *   *   *   *               *   *    *   **   *   *   ******   * \n";
	std::cout << "   *   *      *   *      *   *   *   *************   *   *     *       *   *            * \n";
	std::cout << "   *   *       * *       *   *   *               *   *   *      *      *   *            * \n";
	std::cout << "   *****        *        *****   *****************   *****       *******   ************** \n";
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
		cout << "1. Logout" << endl;
		cout << "2. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			main();
			break;
		case 2:
			exitprogram();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 2);
}

void usermenu(string username)  // User menu
{
	system("cls"); // clear screen
	int choice;
	do {
		drawMenu();
		cout << "School Luch Menu" << endl;
		cout << "1. Logout" << endl;
		cout << "2. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			main();
			break;
		case 2:
			exitprogram();
			break;
		default:
			cout << "Invalid choice." << endl;
			break;
		}
	} while (choice != 2);
	
}





int main()
{
	system("cls"); // clear screen
	int choice;
	cout << "Welcome to the School Lunch Ordering System!" << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice == 1) {
		createuser();
	}
	else if (choice == 2) {
		loginuser();
	}
	else if (choice == 3) {
		exitprogram();
	}
	return 0;
}