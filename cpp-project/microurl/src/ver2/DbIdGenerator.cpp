#include "DbIdGenerator.h"

long DbIdGenerator::id = 100;

long DbIdGenerator::generate(const char* token)
{
	return id++;
}
