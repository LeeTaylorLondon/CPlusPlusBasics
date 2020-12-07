#include <iostream>
#include <string>


// Store user information
const int maxAccounts = 3;
std::string usernames[maxAccounts] = {"null", "null", "null"};
std::string passwords[maxAccounts] = {"null", "null", "null"};
int logInID = -1;

// Init. vars for cin
std::string username_inp;
std::string password_inp;
bool loggedIn = false;

// Commands [Account page]
std::string c1 = "cu";
std::string c2 = "cp";
std::string c3 = "logout";
std::string c4 = "ainfo";
std::string ce = "exit";
std::string c7 = "d32";
// [Home Page]
std::string c5 = "register";
std::string c6 = "login";
std::string c8 = "dinfo"; // debug-info

// Command descriptions
std::string c1Desc = " - Change username";
std::string c2Desc = " - Change password";
std::string c3Desc = " - Log out";
std::string c4Desc = " - View account info";
std::string ceDesc = " - Shuts program down";
std::string c7Desc = " - Delete system32";

std::string c5Desc = " - Register an account";
std::string c6Desc = " - Log into an existing account";
std::string c8Desc = " - View all account information";


// Arrays for storing commands
const int loggedInCommands = 12;
std::string commands[loggedInCommands] = {c1, c1Desc, c2, c2Desc,
										  c3, c3Desc, c4, c4Desc,
										  ce, ceDesc, c7, c7Desc};
const int homePageCommands = 6;
std::string homepage[homePageCommands] = {c5, c5Desc, c6, c6Desc, c8, c8Desc};


void changeStoredString(std::string desc){
	
	/* Used to change stored account data i.e username, password */
	
	// String to overwrite old store
	std::string overwrite;
	
	// Help text and user input
	std::cout << "Enter new " + desc + ": ";
	std::cin >> overwrite;
	
	// Overwrite stored text depending on choice
	if (desc == "username"){
		usernames[logInID] = overwrite;
	} else if (desc == "password"){
		passwords[logInID] = overwrite;
	}
}


void commandsHelp(bool onHomePage) {
	
	/* Displays corresponding commands and their descriptions */
	
	if (!onHomePage){
		// Displays user commands 
		std::cout << "\nCommands available: \n";
		for (int i = 0; i < loggedInCommands; i += 2){
			std::cout << commands[i] + commands[i+1] + "\n";
		}
	} else {
		// Displays register and login command
		std::cout << "\nCommands available: \n";
		for (int i = 0; i < homePageCommands; i += 2){
			std::cout << homepage[i] + homepage[i+1] + "\n";
		}
	}
}


void commandLine(){
	
	// Store for user's inputted command
	std::string userC;
	
	// Display commands and description
	bool onHomePage = false;
	commandsHelp(onHomePage);
	
	/* Commands only available when logged in */
	while (loggedIn){
		
		// user inputs command
		std::cout << "\n[Account Page]\nEnter command: ";
		std::cin >> userC;
		
		// execute user input
		if (userC == c1){
			changeStoredString("username");
		} else if (userC == c2){
			changeStoredString("password");
		} else if (userC == ce){
			std::cout << "\nShutting down...";
			return;
		} else if (userC == c3){
			loggedIn = false;
			logInID = -1;
		} else if (userC == c4){
			std::cout <<  "\n[Account data]\n" << "username: " + usernames[logInID] +
						  "\n" << "password: " + passwords[logInID] + "\n";
		} else if (userC == c7) {
			std::cout << "Deleting System32 please wait... \n";
		} else {
			std::cout << "Unrecognised command";
		}
		
	}
	
}


int checkForEmptySpace(){
	/* return index of empty element 
	   otherwise return -1 */
	for (int i = 0; i < maxAccounts; i++){
		if (usernames[i] == "null"){
			return i;
		}
	}
	return -1;
}


int nameTaken(std::string username) {
	/* return index if the name does not already exist 
	   otherwise return -1 */
	for (int i = 0; i < maxAccounts; i++){
		if (usernames[i] == username){
			return i;
		}
	}
	return -1;
}


void addAccount(std::string username_reg, std::string pw_reg){
	
	/* Performs checks on inputted data: [dissalowed username, 
	   name already exists, space available for account].
	   
	   If checks pass then add/store the account.
	*/
	
	// Disallow certain usernames (replace with array if necessary)
	if (username_reg == "exit" || username_reg == "null"){
		std::cout << "Dissallowed username.";
		return;
	}
	
	// Ensure the account name is not already taken
	if (nameTaken(username_reg) != -1) {
		std::cout << "Username already taken.";
		return;
	}
	
	// Ensure there is memory available for new account
	int i;
	if ((i = checkForEmptySpace()) == -1){
		std::cout << "No more accounts may be stored.";
		return;
	}
	
	// If checks are passed store the new account
	usernames[i] = username_reg;
	passwords[i] = pw_reg;
	
}


void registerAccount() {
	
	// Store for user input
	std::string username_reg;
	std::string pw_reg;
	
	// Take user input
	std::cout << "\nEnter new username: ";
	std::cin >> username_reg;
	std::cout << "Enter new password: ";
	std::cin >> pw_reg;
	
	addAccount(username_reg, pw_reg);
	
}


void logIn(){
	
	/* Log in functionality */
	
	int pw_index;
	while(!loggedIn){
		// Take username
		std::cout << "\nType username as 'exit' to return to the homepage.\n";
		std::cout << "Enter username: ";
		std::cin >> username_inp;
		
		// Take password
		std::cout << "Enter password: ";
		std::cin >> password_inp;
		
		// Prevents logging in as null
		if (username_inp == "null"){
			std::cout << "Username/password combination incorrect";
			return;
		}

		// Check if username exists
		pw_index = nameTaken(username_inp);
		if (pw_index == -1){
			std::cout << "Username/password combination incorrect";
			return;
		}
		
		// Compare input password to stored password
		else {
			if (password_inp == passwords[pw_index]){
				std::cout << "\nLogged in as: " << username_inp << "\n";
				loggedIn = true;
			} else {
				std::cout << "Username-password combination incorrect";
				return;
			}
		}
	}
	
	if (loggedIn){
		logInID = pw_index;
		commandLine();
	}
}


void getAllData(){
	
	std::cout << "Usernames | Passwords\n";
	for (int i = 0; i < maxAccounts; i++){
		std::cout << usernames[i] + " " + passwords[i] + "\n";
	}
	
}


void homePage(){
	
	/* Present login and register feature to user */
	
	// Store for user's inputted command
	std::string userC;
	
	// Display commands and description for homepage
	bool onHomePage = true;
	commandsHelp(onHomePage);
	
	// home page loop
	while(!loggedIn){
		
		// User inputs command
		std::cout << "\n[Home Page]\nEnter command: ";
		std::cin >> userC;
		
		// Execute user input - register an account
		if (userC == c5){  
			registerAccount();
		} 
		
		// log into an existing account
		else if (userC == c6){  
			logIn();
		} 
		
		// display all account info
		else if (userC == c8){
			getAllData();
		}
		
		// incorrect input
		else {
			std::cout << "Unrecognised command";
		}
		
	}
}


int main(){
	
	homePage();
	
	return 0;
}

