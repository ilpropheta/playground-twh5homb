#include "DbIdGenerator.h"

long DbIdGenerator::id = 100;

long DbIdGenerator::Generate(const char* token)
{
	return id++;
}
