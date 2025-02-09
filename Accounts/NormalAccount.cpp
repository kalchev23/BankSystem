#include "NormalAccount.h"
#include <iostream>

NormalAccount::NormalAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID) : 
	Account(userName, password, iban, amount, ID)
{

}

Account* NormalAccount::clone() const
{
	Account* copy = new NormalAccount(*this);
	return copy;
}

bool NormalAccount::withdraw(double amount)
{
	double currentAmount = getBalance();
	if (currentAmount < amount)
		return false;

	setAmount(currentAmount - amount);
	return true;
}

void NormalAccount::display() const
{
	std::cout << "NormalAccount ";
	Account::display();
	std::cout << std::endl;
}
