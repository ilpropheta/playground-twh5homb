#pragma once
#include "IIdGenerator.h"

class DbIdGenerator : public IIdGenerator
{
	static long id;
public:
	long Generate(const char* token); // alza warning a livello 4 e dovrai usare maybe_unused
};