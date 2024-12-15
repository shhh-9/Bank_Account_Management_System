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

	

}

