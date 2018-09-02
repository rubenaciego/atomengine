#include <vector>
#include <Atom/Utils/StringUtils.hpp>

namespace Atom
{
	std::string GetExtension(const std::string& filepath)
	{
		int dotPos = filepath.length();
		while (filepath[--dotPos] != '.');

		return std::string(filepath.begin() + dotPos + 1, filepath.end());
	}
}
