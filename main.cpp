include<iostream>

using namespace std;

int main(){
	
	cout << "|======MENU======|\n   1. Create an account.\n   2. Use an existing account.   0. Exit the program.\nInput (PASS for admin): ";
	cin >> userChoice;
	
	do {
		if (userChoice == 0){
			return 0;
		}
		else if (userChoice == 1){
			accountCreate();
		}
		else if (userChoice == 2){
			cout << "|===ACCOUNT-MENU===|\n   1. Deposit balance.\n   2. Withdraw balance.\n   3. View transaction history.\n   0. Exit menu.\nInput: ";
			cin >> accountChoice;
			while (accountChoice != 0){
				switch (accountChoice) {
	            case 1:
	                depositBalance();
	                break;
	            case 2:
	                withdrawBalance();
	                break;
	            case 3:
	                transactionHistory();
	                break;
	            default:
	                cout << "Invalid value entered. Try again." << endl;
	    	}
		}
		else {
			cout << "Invalid value entered. Try again." << endl;
		}
	} while (true);
}
