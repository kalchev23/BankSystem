#pragma once

class Customer
{
	char* name;
	char* address;
	size_t id;

	void copyFrom(const Customer& other);
	void free();

	void setName(const char* name);
	void setAddress(const char* address);

public:
	static size_t idGenerated;

	const char* getName()const;
	const char* getAddress() const;
	size_t getID() const;

	Customer() = delete;
	Customer(const char* name, const char* address);
	Customer(const Customer& other);
	Customer& operator=(const Customer& other);
	~Customer();

	Customer* clone() const;

	void print() const;
};
