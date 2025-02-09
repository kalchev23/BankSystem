#include <iostream>
#include <fstream>
#include <cstring>
#include "Bank/Bank.h"

using namespace std;

const int SIZE = 1024;

void input(Bank& bank)
{
	while (true)
	{
		cout << endl;
		cout << "1. Edit" << endl;
		cout << "2. List" << endl;
		cout << "3. Action" << endl;
		cout << "4. Display info for the bank" << endl;
		cout << "5. Quit" << endl;
		cout << endl;
		cout << ">";

		char buffer[SIZE];
		cin.getline(buffer, SIZE);

		if (strcmp("1", buffer) == 0)
		{
			cout << "a. Customer" << endl;
			cout << "b. Account" << endl;
			cout << ">";
			char buffer1[SIZE];
			cin.getline(buffer1, SIZE);

			if (strcmp("a", buffer1) == 0)
			{
				cout << "1. Add new customer" << endl;
				cout << "2. Delete customer" << endl;
				cout << ">";
				char buffer2[SIZE];
				cin.getline(buffer2, SIZE);

				if (strcmp("1", buffer2) == 0)
				{
					char name[SIZE];
					cin.getline(name, SIZE);
					char address[SIZE];
					cin.getline(address, SIZE);

					bank.addCustomer(name, address);
				}
				else if (strcmp("2", buffer2) == 0)
				{
					char name[SIZE];
					cin.getline(name, SIZE);
					char address[SIZE];
					cin.getline(address, SIZE);

					bank.deleteCustomer(name, address);
				}
			}
			else if (strcmp("b", buffer1) == 0)
			{
				cout << "1. Add new normal account" << endl;
				cout << "2. Add new savings account" << endl;
				cout << "3. Add new privelege account" << endl;
				cout << "4. Delete account" << endl;
				cout << ">";
				char buffer2[SIZE];
				cin.getline(buffer2, SIZE);

				if (strcmp("1", buffer2) == 0)
				{
					char tempID[SIZE];
					cin.getline(tempID, SIZE);
					size_t id = atoi(tempID);
					char userName[SIZE];
					cin.getline(userName, SIZE);
					char password[SIZE];
					cin.getline(password, SIZE);
					char iban[SIZE];
					cin.getline(iban, SIZE);
					char tempAmount[SIZE];
					cin.getline(tempAmount, SIZE);
					double amount = atof(tempAmount);

					bank.addNormalAccount(id, userName, password, iban, amount);
				}
				else if (strcmp("2", buffer2) == 0)
				{
					char tempID[SIZE];
					cin.getline(tempID, SIZE);
					size_t id = atoi(tempID);
					char userName[SIZE];
					cin.getline(userName, SIZE);
					char password[SIZE];
					cin.getline(password, SIZE);
					char iban[SIZE];
					cin.getline(iban, SIZE);
					char tempAmount[SIZE];
					cin.getline(tempAmount, SIZE);
					double amount = atof(tempAmount);
					char tempInterestRate[SIZE];
					cin.getline(tempInterestRate, SIZE);
					double interestRate = atof(tempInterestRate);

					bank.addSavingsAccount(id, userName, password, iban, amount, interestRate);
				}
				else if (strcmp("3", buffer2) == 0)
				{
					char tempID[SIZE];
					cin.getline(tempID, SIZE);
					size_t id = atoi(tempID);
					char userName[SIZE];
					cin.getline(userName, SIZE);
					char password[SIZE];
					cin.getline(password, SIZE);
					char iban[SIZE];
					cin.getline(iban, SIZE);
					char tempAmount[SIZE];
					cin.getline(tempAmount, SIZE);
					double amount = atof(tempAmount);
					char tempOverdraft[SIZE];
					cin.getline(tempOverdraft, SIZE);
					double overdraft = atof(tempOverdraft);

					bank.addPrivelegeAccount(id, userName, password, iban, amount, overdraft);
				}
				else if (strcmp("4", buffer2) == 0)
				{
					char iban[SIZE];
					cin.getline(iban, SIZE);

					bank.deleteAccount(iban);
				}
			}
		}
		else if (strcmp("2", buffer) == 0)
		{
			cout << "a. List all customers" << endl;
			cout << "b. List all accounts" << endl;
			cout << "c. List customer account" << endl;
			cout << "d. List log" << endl;
			cout << ">";
			char buffer1[SIZE];
			cin.getline(buffer1, SIZE);

			if (strcmp("a", buffer1) == 0)
			{
				bank.listCustomers();
			}
			else if (strcmp("b", buffer1) == 0)
			{
				bank.listAccounts();
			}
			else if (strcmp("c", buffer1) == 0)
			{
				char name[SIZE];
				cin.getline(name, SIZE);
				char address[SIZE];
				cin.getline(address, SIZE);

				bank.listCustomerAccount(name, address);
			}
			else if (strcmp("d", buffer1) == 0)
			{
				bank.listLog();
			}
		}
		else if (strcmp("3", buffer) == 0)
		{
			cout << "a. Withdraw from account" << endl;
			cout << "b. Deposit to account" << endl;
			cout << "c. Transfer" << endl;
			cout << ">";
			char buffer1[SIZE];
			cin.getline(buffer1, SIZE);

			if (strcmp("a", buffer1) == 0)
			{
				char tempAmount[SIZE];
				cin.getline(tempAmount, SIZE);
				double amount = atof(tempAmount);
				char iban[SIZE];
				cin.getline(iban, SIZE);

				if (bank.withdraw(amount, iban))
				{
					cout << "Withdraw successful" << endl;
				}
				else
				{
					cout << "Withdraw unsuccessful" << endl;
				}
			}
			else if (strcmp("b", buffer1) == 0)
			{
				char tempAmount[SIZE];
				cin.getline(tempAmount, SIZE);
				double amount = atof(tempAmount);
				char iban[SIZE];
				cin.getline(iban, SIZE);

				if (bank.deposit(amount, iban))
				{
					cout << "Deposit successful" << endl;
				}
				else
				{
					cout << "Deposit unsuccessful" << endl;
				}
			}
			else if (strcmp("c", buffer1) == 0)
			{
				char tempAmount[SIZE];
				cin.getline(tempAmount, SIZE);
				double amount = atof(tempAmount);
				char myIban[SIZE];
				cin.getline(myIban, SIZE);
				char toIban[SIZE];
				cin.getline(toIban, SIZE);

				if (bank.transfer(amount, myIban, toIban))
				{
					cout << "Transfer successful" << endl;
				}
				else
				{
					cout << "Transfer unsuccessful" << endl;
				}
			}
		}
		else if (strcmp("4", buffer) == 0)
		{
			bank.display();
		}
		else if (strcmp("5", buffer) == 0)
		{
			ofstream outFile("log.txt", ios::out | ios::trunc);
			if (!outFile.is_open())
			{
				std::cout << "Error while opening";
				return;
			}
			bank.exportLog(outFile);
			outFile.close();

			cout << "Quit";
			break;
		}
	}
}

int main()
{
    Bank bank("a", "b");

	input(bank);

    return 0;
}
