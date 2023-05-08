#pragma once

#include <cstdio>

namespace atom
{
	extern FILE* errorOut;
	extern FILE* warnOut;
	extern FILE* logOut;
}

/* Core log macros */
#define ATOM_CORE_ERROR(...) fprintf(atom::errorOut, __VA_ARGS__)
#define ATOM_CORE_WARN(...) fprintf(atom::warnOut, __VA_ARGS__)
#define ATOM_CORE_LOG(...) fprintf(atom::logOut, __VA_ARGS__)


/* App log macros */
#define ATOM_ERROR(...) fprintf(atom::errorOut, __VA_ARGS__)
#define ATOM_WARN(...) fprintf(atom::warnOut, __VA_ARGS__)
#define ATOM_LOG(...) fprintf(atom::logOut, __VA_ARGS__)
