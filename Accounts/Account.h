#pragma once
#include <ctime>

class Account
{
	char* userName;
	char* password;
	char* iban;
	double amount;
	size_t ID;
	time_t dayOfCreation;

	void copyFrom(const Account& other);
	void free();

	void setUserName(const char* userName);
	void setPassword(const char* password);
	void setIban(const char* iban);

protected:
	void setAmount(double amount);

public:
	Account() = delete;
	Account(const char* userName, const char* password, const char* iban, double amount, size_t ID);
	Account(const Account& other);
	Account& operator=(const Account& other);
	virtual ~Account();

	const char* getIban() const;
	size_t getID() const;
	double getBalance() const;

	virtual Account* clone() const = 0;

	void deposit(double amount);
	virtual bool withdraw(double amount) = 0;
	virtual void display() const;
};
