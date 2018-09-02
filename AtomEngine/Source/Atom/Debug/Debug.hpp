#pragma once

#include <string>

namespace Atom
{
	namespace Debug
	{
		void Log(const std::string& msg);
		void Warning(const std::string& warning);
		void Error(const std::string& error);
		void Assert(bool condition);
	}
}
