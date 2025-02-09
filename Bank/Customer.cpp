#include "Customer.h"
#include <cstring>
#include <iostream>
#pragma warning(disable: 4996)

size_t Customer::idGenerated = 0;

void Customer::copyFrom(const Customer& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	address = new char[strlen(other.address) + 1];
	strcpy(address, other.address);

	id = other.id;
}

void Customer::free()
{
	delete[] name;
	delete[] address;
}

void Customer::setName(const char* name)
{
	if (name == nullptr || name == this->name)
		return;

	if(this->name != nullptr)
		delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Customer::setAddress(const char* address)
{
	if (address == nullptr || address == this->address)
		return;

	if (this->address != nullptr)
		delete[] this->address;

	this->address = new char[strlen(address) + 1];
	strcpy(this->address, address);
}

const char* Customer::getName() const
{
	return name;
}

const char* Customer::getAddress() const
{
	return address;
}

size_t Customer::getID() const
{
	return id;
}

Customer::Customer(const char* name, const char* address)
{
	setName(name);
	setAddress(address);
	id = idGenerated++;
}

Customer::Customer(const Customer& other)
{
	copyFrom(other);
}

Customer& Customer::operator=(const Customer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Customer::~Customer()
{
	free();
}

Customer* Customer::clone() const
{
	Customer* copy = new Customer(*this);
	return copy;
}

void Customer::print() const
{
	std::cout << name << " " << address << std::endl;
}
