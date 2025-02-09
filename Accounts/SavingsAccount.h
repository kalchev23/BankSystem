#pragma once
#include "Account.h"

class SavingsAccount : public Account
{
	double interestRate;

public:
	SavingsAccount() = delete;
	SavingsAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID, double interestRate);

	Account* clone() const override;

	bool withdraw(double amount) override;
	void display() const override;
};
