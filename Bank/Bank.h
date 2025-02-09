#pragma once
#include "Customer.h"
#include "../Accounts/Account.h"
#include "Log.h"
#include <fstream>

class Bank
{
	char* name;
	char* address;
	Customer** customers;
	size_t customersCount, customersCapacity;
	Account** accounts;
	size_t accountsCount,  accountsCapacity;
	Log* log;
	size_t logCount, logCapacity;

	void copyFrom(const Bank& other);
	void free();
	void resizeCustomers();
	void resizeAccounts();
	void resizeLog();

	void addToLog(const char* data);

	void setName(const char* name);
	void setAddress(const char* address);

	void addAccount(Account* account);
	void deleteAccountFromIndex(size_t index);

public:
	Bank() = delete;
	Bank(const char* name, const char* address);
	Bank(const Bank& other);
	Bank& operator=(const Bank& other);
	~Bank();

	void addCustomer(const char* name, const char* address);
	void deleteCustomer(const char* name, const char* address);
	void addNormalAccount(size_t id, const char* userName, const char* password, const char* iban, double amount);
	void addSavingsAccount(size_t id, const char* userName, const char* password, const char* iban, double amount, double interestRate);
	void addPrivelegeAccount(size_t id, const char* userName, const char* password, const char* iban, double amount, double overdraft);
	void deleteAccount(const char* iban);
	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount(const char* name, const char* address) const;
	void listLog() const;
	void exportLog(std::ofstream& outFile) const;
	void display() const;
	bool deposit(double amount, const char* iban);
	bool withdraw(double amount, const char* iban);
	bool transfer(double amount, const char* myIban, const char* toIban);
};
