#pragma once

class Log
{
	char* data;

	void copyFrom(const Log& other);
	void free();

	void setData(const char* data);

public:
	Log();
	Log(const char* data);
	Log(const Log& other);
	Log& operator=(const Log& other);
	~Log();

	const char* getData() const;

	void print() const;
};
