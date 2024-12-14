#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

// CLASS SPACE.

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
        }

        int currentLine = 0;
        string line;
        while (getline(file, line)) {
            currentLine++;
            switch (currentLine) {
                case 1:
                    name = line;
                    break;
                case 2:
                    password = line;
                    break;
                case 3:
                    balance = stoi(line);
                    break;
            }
        }
        file.close();
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
};

// CLASS SPACE END.


// FUNCTIONS SPACE.

// FUNCTIONS SPACE END.


int main(){
	
	do {
		
		// Variables = userChoice(int) , userAccount(class)[name, password(not_important_here), balance], accountChoice
		
		cout << "|=====MENU=====|" << endl;
		cout << "   1. Create an account.\n   2. Use an existing account.\n   3. Change bank settings.\n   0. Exit the program.\nInput: ";
		cin >> userChoice;

		if (userChoice == 1){
			accountCreate();
		}
		
		else if (userChoice == 2){
			userAccount = accountSelect();
			
			do {
				cout << "|===ACCOUNT-MENU===|" << endl;
				cout << "   1. Deposit amount.\n   2. Withdraw amount.\n   3. Transfer to another account.\n   0.Exit account settings.\nInput: ";
				cin >> accountChoice;
				
				switch(accountChoice){
					case 1:
						accountDeposit();
						break;
					case 2:
						accountWithdraw();
						break;
					case 3:
						accountTransfer();
						break;
					case 0:
						break;
					default:
						cout << "Invalid input entered. Try again." << endl;
						break;
				}
				
				updateAccount();
				
			}
			
		}
		
		else if (userChoice == 3){
			bankSettings();
		}
		
		else if (userChoice == 0){
			return 0;
		}
		
		else {
			cout << "Invalid value entered. Try again." << endl;
		}
		
	}
}
