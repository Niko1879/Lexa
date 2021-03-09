#include "IO.h"


namespace Lexa
{
	namespace IO
	{
		std::string ReadFile(const std::string& filepath)
		{
			std::ifstream t(filepath);
			std::stringstream buffer;
			buffer << t.rdbuf();
			return buffer.str();
		}
	}
}
