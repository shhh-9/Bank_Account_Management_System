#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <direct.h>

using namespace std;

// =====CLASS SPACE.



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

// MUSAB HERE.


// AQIB HERE.


// =====FUNCTIONS SPACE END.


int main(){

	

}

