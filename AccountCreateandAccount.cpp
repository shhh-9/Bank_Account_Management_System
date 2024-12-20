#include <iostream>
using namespace std;


//Account Create starts here.

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



// ACCOUNT sELECT STARTS HERE
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
// Shahmeers functions end her
