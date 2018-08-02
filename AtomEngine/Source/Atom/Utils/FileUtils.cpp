#include <Atom/Utils/FileUtils.hpp>

namespace atom
{
	std::string ReadFile(const char* path)
	{
		FILE* file;
		fopen_s(&file, path, "rt");
		fseek(file, 0, SEEK_END);

		unsigned long lenght = ftell(file);
		char* data = new char[lenght + 1];
		memset(data, 0, lenght + 1);
		fseek(file, 0, SEEK_SET);

		fread(data, 1, lenght, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}
}
