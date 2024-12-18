#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <direct.h>

// ASSUMPTION # 1: When integers are inputted, strings will cause an error.
// ASSUMPTION # 2: Amounts are always positive.
// ASSUMPTION # 3: Files are not opened and tampered with.

using namespace std;

// CLASS SPACE.

// Bank accont class.
class bankAccount {
	// Private attriibute to not let it be accessed directly.
	private:
	    string name = "", password = "";
	    int balance = 0;
	
	// Indirect functions made to access variables.
	public:
		// Initializing operator.
	    bankAccount(string fileName) {
	        ifstream file(fileName);
	        if (!file.is_open()) {
	            cerr << "ERROR: Could not open file." << endl;
	            return;
	        } else {
	            int currentLine = 0;
	            string line;
	            while (getline(file, line)) {
	                currentLine++;
	                if (currentLine == 1) {
	                    name = line;
	                }
	                if (currentLine == 2) {
	                    password = line;
	                }
	                if (currentLine == 3) {
	                    balance = stoi(line);
	                }
	            }
	            file.close();
	        }
	    }
	
		// To return all the variables.
	    string getName() { return name; }
	    string getPassword() { return password; }
	    int getBalance() { return balance; }
	
		// To update name variable.
	    void updateName(string newName) {
	        name = newName;
	    }
	
		// To update password variable.
	    void updatePassword(string newPassword) {
	        password = newPassword;
	    }
	
		// To update balance variable.
	    void updateBalance(int newBalance) {
	        balance = newBalance;
	    }
};

// CLASS SPACE END.

// FUNCTION SPACE.
// Shahmeers Functions.
//Shahmeer Function 1.
void accountCreate() {
    string accountName, accountPassword, accountID; // Declarations.

    cin.ignore(); // To initialize the input buffer. (Otherwise will use that instead of value given by user)
    // Inputting account name.
    cout << "Enter an account name: ";
    getline(cin, accountName);
    // Inputting account password.
    cout << "Enter a password for your account: ";
    getline(cin, accountPassword);

    srand(time(0)); // Seting seed for a random number generator.
    while (true) {
        accountID = to_string(rand() % 9000 + 1000); // To generate a random number between 1000 and 9999.
        ifstream file("accountIDs.txt"); // Opening and saving accountID in file.
        	
		// Will check if exists, if not then will break out of loop. Otherwise, process will repeat.
        if (!file.is_open()) {
            cerr << "ERROR: Could not open file." << endl;
            return;
        } else {
            string line;
            bool found = false;
            while (getline(file, line)) {
                if (accountID == line) {
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found) {
                break;
            }
        }
    }

    ofstream file("Users/" + accountID + ".txt"); // Creating the account file.
    cout << "Your generated account ID is " << accountID << "." << endl << endl; // Printing out account ID.
    
    // To initialize the values within the file of the account.
    if (!file.is_open()) {
        cerr << "ERROR: Could not open file." << endl;
        return;
    } else {
        file << accountName << endl;
        file << accountPassword << endl;
        file << 0 << endl;
        file.close();
    }

	// To append account ID into list.
    ofstream file2("accountIDs.txt", ios::app); // Opening file for append.
    if (!file2.is_open()) {
        cerr << "ERROR: Could not open file." << endl << endl;
        return;
    } else {
        file2 << accountID << endl;
        file2.close();
    }

	// Making empty transaction file.
    ofstream transactionFile("Users/" + accountID + "T.txt");
    transactionFile.close();
}
//shahmeer function 1 ends here.


//Shahmeer Function 2.
// Selecting an account throuh it's accountID.
string accountSelect() {
    string accountID; // Declarations.
    bool checkID = false; // To check if account exists.

    do {
    	// Asking for id.
        cout << "Enter the account's id (or type 'exit' to return to the main menu): ";
        cin >> accountID;

		// Exiting infinite loop.
        if (accountID == "exit") {
            return "";
        }

		// Checking from "acountIDs.txt" if acountID exists.
        ifstream file("accountIDs.txt");
        if (!file.is_open()) {
            cerr << "ERROR: Could not open file." << endl << endl;
            return "";
        } else {
            string line;
            while (getline(file, line)) {
                if (line == accountID) {
                    checkID = true;
                    break;
                }
            }
            file.close();
            if (!checkID) {
                cout << "ID is either invalid or does not exist. Try again." << endl << endl;
            } else {
                break;
            }
        }
    } while (!checkID);

    return accountID;
}

//shahmeer function 2 ends here.
// Updating an account through values in it's class.
void updateAccount(string accountFileName, bankAccount &userAccount) {
    ofstream outFile("Users/" + accountFileName); // Opening file.
	// Rewriting entire file with new values.
    if (!outFile.is_open()) {
        cerr << "ERROR: Could not open file for writing." << endl << endl;
        return;
    } else {
        outFile << userAccount.getName() << endl;
        outFile << userAccount.getPassword() << endl;
        outFile << userAccount.getBalance() << endl;
        outFile.close();
    }
}

// Creating folder "Users/" and "accountIDs.txt" file.
void initialize() {
	// Will try to read file, if unsucessful, will create it.
    ifstream checkFile("accountIDs.txt");
    if (!checkFile.is_open()) {
        ofstream file("accountIDs.txt");
        file.close();
    }
    // Function to create a file. Returns 0 for created, -1 for not.
    if (_mkdir("Users") == 0){
    	// FOLDER CREATED.
	}
}

// To close the account.
void closeAccount(string accountID) {
	// Declarations and opening of files.
    ifstream inFile("accountIDs.txt");
    ofstream outFile("temp.txt");
    string line;

	// Searching for line with account ID and then removing it indirectly.
	// (Done through creating a new file without the accountID in question)
    while (getline(inFile, line)) {
        if (line != accountID) {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();

	// Removing older "accountIDs.txt" and replacing it with the temporary new file.
    remove("accountIDs.txt");
    rename("temp.txt", "accountIDs.txt");

	// IMPORTANT: (.c_str() is used to convert variable into a const char* as a string datatype will create a compilation error)
	// Removing the account file.
    string filePath = "Users/" + accountID + ".txt";
    remove(filePath.c_str());
	// Removing the transaction file.
    string transactionFilePath = "Users/" + accountID + "T.txt";
    remove(transactionFilePath.c_str());
}

// To initialize the entire system.
void reset() {
    ifstream accountIDsFile("accountIDs.txt");
    if (!accountIDsFile.is_open()) {
        cerr << "ERROR: Could not open accountIDs.txt." << endl;
        return;
    }

	// Will remove account file through taking each line from "accountIDs.txt".
    string accountID;
    while (getline(accountIDsFile, accountID)) {
        string accountFilePath = "Users/" + accountID + ".txt";
        string transactionFilePath = "Users/" + accountID + "T.txt";

        remove(accountFilePath.c_str());
        remove(transactionFilePath.c_str());
    }
    accountIDsFile.close();
	
	// Will clean the "accountIDs.txt" file.
    ofstream resetFile("accountIDs.txt", ios::trunc);
    resetFile.close();
    initialize();
}

// Will log transaction message into the account transaction file.
void logTransaction(string accountID, string message) {
    ofstream transactionFile("Users/" + accountID + "T.txt", ios::app);
    if (transactionFile.is_open()) {
        transactionFile << message << endl;
        transactionFile.close();
    }
}

// FUNCTION SPACE END.

// Running main function.
int main() {
	
    initialize(); // Will create "accountIDs.txt" and "Users/" folder.
    
    // Declarations.
    int userChoice, settingsChoice;
    string userAccountFile, accountPassword, userPassword;
    int accountChoice, accountBalance, userAmount;

	// Run an infinitely running loop that will end when program ends.
    do {
    	// Main menu.
        cout << endl << "|=====MENU=====|" << endl;
        cout << "   1. Create an account.\n   2. Use an existing account.\n   3. Reset all accounts.\n   0. Exit the program.\nInput: ";
        cin >> userChoice; // Main menu operator.

		// A new account will be created.
        if (userChoice == 1) {
            accountCreate();
        }

		// An existing account will be selected.
        else if (userChoice == 2) {
            userAccountFile = accountSelect(); // AccountID will be stored through the function.
            {
            	// In case of an error in accountSelect, loop will restart.
            	if (userAccountFile == ""){
            		continue;
				}
			}
            bankAccount userAccount("Users/" + userAccountFile + ".txt"); // A user account is declared as an existing class.

			// Ask for password. And repeat till password is right. (Infinite loop.
            do {
                accountPassword = userAccount.getPassword(); // Will initialize the account password.
                cout << "Enter password: "; // Asking for password.
                cin >> userPassword;
                
                // If password is right, welcome and break. Else, repeat.
                if (userPassword == accountPassword) {
                    cout << "Welcome, " << userAccount.getName() << "." << endl; // Wil ask for name of account from class.
                    break;
                } else {
                    cout << "Incorrect password. Try again." << endl;
                }
                
            } while (true);

			// Infinitely running loop till exited.
            do {
            	bool closeCheck = false; // Boolean flag check for a closed account.
            	
            	// Initialize account details.
                accountBalance = userAccount.getBalance();
                string accountName = userAccount.getName();
                
                // Second menu.
                cout << endl << "|===ACCOUNT-MENU===|" << endl;
                cout << "   1. Deposit amount.\n   2. Withdraw amount.\n   3. Transfer money.\n   4. View transaction history.\n   5. Account settings.\n   0. Exit account settings.\nInput (Account balance: " << accountBalance << "): ";
                cin >> accountChoice; // Second menu operator.

				// Conditional statement with account choice.
                switch (accountChoice) {
                	
                	// To deposit amount into account.
                    case 1:
                    	// Asking for amount to deposit.
					    cout << "Enter the amount you want to deposit: ";
					    cin >> userAmount;
					    accountBalance += userAmount; // Increments account from balance.
					    userAccount.updateBalance(accountBalance); // Updating balance into class.
					    {
					        string message = "Deposited " + to_string(userAmount) + "."; // Making variable for transaction message.
					        logTransaction(userAccountFile, message); // Storing transaction message in file. ("[AccountID]T.txt")
					        cout << message << ". New balance: " << accountBalance << endl; // Print out message in terminal.
					    }
					    break;
					    
					// To withdraw amount from account.
					case 2:
						// Asking for amount to withdraw.
					    cout << "Enter the amount you want to withdraw: ";
					    cin >> userAmount;
					    if (userAmount > accountBalance) {
					        cout << "Insufficient funds." << endl << endl; // Print error message if amount is greater than balance in account.
					    } 
						else {
					        accountBalance -= userAmount; // Decrement amount from balance.
					        userAccount.updateBalance(accountBalance); // Updating balance into class.
					        {
					            string message = "Withdrew " + to_string(userAmount) + "."; // Making variable for transaction message.
					            logTransaction(userAccountFile, message); // Storing transaction message in file. ("[AccountID]T.txt")
					            cout << message << ". New balance: " << accountBalance << endl; // Print out message in terminal.
					        }
					    }
					    break;
					    
					// To transfer amount between account.
					case 3:
					    {
					    	// Will obtain recipent's ID.
					        string recipientID;
					        cout << "Enter the recipient's account ID: ";
					        cin >> recipientID;
					
							// Will try to open and create a recipent account class.
					        bankAccount recipientAccount("Users/" + recipientID + ".txt");
					        if (recipientAccount.getName() == "") {
					        	// If unopened, class values initialized as empty. So case will break with error message.
					            cout << "Recipient account does not exist." << endl;
					            break;
					        }
					
							// Take a transferring amount.
					        cout << "Enter the amount to transfer: ";
					        cin >> userAmount;
					
							// If amount is greater than balance, error message outputted.
					        if (userAmount > accountBalance) {
					            cout << "Insufficient funds." << endl;
					            break;
					        }
					
							// Amount removed from balance.
					        accountBalance -= userAmount;
					        userAccount.updateBalance(accountBalance); // Updating class.
					
							// Amount added into recipent's balance.
					        int recipientBalance = recipientAccount.getBalance() + userAmount;
					        recipientAccount.updateBalance(recipientBalance); // Updating class.
					
							// Using function to update both account files.
					        updateAccount(userAccountFile + ".txt", userAccount);
					        updateAccount(recipientID + ".txt", recipientAccount);
					
							// Making suitable transaction messages.
					        string senderMessage = "Transferred " + to_string(userAmount) + " to " + recipientAccount.getName() + ".";
					        string recipientMessage = "Received " + to_string(userAmount) + " from " + userAccount.getName() + ".";
					
							// Logging transactions into files.
					        logTransaction(userAccountFile, senderMessage);
					        logTransaction(recipientID, recipientMessage);
					
							// Printing out new balance.
					        cout << senderMessage << ". New balance: " << accountBalance << endl;
					    }
					    break;
					
					case 4:
					    {
					    	// Opening transaction file.
					        string transactionFile = "Users/" + userAccountFile + "T.txt";
					        ifstream file(transactionFile);
						
							// If file is not opened, transaction history does not exist.
					        if (!file.is_open()) {
					            cout << "No transaction history available." << endl;
					        }
					        // Else, will print out entire transaction history.
							else {
					            string line;
					            cout << "Transaction History:" << endl;
					            while (getline(file, line)) {
					                cout << line << endl;
					            }
					            file.close();
					        }
					    }
					    break;

					case 5:
                        do {
                        	// Third menu.
                            cout << endl << "|SETTINGS|" << endl;
                            cout << "   1. Change account name.\n    2. Change account password.\n   3. Close account.\n   0. Exit settings.\nInput: ";
                            cin >> settingsChoice; // Third menu operator.
                            // To change the account name.
                            if (settingsChoice == 1) {
                                cout << "Enter the new account name: ";
                                cin.ignore();
                                getline(cin, accountName);
                                userAccount.updateName(accountName);
                                break;
                            }
                            // To change the account password.
							else if (settingsChoice == 2) {
                                cout << "Enter the new password: ";
                                cin >> accountPassword;
                                userAccount.updatePassword(accountPassword);
                                break;
                            }
							// To close an account. (Completely delete it)
							else if (settingsChoice == 3) {
                                closeAccount(userAccountFile);
                                cout << "Account closed successfully." << endl;
                                userAccountFile = "";
                                closeCheck = true;
                                break;
                            }
							// Exit third menu.
							else if (settingsChoice == 0) {
                                break;
                            }
							// Error message in case of invalid input.
							else {
                                cout << "Invalid input. Try again." << endl;
                            }
                        } while (true);
                        break;
                    // Exit second menu.    
                    case 0:
                        break;
                    // Error message in case of invalid input.
                    default:
                        cout << "Invalid input entered. Try again." << endl;
                        break;
                }
                if (closeCheck){break;} // Break out to main menu if account closed.
                updateAccount(userAccountFile + ".txt", userAccount); // Update all changed info into file.
            } while (accountChoice != 0);
        }

		// The entire system will be reset.
        else if (userChoice == 3) {
            reset();
            cout << "All accounts have been reset." << endl;
        }

		// The program will end.
        else if (userChoice == 0) {
            return 0;
        }

		// If incorrect integer is inputted, an error message will be displayed.
        else {
            cout << "Invalid value entered. Try again." << endl;
        }

    } while (true);
}
