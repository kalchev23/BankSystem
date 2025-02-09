#pragma once
#include "Account.h"

class NormalAccount : public Account
{
public:
	NormalAccount() = delete;
	NormalAccount(const char* userName, const char* password, const char* iban, double amount, size_t ID);

	Account* clone() const override;

	bool withdraw(double amount) override;
	void display() const override;
};
