#pragma once
#include "Account.h"

class PrivelegeAccount : public Account
{
	double overdraft;

public:
	PrivelegeAccount() = delete;
	PrivelegeAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID, double overdraft);

	Account* clone() const override;

	bool withdraw(double amount) override;
	void display() const override;
};
