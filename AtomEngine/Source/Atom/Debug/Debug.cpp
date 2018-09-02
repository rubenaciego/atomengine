#include <Atom/Debug/Debug.hpp>

#ifdef _DEBUG
	#include <iostream>
	#include <assert.h>

	#ifdef _WIN32
		#include <Windows.h>
	#endif
#endif

namespace Atom
{
	namespace Debug
	{
		void Log(const std::string& msg)
		{
			#ifdef _DEBUG
				std::cout << msg;
			#endif
		}

		void Warning(const std::string& warning)
		{
			#ifdef _DEBUG
				#ifdef _WIN32
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
					std::cout << warning;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				#else
					std::cout << "\033[0; 31m" << warning << "\033[0m";
				#endif
			#endif
		}

		void Error(const std::string& error)
		{
			#ifdef _DEBUG
				#ifdef _WIN32
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
					std::cout << error;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				#else
					std::cout << "\033[0; 33m" << error << "\033[0m";
				#endif
			#endif
		}

		void Debug::Assert(bool condition)
		{
			#ifdef _DEBUG
				assert(condition);
			#endif
		}
	}
}
