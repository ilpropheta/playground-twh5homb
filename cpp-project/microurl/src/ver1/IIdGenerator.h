#pragma once

class IIdGenerator
{
public:
	virtual ~IIdGenerator() = default;
	virtual long Generate(const char* token) = 0;
};