#pragma once
#include <string>

namespace Lexa
{
	namespace IO
	{
		std::string ReadFile(const std::string& filepath);

		std::string SubstrUtf8(const std::string& str, size_t start, size_t count);

		std::string EraseUtf8(const std::string& str, size_t index);
	}
}

