#pragma once
#include "IIdGenerator.h"

class DbIdGenerator : public IIdGenerator
{
	static long id;
public:
	long Generate(const char* token) override;
};