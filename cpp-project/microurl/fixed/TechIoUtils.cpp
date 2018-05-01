#include "TechIoUtils.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void TechIo::Message(std::wstring_view channel, std::wstring_view msg)
{
	wstringstream ss(msg.data());
	wstring line;
	while (getline(ss, line, L'\n')) 
	{
		std::wcout << "TECHIO> message --channel \"" << channel << "\" \"" << line << "\"" << std::endl;
	}
}

void TechIo::Message(std::string_view channel, std::string_view msg)
{
	stringstream ss(msg.data());
	string line;
	while (getline(ss, line, '\n'))
	{
		std::cout << "TECHIO> message --channel \"" << channel << "\" \"" << line << "\"" << std::endl;
	}
}

static void SetSuccess(bool success)
{
	cout << "TECHIO> success " << std::boolalpha << success << endl;
}

void TechIo::Succeed()
{
	SetSuccess(true);
}

void TechIo::Fail()
{
	SetSuccess(false);
}

