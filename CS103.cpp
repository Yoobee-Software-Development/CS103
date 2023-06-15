// Zach Lovett & James McGregor CS103 Project
#include <iostream>
#include <string>
#include <fstream>


// Login System

struct User {
	std::string username;
	std::string password;
	std::string type; // "admin" or "user"
};


void loginuser(); //Define Functions
void adminmenu();
void usermenu(std::string username);
void createuser();
void exitprogram();
void drawMenu();
int main();

void createuser() { // Create User
	system("cls"); // clear screen

	User newuser;
	std::cout << "Enter Username: ";
	std::cin >> newuser.username;
	std::cout << "Enter Password ";
	std::cin >> newuser.password;
	newuser.type = "user";

	std::ofstream usersfile("Accounts.txt", std::ios::app);
	usersfile << newuser.username << " " << newuser.password << " " << newuser.type << std::endl;
	usersfile.close();

	std::cout << "Account creation Successful!" << std::endl;

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
	std::cout << "Exiting program. Goodbye!" << std::endl;
	exit(0);
}


void loginuser() {   // Login User

	system("cls"); // clear screen
	std::string username, password;
	int attempts = 0;
	bool found = false;
	User currentuser; // Define currentuser variable in outer scope
	while (attempts < 3 && !found) {
		std::cout << "Enter Username: ";
		std::cin >> username;
		std::cout << "Enter Password: ";
		std::cin >> password;

		if (username.empty() || password.empty()) {
			std::cout << "Username and password cannot be nil." << std::endl;
			attempts++;
			continue;
		}

		std::ifstream usersfile("Accounts.txt");
		while (usersfile >> currentuser.username >> currentuser.password >> currentuser.type) {
			if (currentuser.username == username && currentuser.password == password) {
				found = true;
				break;
			}
		}
		usersfile.close();

		if (!found) {
			std::cout << "Invalid username or password." << std::endl;
			attempts++;
		}
	}


	if (found) {
		std::cout << "Login Successful!" << std::endl;
		if (currentuser.type == "admin") {
			adminmenu();
		}
		else {
			usermenu(username);
		}
	}
	else {
		std::cout << "Too Many failed login attempts. Please try again later." << std::endl;
	}

}




void adminmenu()  // Admin Menu
{
	system("cls"); // clear screen
	int choice;
	do {
		drawMenu();
		std::cout << "Admin Menu:" << std::endl;
		std::cout << "1. Logout" << std::endl;
		std::cout << "2. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			main();
			break;
		case 2:
			exitprogram();
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
			break;
		}
	} while (choice != 2);
}

void usermenu(std::string username)  // User menu
{
	system("cls"); // clear screen
	int choice;
	do {
		drawMenu();
		std::cout << "School Luch Menu" << std::endl;
		std::cout << "1. Logout" << std::endl;
		std::cout << "2. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			main();
			break;
		case 2:
			exitprogram();
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
			break;
		}
	} while (choice != 2);
	
}

// Menu Details
double steakcheesepie = 5.0;
double hotchips = 10.0;
double pizza = 12.50;
double sushi = 15.0;
double sausageroll = 5.0;
double brownie = 7.50;
double sandwich = 5.0;
double bagel = 5.0;
double donut = 7.0;
// Payment

// Discounts

// Billing


int main()
{
	system("cls"); // clear screen
	int choice;
	std::cout << "Welcome to the School Lunch Ordering System!" << std::endl;
	std::cout << "1. Register" << std::endl;
	std::cout << "2. Login" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cout << "Enter your choice: ";
	std::cin >> choice;

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