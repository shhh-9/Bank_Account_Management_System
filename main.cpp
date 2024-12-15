#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <direct.h>

using namespace std;

// =====CLASS SPACE.
class bankAccount {
private:
    string name, password;
    int balance;

public:
    bankAccount(string fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "ERROR: Could not open file." << endl << endl;
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

    string getName() { return name; }
    string getPassword() { return password; }
    int getBalance() { return balance; }

    void updateName(string newName) {
        name = newName;
    }

    void updatePassword(string newPassword) {
        password = newPassword;
    }

    void updateBalance(int newBalance) {
        balance = newBalance;
    }

    void closeAccount() {
        name = "";
        password = "";
        balance = 0;
    }
};


// =====CLASS SPACE END.


// =====FUNCTIONS SPACE.

// SHAHMEER HERE.
void accountCreate() {
    string accountName, accountPassword, accountID;

    cin.ignore();
    cout << "Enter an account name: ";
    getline(cin, accountName);
    cout << "Enter a password for your account: ";
    getline(cin, accountPassword);

    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        accountID = to_string(rand() % 9000);
        ifstream file("accountIDs.txt");

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

    ofstream file("Users/" + accountID + ".txt");
    cout << "Your generated account ID is " << accountID << "." << endl << endl;
    if (!file.is_open()) {
        cerr << "ERROR: Could not open file." << endl;
        return;
    } else {
        file << accountName << endl;
        file << accountPassword << endl;
        file << 0 << endl;
        file.close();
    }

    ofstream file2("accountIDs.txt", ios::app);
    if (!file2.is_open()) {
        cerr << "ERROR: Could not open file." << endl << endl;
        return;
    } else {
        file2 << accountID << endl;
        file2.close();
    }

    ofstream transactionFile("Users/" + accountID + "T.txt");
    transactionFile.close();
}

string accountSelect() {
    string accountID;
    bool checkID = false;

    do {
        cout << "Enter the account's id (or type 'exit' to return to the main menu): ";
        cin >> accountID;

        if (accountID == "exit") {
            return "";
        }

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

// AQIB HERE.
void initialize() {
    ifstream checkFile("accountIDs .txt");
    if (!checkFile.is_open()) {
        ofstream file("accountIDs.txt");
        file.close();
    }
    if (_mkdir("Users") == 0){
    	// FOLDER CREATED.
	}
}

void closeAccount(string accountID) {
    ifstream inFile("accountIDs.txt");
    ofstream outFile("temp.txt");
    string line;

    while (getline(inFile, line)) {
        if (line != accountID) {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();

    remove("accountIDs.txt");
    rename("temp.txt", "accountIDs.txt");

    string filePath = "Users/" + accountID + ".txt";
    remove(filePath.c_str());

    string transactionFilePath = "Users/" + accountID + "T.txt";
    remove(transactionFilePath.c_str());
}

void reset() {
    ifstream accountIDsFile("accountIDs.txt");
    if (!accountIDsFile.is_open()) {
        cerr << "ERROR: Could not open accountIDs.txt." << endl;
        return;
    }

    string accountID;
    while (getline(accountIDsFile, accountID)) {
        string accountFilePath = "Users/" + accountID + ".txt";
        string transactionFilePath = "Users/" + accountID + "T.txt";

        remove(accountFilePath.c_str());
        remove(transactionFilePath.c_str());
    }
    accountIDsFile.close();

    ofstream resetFile("accountIDs.txt", ios::trunc);
    resetFile.close();
    initialize();
}

// MUSAB HERE.
void updateAccount(string accountFileName, bankAccount &userAccount) {
    ofstream outFile("Users/" + accountFileName);
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

void logTransaction(const string &accountID, const string &message) {
    ofstream transactionFile("Users/" + accountID + "T.txt", ios::app);
    if (transactionFile.is_open()) {
        transactionFile << message << endl;
        transactionFile.close();
    }
}
void transferMoney(bankAccount &senderAccount) {
    string recipientID;
    cout << "Enter the recipient's account ID: ";
    cin >> recipientID;

    bankAccount recipientAccount("Users/" + recipientID + ".txt");
    if (recipientAccount.getName() == "") {
        cout << "Recipient account does not exist." << endl;
        return;
    }

    int amount;
    cout << "Enter the amount to transfer: ";
    cin >> amount;

    if (amount > senderAccount.getBalance()) {
        cout << "Insufficient funds." << endl;
        return;
    }

    senderAccount.updateBalance(senderAccount.getBalance() - amount);
    recipientAccount.updateBalance(recipientAccount.getBalance() + amount);

    updateAccount(senderAccount.getName() + ".txt", senderAccount);
    updateAccount(recipientID + ".txt", recipientAccount);

    logTransaction(senderAccount.getName(), "Transferred " + to_string(amount) + " to " + recipientAccount.getName());
    logTransaction(recipientID, "Received " + to_string(amount) + " from " + senderAccount.getName());

    cout << "Transfer successful! " << amount << " has been transferred to " << recipientAccount.getName() << "." << endl;
}


// =====FUNCTIONS SPACE END.


int main(){
    initialize();
    int userChoice, settingsChoice;
    string userAccountFile, accountPassword, userPassword;
    int accountChoice, accountBalance, userAmount;

    do {
        cout << endl << "|=====MENU=====|" << endl;
        cout << "   1. Create an account.\n   2. Use an existing account.\n   3. Reset all accounts.\n   0. Exit the program.\nInput: ";
        cin >> userChoice;

        if (userChoice == 1) {
            accountCreate();
        }

        else if (userChoice == 2) {
            userAccountFile = accountSelect();
            if (userAccountFile == "") {
                continue;
            }
            bankAccount userAccount("Users/" + userAccountFile + ".txt");

            do {
                accountPassword = userAccount.getPassword();
                cout << "Enter password: ";
                cin >> userPassword;
                if (userPassword == accountPassword) {
                    cout << "Welcome, " << userAccount.getName() << "." << endl;
                    break;
                } else {
                    cout << "Incorrect password. Try again." << endl;
                }
            } while (true);

            do {
            	bool closeCheck = false;
                accountBalance = userAccount.getBalance();
                string accountName = userAccount.getName();
                cout << endl << "|===ACCOUNT-MENU===|" << endl;
                cout << "   1. Deposit amount.\n   2. Withdraw amount.\n   3. Transfer money.\n   4. View transaction history.\n   5. Account settings.\n   0. Exit account settings.\nInput (Account balance: " << accountBalance << "): ";
                cin >> accountChoice;

                switch (accountChoice) {
                    case 1:
					    cout << "Enter the amount you want to deposit: ";
					    cin >> userAmount;
					    accountBalance += userAmount;
					    userAccount.updateBalance(accountBalance);
					
					    {
					        string message = "Deposited " + to_string(userAmount) + ".";
					        logTransaction(userAccountFile, message);
					        cout << message << ". New balance: " << accountBalance << endl;
					    }
					    break;
					case 2:
					    cout << "Enter the amount you want to withdraw: ";
					    cin >> userAmount;
					    if (userAmount > accountBalance) {
					        cout << "Insufficient funds." << endl << endl;
					    } else {
					        accountBalance -= userAmount;
					        userAccount.updateBalance(accountBalance);
					
					        {
					            string message = "Withdrew " + to_string(userAmount) + ".";
					            logTransaction(userAccountFile, message);
					            cout << message << ". New balance: " << accountBalance << endl;
					        }
					    }
					    break;
					case 3:
					    {
					        string recipientID;
					        cout << "Enter the recipient's account ID: ";
					        cin >> recipientID;
					
					        bankAccount recipientAccount("Users/" + recipientID + ".txt");
					        if (recipientAccount.getName() == "") {
					            cout << "Recipient account does not exist." << endl;
					            break;
					        }
					
					        cout << "Enter the amount to transfer: ";
					        cin >> userAmount;
					
					        if (userAmount > accountBalance) {
					            cout << "Insufficient funds." << endl;
					            break;
					        }
					
					        accountBalance -= userAmount;
					        userAccount.updateBalance(accountBalance);
					
					        int recipientBalance = recipientAccount.getBalance() + userAmount;
					        recipientAccount.updateBalance(recipientBalance);
					
					        updateAccount(userAccountFile + ".txt", userAccount);
					        updateAccount(recipientID + ".txt", recipientAccount);
					
					        string senderMessage = "Transferred " + to_string(userAmount) + " to " + recipientAccount.getName() + ".";
					        string recipientMessage = "Received " + to_string(userAmount) + " from " + userAccount.getName() + ".";
					
					        logTransaction(userAccountFile, senderMessage);
					        logTransaction(recipientID, recipientMessage);
					
					        cout << senderMessage << ". New balance: " << accountBalance << endl;
					    }
					    break;
					
					case 4:
					    {
					        string transactionFile = "Users/" + userAccountFile + "T.txt";
					        ifstream file(transactionFile);
					
					        if (!file.is_open()) {
					            cout << "No transaction history available." << endl;
					        } else {
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
                            cout << endl << "|SETTINGS|" << endl;
                            cout << "1. Change account name.\n2. Change account password.\n3. Close account.\n0. Exit settings.\nInput: ";
                            cin >> settingsChoice;
                            if (settingsChoice == 1) {
                                cout << "Enter the new account name: ";
                                cin.ignore();
                                getline(cin, accountName);
                                userAccount.updateName(accountName);
                                break;
                            } else if (settingsChoice == 2) {
                                cout << "Enter the new password: ";
                                cin >> accountPassword;
                                userAccount.updatePassword(accountPassword);
                                break;
                            } else if (settingsChoice == 3) {
                                closeAccount(userAccountFile);
                                cout << "Account closed successfully." << endl;
                                userAccountFile = "";
                                closeCheck = true;
                                break;
                            } else if (settingsChoice == 0) {
                                break;
                            } else {
                                cout << "Invalid input. Try again." << endl;
                            }
                        } while (true);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input entered. Try again." << endl;
                        break;
                }
                if (closeCheck){break;}
                updateAccount(userAccountFile + ".txt", userAccount);
            } while (accountChoice != 0);
        }

        else if (userChoice == 3) {
            reset();
            cout << "All accounts have been reset." << endl;
        }

        else if (userChoice == 0) {
            return 0;
        }

        else {
            cout << "Invalid value entered. Try again." << endl;
        }

    } while (true);
	

}

