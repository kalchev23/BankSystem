#include "Log.h"
#include <iostream>
#pragma warning(disable: 4996)

void Log::copyFrom(const Log& other)
{
	data = new char[strlen(other.data) + 1];
	strcpy(data, other.data);
}

void Log::free()
{
	delete[] data;
}

void Log::setData(const char* data)
{
	if (data == nullptr || data == this->data)
		return;

	if (this->data != nullptr)
		delete[] this->data;

	this->data = new char[strlen(data) + 1];
	strcpy(this->data, data);
}

Log::Log()
{
	data = new char[1];
	data[0] = '\0';
}

Log::Log(const char* data) : data(nullptr)
{
	setData(data);
}

Log::Log(const Log& other)
{
	copyFrom(other);
}

Log& Log::operator=(const Log& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Log::~Log()
{
	free();
}

void Log::print() const
{
	std::cout << data << std::endl;
}

const char* Log::getData() const
{
	return data;
}
