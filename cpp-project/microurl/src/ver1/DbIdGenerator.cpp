#include "DbIdGenerator.h"

long DbIdGenerator::id = 1;

long DbIdGenerator::generate(const char* token)
{
	return id++;
}
