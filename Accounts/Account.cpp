#include "Account.h"
#include "../Bank/Customer.h"
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)

void Account::copyFrom(const Account& other)
{
	userName = new char [strlen(other.userName) + 1];
	strcpy(userName, other.userName);

	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);

	iban = new char[strlen(other.iban) + 1];
	strcpy(iban, other.iban);

	amount = other.amount;
	ID = other.ID;
	dayOfCreation = other.dayOfCreation;
}

void Account::free()
{
	delete[] userName;
	delete[] password;
	delete[] iban;
}

void Account::setUserName(const char* userName)
{
	if (userName == nullptr || userName == this->userName)
		return;

	if (this->userName != nullptr)
		delete[] this->userName;

	this->userName = new char[strlen(userName) + 1];
	strcpy(this->userName, userName);
}

void Account::setPassword(const char* password)
{
	if (password == nullptr || password == this->password)
		return;

	if (this->password != nullptr)
		delete[] this->password;

	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
}

void Account::setIban(const char* iban)
{
	if (iban == nullptr || iban == this->iban)
		return;

	if (this->iban != nullptr)
		delete[] this->iban;

	this->iban = new char[strlen(iban) + 1];
	strcpy(this->iban, iban);
}

void Account::setAmount(double amount)
{
	this->amount = amount;
}

Account::Account(const char* userName, const char* password, const char* iban, double amount, size_t ID)
{
	setUserName(userName);
	setPassword(password);
	setIban(iban);
	setAmount(amount);
	this->ID = ID;
	dayOfCreation = std::time(0);
}

Account::Account(const Account& other)
{
	copyFrom(other);
}

Account& Account::operator=(const Account& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Account::~Account()
{
	free();
}

const char* Account::getIban() const
{
	return iban;
}

size_t Account::getID() const
{
	return ID;
}

double Account::getBalance() const
{
	return amount;
}

void Account::deposit(double amount)
{
	this->amount += amount;
}

void Account::display() const
{
	std::cout << iban << " " << ID << " " << amount;
}
