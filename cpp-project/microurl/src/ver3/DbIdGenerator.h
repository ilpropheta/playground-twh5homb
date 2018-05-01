#pragma once

class DbIdGenerator
{
	static long id;
public:
	long Generate(const char* token);
};