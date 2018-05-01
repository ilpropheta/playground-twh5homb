#include "DbIdGenerator.h"

long DbIdGenerator::id = 100;

long DbIdGenerator::Generate([[maybe_unused]]const char* token) // alza warning a livello 4 e dovrai usare maybe_unused
{
	return id++;
}
