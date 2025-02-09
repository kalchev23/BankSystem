#include "Bank.h"
#include "../Accounts/NormalAccount.h"
#include "../Accounts/SavingsAccount.h"
#include "../Accounts/PrivelegeAccount.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

void Bank::copyFrom(const Bank& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	address = new char[strlen(other.address) + 1];
	strcpy(address, other.address);

	customersCount = other.customersCount;
	customersCapacity = other.customersCapacity;
	customers = new Customer * [customersCapacity];
	for (size_t i = 0; i < customersCount; i++)
	{
		customers[i] = other.customers[i]->clone();
	}

	accountsCount = other.accountsCount;
	accountsCapacity = other.accountsCapacity;
	accounts = new Account * [accountsCapacity];
	for (size_t i = 0; i < accountsCount; i++)
	{
		accounts[i] = other.accounts[i]->clone();
	}

	logCount = other.logCount;
	logCapacity = other.logCapacity;
	log = new Log [logCapacity];
	for (size_t i = 0; i < logCount; i++)
	{
		log[i] = other.log[i];
	}
}

void Bank::free()
{
	delete[] name;
	delete[] address;

	for (size_t i = 0; i < customersCount; i++)
	{
		delete customers[i];
	}
	delete[] customers;

	for (size_t i = 0; i < accountsCount; i++)
	{
		delete accounts[i];
	}
	delete[] accounts;

	delete[] log;
}

void Bank::resizeCustomers()
{
	Customer** temp = new Customer * [customersCapacity];
	for (size_t i = 0; i < customersCount; i++)
		temp[i] = customers[i];

	delete[] customers;
	customers = temp;
}

void Bank::resizeAccounts()
{
	Account** temp = new Account * [accountsCapacity];
	for (size_t i = 0; i < accountsCount; i++)
		temp[i] = accounts[i];

	delete[] accounts;
	accounts = temp;
}

void Bank::resizeLog()
{
	logCapacity *= 2;
	Log* temp = new Log[logCapacity];
	for (size_t i = 0; i < logCount; i++)
		temp[i] = log[i];

	delete[] log;
	log = temp;
}

void Bank::addToLog(const char* data)
{
	if (logCount == logCapacity)
		resizeLog();

	log[logCount++] = Log(data);
}

void Bank::setName(const char* name)
{
	if (name == nullptr || name == this->name)
		return;

	if (this->name != nullptr)
		delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Bank::setAddress(const char* address)
{
	if (address == nullptr || address == this->address)
		return;

	if (this->address != nullptr)
		delete[] this->address;

	this->address = new char[strlen(address) + 1];
	strcpy(this->address, address);
}

void Bank::addAccount(Account* account)
{
	if (accountsCount == accountsCapacity)
	{
		accountsCapacity *= 2;
		resizeAccounts();
	}
	accounts[accountsCount++] = account;
}

void Bank::deleteAccountFromIndex(size_t index)
{
	delete accounts[index];
	for (size_t i = index + 1; i < accountsCount; i++)
	{
		accounts[i - 1] = accounts[i];
	}

	accountsCount--;
	if (accountsCount == accountsCapacity / 4)
	{
		accountsCapacity /= 2;
		resizeAccounts();
	}
}

Bank::Bank(const char* name, const char* address)
{
	setName(name);
	setAddress(address);

	customersCapacity = 4;
	customersCount = 0;
	customers = new Customer * [customersCapacity];

	accountsCapacity = 4;
	accountsCount = 0;
	accounts = new Account * [accountsCapacity];

	logCapacity = 4;
	logCount = 0;
	log = new Log [logCapacity];
}

Bank::Bank(const Bank& other)
{
	copyFrom(other);
}

Bank& Bank::operator=(const Bank& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Bank::~Bank()
{
	free();
}

void Bank::addCustomer(const char* name, const char* address)
{
	if (customersCount == customersCapacity)
	{
		customersCapacity *= 2;
		resizeCustomers();
	}

	for (size_t i = 0; i < customersCount; i++)
	{
		if (strcmp(name, customers[i]->getName()) == 0 && strcmp(address, customers[i]->getAddress()) == 0)
			return;
	}
	Customer* newCustomer = new Customer(name, address);
	customers[customersCount++] = newCustomer;

	addToLog("Add Customer");
}

void Bank::deleteCustomer(const char* name, const char* address)
{
	for (size_t i = 0; i < customersCount; i++)
	{
		if (strcmp(name, customers[i]->getName()) == 0 && strcmp(address, customers[i]->getAddress()) == 0)
		{
			size_t tempId = customers[i]->getID();

			for (size_t j = 0; j < accountsCount; j++)
			{
				if (tempId == accounts[j]->getID())
				{
					deleteAccountFromIndex(j);
					j--;
				}
			}
			delete customers[i];
			for (size_t j = i + 1; j < customersCount; j++)
			{
				customers[j - 1] = customers[j];
			}

			customersCount--;
			if (customersCount == customersCapacity / 4)
			{
				customersCapacity /= 2;
				resizeCustomers();
			}

			addToLog("Delete Customer");
			break;
		}
	}
}

void Bank::addNormalAccount(size_t id, const char* userName, const char* password, const char* iban, double amount)
{
	for (size_t i = 0; i < customersCount; i++)
	{
		if (id == customers[i]->getID())
		{
			NormalAccount* newAccount = new NormalAccount(userName, password, iban, amount, id);
			addAccount(newAccount);

			addToLog("Add Normal Account");
			break;
		}
	}
}

void Bank::addSavingsAccount(size_t id, const char* userName, const char* password, const char* iban, double amount, double interestRate)
{
	for (size_t i = 0; i < customersCount; i++)
	{
		if (id == customers[i]->getID())
		{
			SavingsAccount* newAccount = new SavingsAccount(userName, password, iban, amount, id, interestRate);
			addAccount(newAccount);

			addToLog("Add Savings Account");
			break;
		}
	}
}

void Bank::addPrivelegeAccount(size_t id, const char* userName, const char* password, const char* iban, double amount, double overdraft)
{
	for (size_t i = 0; i < customersCount; i++)
	{
		if (id == customers[i]->getID())
		{
			PrivelegeAccount* newAccount = new PrivelegeAccount(userName, password, iban, amount, id, overdraft);
			addAccount(newAccount);

			addToLog("Add Privelege Account");
			break;
		}
	}
}

void Bank::deleteAccount(const char* iban)
{
	for (size_t i = 0; i < accountsCount; i++)
	{
		if (strcmp(iban, accounts[i]->getIban()) == 0)
		{
			delete accounts[i];
			for (size_t j = i + 1; j < accountsCount; j++)
			{
				accounts[j - 1] = accounts[j];
			}

			accountsCount--;
			if (accountsCount == accountsCapacity / 4)
			{
				accountsCapacity /= 2;
				resizeAccounts();
			}

			addToLog("Delete Account");
			break;
		}
	}
}

void Bank::listCustomers() const
{
	for (size_t i = 0; i < customersCount; i++)
	{
		std::cout << i + 1 << ". ";
		customers[i]->print();
	}
}

void Bank::listAccounts() const
{
	for (size_t i = 0; i < accountsCount; i++)
	{
		std::cout << i + 1 << ". ";
		accounts[i]->display();
	}
}

void Bank::listCustomerAccount(const char* name, const char* address) const
{
	for (size_t i = 0; i < customersCount; i++)
	{
		if (strcmp(name, customers[i]->getName()) == 0 && strcmp(address, customers[i]->getAddress()) == 0)
		{
			size_t tempId = customers[i]->getID();
			for (size_t j = 0; j < accountsCount; j++)
			{
				if (tempId == accounts[j]->getID())
				{
					std::cout << " . ";
					accounts[j]->display();
				}
			}
		}
	}
}

void Bank::listLog() const
{
	for (size_t i = 0; i < logCount; i++)
	{
		std::cout << i + 1 << ". ";
		log[i].print();
	}
}

void Bank::exportLog(std::ofstream& outFile) const
{
	for (size_t i = 0; i < logCount; i++)
	{
		outFile << log[i].getData() << "\n";
	}
}

void Bank::display() const
{
	std::cout << name << " " << address << " " << customersCount << " " << accountsCount << std::endl;
}

bool Bank::deposit(double amount, const char* iban)
{
	for (size_t i = 0; i < accountsCount; i++)
	{
		if (strcmp(iban, accounts[i]->getIban()) == 0)
		{
			accounts[i]->deposit(amount);

			addToLog("Deposit");
			return true;
		}
	}
	return false;
}

bool Bank::withdraw(double amount, const char* iban)
{
	for (size_t i = 0; i < accountsCount; i++)
	{
		if (strcmp(iban, accounts[i]->getIban()) == 0)
		{
			if (accounts[i]->withdraw(amount))
			{
				addToLog("Withdraw");
				return true;
			}
			return false;
		}
	}
	return false;
}

bool Bank::transfer(double amount, const char* myIban, const char* toIban)
{
	for (size_t i = 0; i < accountsCount; i++)
	{
		if (strcmp(myIban, accounts[i]->getIban()) == 0)
		{
			if (accounts[i]->withdraw(amount))
			{
				for (size_t j = 0; j < accountsCount; j++)
				{
					if (strcmp(toIban, accounts[j]->getIban()) == 0)
					{
						accounts[j]->deposit(amount);

						addToLog("Transfer");
						return true;
					}
				}
			}
		}
	}
	return false;
}
