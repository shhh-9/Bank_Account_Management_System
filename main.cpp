#include<iostream>

using namespace std;

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
