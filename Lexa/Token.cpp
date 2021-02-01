#include "Token.h"

namespace Lexa
{
	namespace Interpreter
	{
		bool operator==(const Token& t1, const Token& t2)
		{
			return t1.type == t2.type &&
				t1.value == t2.value;
		}


		std::ostream& operator<<(std::ostream& stream, const Token& token)
		{
			return stream << "(" << TokenTypeStr.at(token.type) << ", " << token.value << ")";
		}
	}
}