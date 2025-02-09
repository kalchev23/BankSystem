#include "PrivelegeAccount.h"
#include <iostream>

PrivelegeAccount::PrivelegeAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID, double overdraft) :
	Account(userName, password, iban, amount, ID)
{
	this->overdraft = overdraft;
}

Account* PrivelegeAccount::clone() const
{
	Account* copy = new PrivelegeAccount(*this);
	return copy;
}

bool PrivelegeAccount::withdraw(double amount)
{
	double currentAmount = getBalance();
	if (currentAmount + overdraft < amount)
		return false;

	setAmount(currentAmount - amount);
	return true;
}

void PrivelegeAccount::display() const
{
	std::cout << "PrivelegeAccount ";
	Account::display();
	std::cout << " " << overdraft << std::endl;
}
