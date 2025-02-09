#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID, double interestRate) :
	Account(userName, password, iban, amount, ID)
{
	this->interestRate = interestRate;
}

Account* SavingsAccount::clone() const
{
	Account* copy = new SavingsAccount(*this);
	return copy;
}

bool SavingsAccount::withdraw(double amount)
{
	return false;
}

void SavingsAccount::display() const
{
	std::cout << "SavingsAccount ";
	Account::display();
	std::cout << " " << interestRate << std::endl;
}
