#pragma once

class DbIdGenerator
{
	static long id;
public:
	long generate(const char* token);
};