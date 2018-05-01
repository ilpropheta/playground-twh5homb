#pragma once
#include <string_view>

namespace TechIo
{
	void Message(std::wstring_view channel, std::wstring_view msg);
	void Message(std::string_view channel, std::string_view msg);
	void Succeed();
	void Fail();
}